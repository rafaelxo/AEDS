package repository

import (
	"backend/internal/domain"
	propertyamenityuc "backend/internal/usecase/propertyamenity"
	"encoding/binary"
	"errors"
	"io"
	"os"
	"path/filepath"
	"sync"
)

const propertyAmenityRecordHeaderSize = 13

type PropertyAmenityFileRepository struct {
	path         string
	byPropertyID *multiExtensibleHashIndex
	byAmenityID  *multiExtensibleHashIndex
	orderedByKey *bPlusTree
	mu           sync.Mutex
}

func NewPropertyAmenityFileRepository(path string) (*PropertyAmenityFileRepository, error) {
	repo := &PropertyAmenityFileRepository{
		path:         path,
		orderedByKey: newBPlusTree(),
	}
	if err := repo.ensureFile(); err != nil {
		return nil, err
	}

	byPropertyID, err := newMultiExtensibleHashIndex(path+".byproperty.ridx", 8)
	if err != nil {
		return nil, err
	}
	byAmenityID, err := newMultiExtensibleHashIndex(path+".byamenity.ridx", 8)
	if err != nil {
		return nil, err
	}
	repo.byPropertyID = byPropertyID
	repo.byAmenityID = byAmenityID

	if err := repo.rebuildIndexes(); err != nil {
		return nil, err
	}
	return repo, nil
}

func (r *PropertyAmenityFileRepository) Create(item domain.PropertyAmenity) (domain.PropertyAmenity, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	if _, err := r.findByPairLocked(item.PropertyID, item.AmenityID); err == nil {
		return domain.PropertyAmenity{}, domain.ErrAlreadyExists
	} else if !errors.Is(err, domain.ErrNotFound) {
		return domain.PropertyAmenity{}, err
	}

	file, err := os.OpenFile(r.path, os.O_RDWR, 0o644)
	if err != nil {
		return domain.PropertyAmenity{}, err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		return domain.PropertyAmenity{}, err
	}
	offset, err := appendPropertyAmenityRecord(file, item)
	if err != nil {
		return domain.PropertyAmenity{}, err
	}
	header.Count++
	if err := writeHeader(file, header); err != nil {
		return domain.PropertyAmenity{}, err
	}

	r.indexLocked(item, offset)
	r.syncIndexesLocked()
	return item, nil
}

func (r *PropertyAmenityFileRepository) Get(propertyID, amenityID int) (domain.PropertyAmenity, error) {
	r.mu.Lock()
	defer r.mu.Unlock()
	return r.findByPairLocked(propertyID, amenityID)
}

func (r *PropertyAmenityFileRepository) GetByPropertyID(propertyID int) ([]domain.PropertyAmenity, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	offsets, ok := r.byPropertyID.Get(propertyID)
	if !ok {
		return []domain.PropertyAmenity{}, nil
	}
	return r.loadByOffsetsLocked(offsets)
}

func (r *PropertyAmenityFileRepository) GetByPropertyIDOrderedByAmenityID(propertyID int) ([]domain.PropertyAmenity, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	minKey := propertyAmenityOrderKey(propertyID, 0)
	maxKey := int64(uint64(uint32(propertyID))<<32 | uint64(^uint32(0)))
	offsets := r.orderedByKey.Range(minKey, maxKey)
	return r.loadByOffsetsLocked(offsets)
}

func (r *PropertyAmenityFileRepository) GetByAmenityID(amenityID int) ([]domain.PropertyAmenity, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	offsets, ok := r.byAmenityID.Get(amenityID)
	if !ok {
		return []domain.PropertyAmenity{}, nil
	}
	return r.loadByOffsetsLocked(offsets)
}

func (r *PropertyAmenityFileRepository) Delete(propertyID, amenityID int) error {
	r.mu.Lock()
	defer r.mu.Unlock()
	return r.deleteLocked(propertyID, amenityID)
}

func (r *PropertyAmenityFileRepository) DeleteByPropertyID(propertyID int) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	offsets, ok := r.byPropertyID.Get(propertyID)
	if !ok {
		return nil
	}
	items, err := r.loadByOffsetsLocked(offsets)
	if err != nil {
		return err
	}
	for _, item := range items {
		if err := r.deleteLocked(item.PropertyID, item.AmenityID); err != nil && !errors.Is(err, domain.ErrNotFound) {
			return err
		}
	}
	return nil
}

func (r *PropertyAmenityFileRepository) DeleteByAmenityID(amenityID int) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	offsets, ok := r.byAmenityID.Get(amenityID)
	if !ok {
		return nil
	}
	items, err := r.loadByOffsetsLocked(offsets)
	if err != nil {
		return err
	}
	for _, item := range items {
		if err := r.deleteLocked(item.PropertyID, item.AmenityID); err != nil && !errors.Is(err, domain.ErrNotFound) {
			return err
		}
	}
	return nil
}

func (r *PropertyAmenityFileRepository) ensureFile() error {
	if err := os.MkdirAll(filepath.Dir(r.path), 0o755); err != nil {
		return err
	}
	file, err := os.OpenFile(r.path, os.O_CREATE|os.O_RDWR, 0o644)
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

	header, err := readHeader(file)
	if err != nil || header.Version != fileHeaderVersion {
		if err := file.Truncate(0); err != nil {
			return err
		}
		return writeHeader(file, fileHeader{Version: fileHeaderVersion})
	}
	return nil
}

func (r *PropertyAmenityFileRepository) rebuildIndexes() error {
	r.byPropertyID.Reset()
	r.byAmenityID.Reset()
	r.orderedByKey.Reset()

	items, err := r.scanAllWithOffsets()
	if err != nil {
		return err
	}
	for _, item := range items {
		r.indexLocked(item.relation, item.offset)
	}
	return r.flushIndexes()
}

func (r *PropertyAmenityFileRepository) flushIndexes() error {
	if err := r.byPropertyID.persistToFile(); err != nil {
		return err
	}
	return r.byAmenityID.persistToFile()
}

func (r *PropertyAmenityFileRepository) syncIndexesLocked() {
	if err := r.flushIndexes(); err == nil {
		return
	}
	_ = r.rebuildIndexes()
}

func (r *PropertyAmenityFileRepository) indexLocked(item domain.PropertyAmenity, offset int64) {
	r.byPropertyID.Insert(item.PropertyID, offset)
	r.byAmenityID.Insert(item.AmenityID, offset)
	r.orderedByKey.Insert(propertyAmenityOrderKey(item.PropertyID, item.AmenityID), offset)
}

func (r *PropertyAmenityFileRepository) unindexLocked(item domain.PropertyAmenity, offset int64) {
	r.byPropertyID.Delete(item.PropertyID, offset)
	r.byAmenityID.Delete(item.AmenityID, offset)
	r.orderedByKey.Delete(propertyAmenityOrderKey(item.PropertyID, item.AmenityID), offset)
}

func (r *PropertyAmenityFileRepository) findByPairLocked(propertyID, amenityID int) (domain.PropertyAmenity, error) {
	item, _, err := r.findByPairWithOffsetLocked(propertyID, amenityID)
	return item, err
}

func (r *PropertyAmenityFileRepository) findByPairWithOffsetLocked(propertyID, amenityID int) (domain.PropertyAmenity, int64, error) {
	offsets, ok := r.byPropertyID.Get(propertyID)
	if !ok {
		return domain.PropertyAmenity{}, 0, domain.ErrNotFound
	}
	file, err := os.OpenFile(r.path, os.O_RDONLY, 0o644)
	if err != nil {
		return domain.PropertyAmenity{}, 0, err
	}
	defer file.Close()

	for _, offset := range offsets {
		item, deleted, err := readPropertyAmenityAt(file, offset)
		if err != nil || deleted {
			continue
		}
		if item.PropertyID == propertyID && item.AmenityID == amenityID {
			return item, offset, nil
		}
	}
	return domain.PropertyAmenity{}, 0, domain.ErrNotFound
}

func (r *PropertyAmenityFileRepository) loadByOffsetsLocked(offsets []int64) ([]domain.PropertyAmenity, error) {
	file, err := os.OpenFile(r.path, os.O_RDONLY, 0o644)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	items := make([]domain.PropertyAmenity, 0, len(offsets))
	for _, offset := range offsets {
		item, deleted, err := readPropertyAmenityAt(file, offset)
		if err != nil || deleted {
			continue
		}
		items = append(items, item)
	}
	return items, nil
}

func (r *PropertyAmenityFileRepository) deleteLocked(propertyID, amenityID int) error {
	item, offset, err := r.findByPairWithOffsetLocked(propertyID, amenityID)
	if err != nil {
		return err
	}

	file, err := os.OpenFile(r.path, os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		return err
	}
	if _, err := file.Seek(offset, io.SeekStart); err != nil {
		return err
	}
	if _, err := file.Write([]byte{1}); err != nil {
		return err
	}
	if header.Count > 0 {
		header.Count--
	}
	if err := writeHeader(file, header); err != nil {
		return err
	}

	r.unindexLocked(item, offset)
	r.syncIndexesLocked()
	return nil
}

type propertyAmenityWithOffset struct {
	relation domain.PropertyAmenity
	offset   int64
}

func (r *PropertyAmenityFileRepository) scanAllWithOffsets() ([]propertyAmenityWithOffset, error) {
	file, err := os.OpenFile(r.path, os.O_RDWR, 0o644)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	header, err := readHeader(file)
	if err != nil {
		return nil, err
	}
	activeCount := int32(0)
	items := make([]propertyAmenityWithOffset, 0)

	if _, err := file.Seek(fileHeaderSize, io.SeekStart); err != nil {
		return nil, err
	}
	for {
		offset, err := file.Seek(0, io.SeekCurrent)
		if err != nil {
			return nil, err
		}
		item, deleted, err := readNextPropertyAmenity(file)
		if err == io.EOF || err == io.ErrUnexpectedEOF {
			break
		}
		if err != nil {
			return nil, err
		}
		if deleted {
			continue
		}
		activeCount++
		items = append(items, propertyAmenityWithOffset{relation: item, offset: offset})
	}

	if header.Count != activeCount {
		header.Count = activeCount
		if err := writeHeader(file, header); err != nil {
			return nil, err
		}
	}
	return items, nil
}

func appendPropertyAmenityRecord(file *os.File, item domain.PropertyAmenity) (int64, error) {
	payload := encodePropertyAmenityPayload(item)
	offset, err := file.Seek(0, io.SeekEnd)
	if err != nil {
		return 0, err
	}

	header := make([]byte, propertyAmenityRecordHeaderSize)
	header[0] = 0
	binary.LittleEndian.PutUint32(header[1:5], uint32(int32(item.PropertyID)))
	binary.LittleEndian.PutUint32(header[5:9], uint32(int32(item.AmenityID)))
	binary.LittleEndian.PutUint32(header[9:13], uint32(len(payload)))
	if _, err := file.Write(header); err != nil {
		return 0, err
	}
	if _, err := file.Write(payload); err != nil {
		return 0, err
	}
	return offset, nil
}

func readPropertyAmenityAt(file *os.File, offset int64) (domain.PropertyAmenity, bool, error) {
	if _, err := file.Seek(offset, io.SeekStart); err != nil {
		return domain.PropertyAmenity{}, false, err
	}
	return readNextPropertyAmenity(file)
}

func readNextPropertyAmenity(file *os.File) (domain.PropertyAmenity, bool, error) {
	header := make([]byte, propertyAmenityRecordHeaderSize)
	if _, err := io.ReadFull(file, header); err != nil {
		return domain.PropertyAmenity{}, false, err
	}

	deleted := header[0] == 1
	propertyID := int(int32(binary.LittleEndian.Uint32(header[1:5])))
	amenityID := int(int32(binary.LittleEndian.Uint32(header[5:9])))
	size := binary.LittleEndian.Uint32(header[9:13])
	payload := make([]byte, size)
	if _, err := io.ReadFull(file, payload); err != nil {
		return domain.PropertyAmenity{}, false, err
	}
	if deleted {
		return domain.PropertyAmenity{}, true, nil
	}

	item, err := decodePropertyAmenityPayload(payload)
	if err != nil {
		return domain.PropertyAmenity{}, false, err
	}
	item.PropertyID = propertyID
	item.AmenityID = amenityID
	return item, false, nil
}

func encodePropertyAmenityPayload(item domain.PropertyAmenity) []byte {
	createdAt := []byte(item.CreatedAt)
	payload := make([]byte, 5+len(createdAt))
	if item.Active {
		payload[0] = 1
	}
	binary.LittleEndian.PutUint32(payload[1:5], uint32(len(createdAt)))
	copy(payload[5:], createdAt)
	return payload
}

func decodePropertyAmenityPayload(payload []byte) (domain.PropertyAmenity, error) {
	if len(payload) < 5 {
		return domain.PropertyAmenity{}, domain.ErrInvalidEntity
	}
	size := int(binary.LittleEndian.Uint32(payload[1:5]))
	if size < 0 || 5+size > len(payload) {
		return domain.PropertyAmenity{}, domain.ErrInvalidEntity
	}
	return domain.PropertyAmenity{
		CreatedAt: string(payload[5 : 5+size]),
		Active:    payload[0] == 1,
	}, nil
}

func propertyAmenityOrderKey(propertyID, amenityID int) int64 {
	return int64(uint64(uint32(propertyID))<<32 | uint64(uint32(amenityID)))
}

var _ propertyamenityuc.Repository = (*PropertyAmenityFileRepository)(nil)
