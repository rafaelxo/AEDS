package repository

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"sync"
)

type multiIndexEntry struct {
	Key    int
	Values []int64
}

type multiExtensibleHashIndex struct {
	core *extensibleHashCore[[]int64]
	path string
	mu   sync.Mutex
}

func newMultiExtensibleHashIndex(path string, bucketSize int) (*multiExtensibleHashIndex, error) {
	h := &multiExtensibleHashIndex{
		core: newExtensibleHashCore[[]int64](bucketSize),
		path: path,
	}
	if err := h.ensureFile(); err != nil {
		return nil, err
	}
	if err := h.loadFromFile(); err != nil {
		if err := h.persistToFile(); err != nil {
			return nil, err
		}
	}
	return h, nil
}

func (h *multiExtensibleHashIndex) ensureFile() error {
	if err := os.MkdirAll(filepath.Dir(h.path), 0o755); err != nil {
		return err
	}
	file, err := os.OpenFile(h.path, os.O_CREATE|os.O_RDWR, 0o644)
	if err != nil {
		return err
	}
	return file.Close()
}

func (h *multiExtensibleHashIndex) Reset() {
	h.mu.Lock()
	defer h.mu.Unlock()
	h.core.Reset()
}

func (h *multiExtensibleHashIndex) Snapshot() []multiIndexEntry {
	h.mu.Lock()
	defer h.mu.Unlock()
	return h.snapshotLocked()
}

func (h *multiExtensibleHashIndex) snapshotLocked() []multiIndexEntry {
	entries := make([]multiIndexEntry, 0)
	for _, bucket := range h.core.buckets {
		for key, values := range bucket.entries {
			copied := append([]int64(nil), values...)
			entries = append(entries, multiIndexEntry{Key: key, Values: copied})
		}
	}
	return entries
}

func (h *multiExtensibleHashIndex) Load(entries []multiIndexEntry) {
	h.mu.Lock()
	defer h.mu.Unlock()
	h.core.Reset()
	for _, entry := range entries {
		for _, value := range entry.Values {
			h.insertLocked(entry.Key, value)
		}
	}
}

func (h *multiExtensibleHashIndex) Get(key int) ([]int64, bool) {
	h.mu.Lock()
	defer h.mu.Unlock()
	values, ok := h.core.Get(key)
	if !ok {
		return nil, false
	}
	return append([]int64(nil), values...), true
}

func (h *multiExtensibleHashIndex) Insert(key int, value int64) {
	h.mu.Lock()
	defer h.mu.Unlock()
	h.insertLocked(key, value)
}

func (h *multiExtensibleHashIndex) insertLocked(key int, value int64) {
	values, ok := h.core.Get(key)
	if !ok {
		h.core.Set(key, []int64{value})
		return
	}
	for _, current := range values {
		if current == value {
			return
		}
	}
	updated := append(append([]int64(nil), values...), value)
	h.core.Set(key, updated)
}

func (h *multiExtensibleHashIndex) Delete(key int, value int64) {
	h.mu.Lock()
	defer h.mu.Unlock()
	values, ok := h.core.Get(key)
	if !ok {
		return
	}
	filtered := make([]int64, 0, len(values))
	for _, current := range values {
		if current != value {
			filtered = append(filtered, current)
		}
	}
	if len(filtered) == 0 {
		h.core.Delete(key)
		return
	}
	h.core.Set(key, filtered)
}

func (h *multiExtensibleHashIndex) Stats() HashIndexStats {
	h.mu.Lock()
	defer h.mu.Unlock()
	return h.core.Stats(func(values []int64) int { return len(values) })
}

func (h *multiExtensibleHashIndex) persistToFile() error {
	h.mu.Lock()
	defer h.mu.Unlock()
	entries := h.snapshotLocked()
	sort.Slice(entries, func(i, j int) bool { return entries[i].Key < entries[j].Key })
	tempPath := h.path + ".tmp"
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

	if _, err := file.Write([]byte{indexVersion}); err != nil {
		return cleanup(err)
	}

	var countBuf [4]byte
	binary.LittleEndian.PutUint32(countBuf[:], uint32(len(entries)))
	if _, err := file.Write(countBuf[:]); err != nil {
		return cleanup(err)
	}

	for _, entry := range entries {
		var keyBuf [4]byte
		binary.LittleEndian.PutUint32(keyBuf[:], uint32(int32(entry.Key)))
		if _, err := file.Write(keyBuf[:]); err != nil {
			return cleanup(err)
		}

		var valueCount [4]byte
		binary.LittleEndian.PutUint32(valueCount[:], uint32(len(entry.Values)))
		if _, err := file.Write(valueCount[:]); err != nil {
			return cleanup(err)
		}

		for _, value := range entry.Values {
			var valueBuf [8]byte
			binary.LittleEndian.PutUint64(valueBuf[:], uint64(value))
			if _, err := file.Write(valueBuf[:]); err != nil {
				return cleanup(err)
			}
		}
	}

	if err := file.Sync(); err != nil {
		return cleanup(err)
	}
	if err := file.Close(); err != nil {
		_ = os.Remove(tempPath)
		return err
	}
	if err := os.Remove(h.path); err != nil && !os.IsNotExist(err) {
		_ = os.Remove(tempPath)
		return err
	}
	return os.Rename(tempPath, h.path)
}

func (h *multiExtensibleHashIndex) loadFromFile() error {
	file, err := os.OpenFile(h.path, os.O_RDONLY, 0o644)
	if err != nil {
		return err
	}
	defer file.Close()

	buf := make([]byte, indexHeaderSize)
	if _, err := io.ReadFull(file, buf); err != nil {
		return err
	}
	if buf[0] != indexVersion {
		return fmt.Errorf("invalid relation index version")
	}

	count := binary.LittleEndian.Uint32(buf[1:5])
	entries := make([]multiIndexEntry, 0, count)
	for i := uint32(0); i < count; i++ {
		var keyBuf [4]byte
		if _, err := io.ReadFull(file, keyBuf[:]); err != nil {
			return err
		}
		var valueCountBuf [4]byte
		if _, err := io.ReadFull(file, valueCountBuf[:]); err != nil {
			return err
		}

		valueCount := binary.LittleEndian.Uint32(valueCountBuf[:])
		values := make([]int64, 0, valueCount)
		for j := uint32(0); j < valueCount; j++ {
			var valueBuf [8]byte
			if _, err := io.ReadFull(file, valueBuf[:]); err != nil {
				return err
			}
			values = append(values, int64(binary.LittleEndian.Uint64(valueBuf[:])))
		}
		entries = append(entries, multiIndexEntry{Key: int(int32(binary.LittleEndian.Uint32(keyBuf[:]))), Values: values})
	}

	h.Load(entries)
	return nil
}
