package repository

import "math/bits"

type indexEntry struct {
	Key    int
	Offset int64
}

type HashIndexStats struct {
	GlobalDepth int `json:"globalDepth"`
	Buckets     int `json:"buckets"`
	Entries     int `json:"entries"`
}

type hashBucket[V any] struct {
	localDepth int
	entries    map[int]V
}

type extensibleHashCore[V any] struct {
	bucketSize   int
	globalDepth  int
	directory    []int
	nextBucketID int
	buckets      map[int]*hashBucket[V]
}

func newExtensibleHashCore[V any](bucketSize int) *extensibleHashCore[V] {
	if bucketSize < 2 {
		bucketSize = 4
	}
	h := &extensibleHashCore[V]{
		bucketSize:   bucketSize,
		globalDepth:  1,
		directory:    make([]int, 2),
		nextBucketID: 2,
		buckets: map[int]*hashBucket[V]{
			0: {localDepth: 1, entries: make(map[int]V)},
			1: {localDepth: 1, entries: make(map[int]V)},
		},
	}
	h.directory[0] = 0
	h.directory[1] = 1
	return h
}

func (h *extensibleHashCore[V]) Reset() {
	n := newExtensibleHashCore[V](h.bucketSize)
	h.globalDepth = n.globalDepth
	h.directory = n.directory
	h.nextBucketID = n.nextBucketID
	h.buckets = n.buckets
}

func (h *extensibleHashCore[V]) Get(key int) (V, bool) {
	bucket := h.bucketForKey(key)
	value, ok := bucket.entries[key]
	return value, ok
}

func (h *extensibleHashCore[V]) Delete(key int) {
	bucket := h.bucketForKey(key)
	delete(bucket.entries, key)
}

func (h *extensibleHashCore[V]) Set(key int, value V) {
	for {
		bucket := h.bucketForKey(key)
		if _, exists := bucket.entries[key]; exists {
			bucket.entries[key] = value
			return
		}
		if len(bucket.entries) < h.bucketSize {
			bucket.entries[key] = value
			return
		}
		h.splitBucketForKey(key)
	}
}

func (h *extensibleHashCore[V]) Stats(entryCount func(V) int) HashIndexStats {
	entries := 0
	for _, b := range h.buckets {
		for _, value := range b.entries {
			entries += entryCount(value)
		}
	}
	return HashIndexStats{
		GlobalDepth: h.globalDepth,
		Buckets:     len(h.buckets),
		Entries:     entries,
	}
}

func (h *extensibleHashCore[V]) bucketForKey(key int) *hashBucket[V] {
	dirIndex := h.directoryIndex(key)
	bucketID := h.directory[dirIndex]
	return h.buckets[bucketID]
}

func (h *extensibleHashCore[V]) directoryIndex(key int) int {
	mask := (1 << h.globalDepth) - 1
	return int(uint32(key)) & mask
}

func (h *extensibleHashCore[V]) splitBucketForKey(key int) {
	dirIndex := h.directoryIndex(key)
	oldBucketID := h.directory[dirIndex]
	oldBucket := h.buckets[oldBucketID]

	if oldBucket.localDepth == h.globalDepth {
		h.growDirectory()
	}

	oldBucket.localDepth++
	newBucketID := h.nextBucketID
	h.nextBucketID++
	newBucket := &hashBucket[V]{
		localDepth: oldBucket.localDepth,
		entries:    make(map[int]V),
	}
	h.buckets[newBucketID] = newBucket

	discriminatorBit := 1 << (oldBucket.localDepth - 1)
	for i, bID := range h.directory {
		if bID != oldBucketID {
			continue
		}
		if (i & discriminatorBit) != 0 {
			h.directory[i] = newBucketID
		}
	}

	for entryKey, entryValue := range oldBucket.entries {
		idx := h.directoryIndex(entryKey)
		targetBucketID := h.directory[idx]
		if targetBucketID == newBucketID {
			newBucket.entries[entryKey] = entryValue
			delete(oldBucket.entries, entryKey)
		}
	}
}

func (h *extensibleHashCore[V]) growDirectory() {
	old := h.directory
	h.globalDepth++
	h.directory = make([]int, 1<<h.globalDepth)
	for i := range h.directory {
		h.directory[i] = old[i%(1<<(h.globalDepth-1))]
	}
}

type extensibleHashIndex struct {
	core *extensibleHashCore[int64]
}

func newExtensibleHashIndex(bucketSize int) *extensibleHashIndex {
	return &extensibleHashIndex{core: newExtensibleHashCore[int64](bucketSize)}
}

func (h *extensibleHashIndex) Reset() {
	h.core.Reset()
}

func (h *extensibleHashIndex) Snapshot() []indexEntry {
	entries := make([]indexEntry, 0)
	for _, bucket := range h.core.buckets {
		for key, offset := range bucket.entries {
			entries = append(entries, indexEntry{Key: key, Offset: offset})
		}
	}
	return entries
}

func (h *extensibleHashIndex) Load(entries []indexEntry) {
	h.Reset()
	for _, entry := range entries {
		h.Insert(entry.Key, entry.Offset)
	}
}

func (h *extensibleHashIndex) Get(key int) (int64, bool) {
	return h.core.Get(key)
}

func (h *extensibleHashIndex) Delete(key int) {
	h.core.Delete(key)
}

func (h *extensibleHashIndex) Insert(key int, offset int64) {
	h.core.Set(key, offset)
}

func (h *extensibleHashIndex) Stats() HashIndexStats {
	return h.core.Stats(func(_ int64) int { return 1 })
}

func (h *extensibleHashIndex) RequiredBits() int {
	if h.core.globalDepth <= 1 {
		return 1
	}
	return bits.Len(uint(h.core.globalDepth))
}
