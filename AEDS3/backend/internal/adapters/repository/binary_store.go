package repository

import (
	"encoding/binary"
	"io"
	"os"
	"path/filepath"
	"sort"
	"sync"

	"backend/internal/domain"
)

const (
	fileHeaderVersion byte = 1
	fileHeaderSize         = 9
	recordMetaSize         = 9
	indexVersion      byte = 1
	indexHeaderSize        = 5
	indexEntrySize         = 12
)

type fileHeader struct {
	Version byte
	LastID  int32
	Count   int32
}

type recordMeta struct {
	Offset int64
	ID     int
	Size   uint32
}

type payloadCodec[T any] struct {
	encode func(T) ([]byte, error)
	decode func([]byte, int) (T, error)
}

type storedRecord[T any] struct {
	Meta  recordMeta
	Value T
}

type binaryEntityStore[T any] struct {
	path      string
	indexPath string
	index     *extensibleHashIndex
	getID     func(T) int
	setID     func(*T, int)
	codec     payloadCodec[T]
	mu        sync.Mutex
}

func newBinaryEntityStore[T any](path string, getID func(T) int, setID func(*T, int), codec payloadCodec[T]) (*binaryEntityStore[T], error) {
	store := &binaryEntityStore[T]{
		path:      path,
		indexPath: path + ".pidx",
		getID:     getID,
		setID:     setID,
		codec:     codec,
		index:     newExtensibleHashIndex(8),
	}
	if err := store.ensureFile(); err != nil {
		return nil, err
	}
	if err := store.initializeIndex(); err != nil {
		return nil, err
	}
	return store, nil
}

func (s *binaryEntityStore[T]) ensureFile() error {
	if err := os.MkdirAll(filepath.Dir(s.path), 0o755); err != nil {
		return err
	}

	file, err := os.OpenFile(s.path, os.O_CREATE|os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	info, err := file.Stat()
	if err != nil {
		return err
	}
	if info.Size() < fileHeaderSize {
		if err := file.Truncate(0); err != nil {
			return err
		}
		return writeHeader(file, fileHeader{Version: fileHeaderVersion})
	}

	head, err := readHeader(file)
	if err != nil || head.Version != fileHeaderVersion {
		if err := file.Truncate(0); err != nil {
			return err
		}
		return writeHeader(file, fileHeader{Version: fileHeaderVersion})
	}

	return nil
}

func (s *binaryEntityStore[T]) initializeIndex() error {
	s.mu.Lock()
	defer s.mu.Unlock()
	if err := s.loadIndexFileLocked(); err == nil {
		return nil
	}
	return s.rebuildIndexLocked()
}

func (s *binaryEntityStore[T]) rebuildIndexLocked() error {
	file, err := os.OpenFile(s.path, os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		return err
	}
	lastID := header.LastID
	activeCount := int32(0)

	s.index.Reset()
	if _, err := file.Seek(fileHeaderSize, io.SeekStart); err != nil {
		return err
	}

	for {
		offset, err := file.Seek(0, io.SeekCurrent)
		if err != nil {
			return err
		}

		headerBuf := make([]byte, recordMetaSize)
		_, err = io.ReadFull(file, headerBuf)
		if err == io.EOF || err == io.ErrUnexpectedEOF {
			break
		}
		if err != nil {
			return err
		}

		deleted := headerBuf[0] == 1
		recordID := int(int32(binary.LittleEndian.Uint32(headerBuf[1:5])))
		size := binary.LittleEndian.Uint32(headerBuf[5:9])
		if int32(recordID) > lastID {
			lastID = int32(recordID)
		}
		if _, err := file.Seek(int64(size), io.SeekCurrent); err != nil {
			return err
		}

		if deleted {
			continue
		}
		activeCount++
		s.index.Insert(recordID, offset)
	}

	if header.LastID != lastID || header.Count != activeCount {
		header.LastID = lastID
		header.Count = activeCount
		if err := writeHeader(file, header); err != nil {
			return err
		}
	}

	return s.persistIndexFile()
}

func (s *binaryEntityStore[T]) loadIndexFileLocked() error {
	file, err := os.OpenFile(s.indexPath, os.O_RDONLY, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	header := make([]byte, indexHeaderSize)
	if _, err := io.ReadFull(file, header); err != nil {
		return err
	}
	if header[0] != indexVersion {
		return domain.ErrInvalidEntity
	}

	count := binary.LittleEndian.Uint32(header[1:5])
	entries := make([]indexEntry, 0, count)
	for i := uint32(0); i < count; i++ {
		var buf [indexEntrySize]byte
		if _, err := io.ReadFull(file, buf[:]); err != nil {
			return err
		}
		entries = append(entries, indexEntry{
			Key:    int(int32(binary.LittleEndian.Uint32(buf[0:4]))),
			Offset: int64(binary.LittleEndian.Uint64(buf[4:12])),
		})
	}

	s.index.Load(entries)
	return nil
}

func (s *binaryEntityStore[T]) syncPrimaryIndexLocked() {
	if err := s.persistIndexFile(); err == nil {
		return
	}
	_ = s.rebuildIndexLocked()
}

func (s *binaryEntityStore[T]) persistIndexFile() error {
	entries := s.index.Snapshot()
	sort.Slice(entries, func(i, j int) bool { return entries[i].Key < entries[j].Key })

	tempPath := s.indexPath + ".tmp"
	file, err := os.OpenFile(tempPath, os.O_CREATE|os.O_TRUNC|os.O_RDWR, 0o644)
	if err != nil {
		return err
	}

	cleanup := func(retErr error) error {
		_ = file.Close()
		if retErr != nil {
			_ = os.Remove(tempPath)
		}
		return retErr
	}

	header := make([]byte, indexHeaderSize)
	header[0] = indexVersion
	binary.LittleEndian.PutUint32(header[1:5], uint32(len(entries)))
	if _, err := file.Write(header); err != nil {
		return cleanup(err)
	}

	for _, entry := range entries {
		var buf [indexEntrySize]byte
		binary.LittleEndian.PutUint32(buf[0:4], uint32(entry.Key))
		binary.LittleEndian.PutUint64(buf[4:12], uint64(entry.Offset))
		if _, err := file.Write(buf[:]); err != nil {
			return cleanup(err)
		}
	}

	if err := file.Sync(); err != nil {
		return cleanup(err)
	}
	if err := file.Close(); err != nil {
		_ = os.Remove(tempPath)
		return err
	}
	if err := os.Remove(s.indexPath); err != nil && !os.IsNotExist(err) {
		_ = os.Remove(tempPath)
		return err
	}
	return os.Rename(tempPath, s.indexPath)
}

func (s *binaryEntityStore[T]) Create(item T) (T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	file, err := os.OpenFile(s.path, os.O_RDWR, 0o644)
	if err != nil {
		var zero T
		return zero, err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		var zero T
		return zero, err
	}

	header.LastID++
	id := int(header.LastID)
	s.setID(&item, id)

	payload, err := s.codec.encode(item)
	if err != nil {
		var zero T
		return zero, err
	}

	offset, err := appendRecord(file, false, id, payload)
	if err != nil {
		var zero T
		return zero, err
	}

	s.index.Insert(id, offset)
	header.Count++
	if err := writeHeader(file, header); err != nil {
		var zero T
		return zero, err
	}
	s.syncPrimaryIndexLocked()

	return item, nil
}

func (s *binaryEntityStore[T]) GetByID(id int) (T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	file, err := os.OpenFile(s.path, os.O_RDONLY, 0o644)
	if err != nil {
		var zero T
		return zero, err
	}
	defer file.Close()

	if _, err = readHeader(file); err != nil {
		var zero T
		return zero, err
	}

	offset, ok := s.index.Get(id)
	if !ok {
		if err := s.rebuildIndexLocked(); err != nil {
			var zero T
			return zero, err
		}
		offset, ok = s.index.Get(id)
		if !ok {
			var zero T
			return zero, domain.ErrNotFound
		}
	}

	item, recordID, deleted, err := readRecordAt(file, offset, s.codec)
	if err != nil {
		var zero T
		return zero, err
	}
	if deleted || recordID != id {
		if err := s.rebuildIndexLocked(); err != nil {
			var zero T
			return zero, err
		}
		offset, ok = s.index.Get(id)
		if !ok {
			var zero T
			return zero, domain.ErrNotFound
		}
		item, _, deleted, err = readRecordAt(file, offset, s.codec)
		if err != nil || deleted {
			var zero T
			return zero, domain.ErrNotFound
		}
	}

	return item, nil
}

func (s *binaryEntityStore[T]) GetAll() ([]T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	file, err := os.OpenFile(s.path, os.O_RDONLY, 0o644)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	if _, err = readHeader(file); err != nil {
		return nil, err
	}

	items := make([]T, 0)
	if _, err := file.Seek(fileHeaderSize, io.SeekStart); err != nil {
		return nil, err
	}

	for {
		headerBuf := make([]byte, recordMetaSize)
		_, err := io.ReadFull(file, headerBuf)
		if err == io.EOF || err == io.ErrUnexpectedEOF {
			break
		}
		if err != nil {
			return nil, err
		}

		deleted := headerBuf[0] == 1
		size := binary.LittleEndian.Uint32(headerBuf[5:9])
		payload := make([]byte, size)
		if _, err := io.ReadFull(file, payload); err != nil {
			return nil, err
		}
		if deleted {
			continue
		}
		item, err := s.codec.decode(payload, int(int32(binary.LittleEndian.Uint32(headerBuf[1:5]))))
		if err != nil {
			continue
		}
		items = append(items, item)
	}

	return items, nil
}

func (s *binaryEntityStore[T]) Update(id int, item T) (T, error) {
	s.mu.Lock()
	defer s.mu.Unlock()

	file, err := os.OpenFile(s.path, os.O_RDWR, 0o644)
	if err != nil {
		var zero T
		return zero, err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		var zero T
		return zero, err
	}

	offset, ok := s.index.Get(id)
	if !ok {
		if err := s.rebuildIndexLocked(); err != nil {
			var zero T
			return zero, err
		}
		offset, ok = s.index.Get(id)
		if !ok {
			var zero T
			return zero, domain.ErrNotFound
		}
	}

	if err := markDeletedAt(file, offset); err != nil {
		var zero T
		return zero, err
	}

	s.setID(&item, id)
	payload, err := s.codec.encode(item)
	if err != nil {
		var zero T
		return zero, err
	}
	newOffset, err := appendRecord(file, false, id, payload)
	if err != nil {
		var zero T
		return zero, err
	}

	s.index.Insert(id, newOffset)
	if err := writeHeader(file, header); err != nil {
		var zero T
		return zero, err
	}
	s.syncPrimaryIndexLocked()

	return item, nil
}

func (s *binaryEntityStore[T]) Delete(id int) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	file, err := os.OpenFile(s.path, os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		return err
	}

	offset, ok := s.index.Get(id)
	if !ok {
		if err := s.rebuildIndexLocked(); err != nil {
			return err
		}
		offset, ok = s.index.Get(id)
		if !ok {
			return domain.ErrNotFound
		}
	}

	if err := markDeletedAt(file, offset); err != nil {
		return err
	}
	s.index.Delete(id)
	if header.Count > 0 {
		header.Count--
	}
	if err := writeHeader(file, header); err != nil {
		return err
	}
	s.syncPrimaryIndexLocked()
	return nil
}

func (s *binaryEntityStore[T]) HashStats() HashIndexStats {
	s.mu.Lock()
	defer s.mu.Unlock()
	return s.index.Stats()
}

func (s *binaryEntityStore[T]) RewriteSorted(items []T) error {
	s.mu.Lock()
	defer s.mu.Unlock()

	existingLastID := int32(0)
	if f, err := os.Open(s.path); err == nil {
		if h, err := readHeader(f); err == nil {
			existingLastID = h.LastID
		}
		f.Close()
	}

	maxID := existingLastID
	for _, item := range items {
		if id := int32(s.getID(item)); id > maxID {
			maxID = id
		}
	}

	tmpPath := s.path + ".rewrite.tmp"
	file, err := os.OpenFile(tmpPath, os.O_CREATE|os.O_TRUNC|os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	cleanup := func() { file.Close(); os.Remove(tmpPath) }

	header := fileHeader{Version: fileHeaderVersion, LastID: maxID, Count: int32(len(items))}
	if err := writeHeader(file, header); err != nil {
		cleanup()
		return err
	}

	s.index.Reset()
	for _, item := range items {
		payload, err := s.codec.encode(item)
		if err != nil {
			cleanup()
			return err
		}
		offset, err := appendRecord(file, false, s.getID(item), payload)
		if err != nil {
			cleanup()
			return err
		}
		s.index.Insert(s.getID(item), offset)
	}
	file.Close()

	if err := os.Rename(tmpPath, s.path); err != nil {
		os.Remove(tmpPath)
		return err
	}

	return s.persistIndexFile()
}

func readHeader(file *os.File) (fileHeader, error) {
	if _, err := file.Seek(0, io.SeekStart); err != nil {
		return fileHeader{}, err
	}

	buf := make([]byte, fileHeaderSize)
	if _, err := io.ReadFull(file, buf); err != nil {
		return fileHeader{}, err
	}
	return fileHeader{
		Version: buf[0],
		LastID:  int32(binary.LittleEndian.Uint32(buf[1:5])),
		Count:   int32(binary.LittleEndian.Uint32(buf[5:9])),
	}, nil
}

func writeHeader(file *os.File, h fileHeader) error {
	if _, err := file.Seek(0, io.SeekStart); err != nil {
		return err
	}
	buf := make([]byte, fileHeaderSize)
	buf[0] = fileHeaderVersion
	binary.LittleEndian.PutUint32(buf[1:5], uint32(h.LastID))
	binary.LittleEndian.PutUint32(buf[5:9], uint32(h.Count))
	_, err := file.Write(buf)
	return err
}

func appendRecord(file *os.File, deleted bool, id int, payload []byte) (int64, error) {
	offset, err := file.Seek(0, io.SeekEnd)
	if err != nil {
		return 0, err
	}

	tomb := byte(0)
	if deleted {
		tomb = 1
	}

	headerBuf := make([]byte, recordMetaSize)
	headerBuf[0] = tomb
	binary.LittleEndian.PutUint32(headerBuf[1:5], uint32(id))
	binary.LittleEndian.PutUint32(headerBuf[5:9], uint32(len(payload)))

	if _, err := file.Write(headerBuf); err != nil {
		return 0, err
	}
	if _, err := file.Write(payload); err != nil {
		return 0, err
	}

	return offset, nil
}

func markDeletedAt(file *os.File, offset int64) error {
	if _, err := file.Seek(offset, io.SeekStart); err != nil {
		return err
	}
	_, err := file.Write([]byte{1})
	return err
}

func readRecordAt[T any](file *os.File, offset int64, codec payloadCodec[T]) (T, int, bool, error) {
	if _, err := file.Seek(offset, io.SeekStart); err != nil {
		var zero T
		return zero, 0, false, err
	}

	headerBuf := make([]byte, recordMetaSize)
	if _, err := io.ReadFull(file, headerBuf); err != nil {
		var zero T
		return zero, 0, false, err
	}

	deleted := headerBuf[0] == 1
	recordID := int(int32(binary.LittleEndian.Uint32(headerBuf[1:5])))
	size := binary.LittleEndian.Uint32(headerBuf[5:9])
	payload := make([]byte, size)
	if _, err := io.ReadFull(file, payload); err != nil {
		var zero T
		return zero, 0, false, err
	}

	if deleted {
		var zero T
		return zero, recordID, true, nil
	}

	item, err := codec.decode(payload, recordID)
	if err != nil {
		var zero T
		return zero, 0, false, err
	}

	return item, recordID, false, nil
}
