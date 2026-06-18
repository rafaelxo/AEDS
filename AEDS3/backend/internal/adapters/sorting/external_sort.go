package sorting

import (
	"bufio"
	"container/heap"
	"encoding/binary"
	"encoding/json"
	"io"
	"math"
	"os"
	"path/filepath"
	"sort"
)

type Engine struct {
	dir     string
	runSize int
}

func NewEngine(dir string, runSize int) *Engine {
	if runSize < 1 {
		runSize = 1
	}
	return &Engine{dir: dir, runSize: runSize}
}

type record struct {
	key     float64
	id      int32
	payload []byte
}

func less(a, b record, ascending bool) bool {
	if a.key != b.key {
		if ascending {
			return a.key < b.key
		}
		return a.key > b.key
	}
	return a.id < b.id
}

func SortExternal[T any](e *Engine, name string, items []T, keyFn func(T) (float64, int), ascending bool) ([]T, error) {
	if err := os.MkdirAll(e.dir, 0o755); err != nil {
		return nil, err
	}

	if err := e.removeRunFiles(name); err != nil {
		return nil, err
	}

	runPaths, err := distribute(e, name, items, keyFn, ascending)
	if err != nil {
		return nil, err
	}

	return merge[T](e, name, runPaths, ascending, len(items))
}

func distribute[T any](e *Engine, name string, items []T, keyFn func(T) (float64, int), ascending bool) ([]string, error) {
	paths := make([]string, 0)

	for start := 0; start < len(items); start += e.runSize {
		end := min(start+e.runSize, len(items))

		chunk := make([]record, 0, end-start)
		for _, item := range items[start:end] {
			key, id := keyFn(item)
			payload, err := json.Marshal(item)
			if err != nil {
				return nil, err
			}
			chunk = append(chunk, record{key: key, id: int32(id), payload: payload})
		}

		sort.Slice(chunk, func(i, j int) bool { return less(chunk[i], chunk[j], ascending) })

		path := filepath.Join(e.dir, name+".sort.run."+itoa(len(paths))+".bin")
		if err := writeRun(path, chunk); err != nil {
			return nil, err
		}
		paths = append(paths, path)
	}

	return paths, nil
}

func merge[T any](e *Engine, name string, runPaths []string, ascending bool, total int) ([]T, error) {
	outputPath := filepath.Join(e.dir, name+".sorted.bin")
	outFile, err := os.OpenFile(outputPath, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0o644)
	if err != nil {
		return nil, err
	}
	out := bufio.NewWriter(outFile)
	var header [4]byte
	binary.LittleEndian.PutUint32(header[:], uint32(total))
	if _, err := out.Write(header[:]); err != nil {
		_ = outFile.Close()
		return nil, err
	}

	readers := make([]*bufio.Reader, len(runPaths))
	files := make([]*os.File, len(runPaths))
	defer func() {
		for _, f := range files {
			if f != nil {
				_ = f.Close()
			}
		}
	}()

	pq := &recordHeap{ascending: ascending}
	for i, path := range runPaths {
		f, err := os.Open(path)
		if err != nil {
			_ = outFile.Close()
			return nil, err
		}
		files[i] = f
		r := bufio.NewReader(f)
		readers[i] = r
		if _, err := io.ReadFull(r, header[:]); err != nil {
			_ = outFile.Close()
			return nil, err
		}
		rec, ok, err := readRecord(r)
		if err != nil {
			_ = outFile.Close()
			return nil, err
		}
		if ok {
			heap.Push(pq, heapItem{rec: rec, run: i})
		}
	}

	result := make([]T, 0, total)
	for pq.Len() > 0 {
		top := heap.Pop(pq).(heapItem)
		if err := writeRecord(out, top.rec); err != nil {
			_ = outFile.Close()
			return nil, err
		}
		var item T
		if err := json.Unmarshal(top.rec.payload, &item); err != nil {
			_ = outFile.Close()
			return nil, err
		}
		result = append(result, item)

		next, ok, err := readRecord(readers[top.run])
		if err != nil {
			_ = outFile.Close()
			return nil, err
		}
		if ok {
			heap.Push(pq, heapItem{rec: next, run: top.run})
		}
	}

	if err := out.Flush(); err != nil {
		_ = outFile.Close()
		return nil, err
	}
	return result, outFile.Close()
}

func (e *Engine) removeRunFiles(name string) error {
	matches, err := filepath.Glob(filepath.Join(e.dir, name+".sort.run.*.bin"))
	if err != nil {
		return err
	}
	for _, path := range matches {
		if err := os.Remove(path); err != nil && !os.IsNotExist(err) {
			return err
		}
	}
	return nil
}

func writeRun(path string, records []record) error {
	file, err := os.OpenFile(path, os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0o644)
	if err != nil {
		return err
	}
	w := bufio.NewWriter(file)
	var header [4]byte
	binary.LittleEndian.PutUint32(header[:], uint32(len(records)))
	if _, err := w.Write(header[:]); err != nil {
		_ = file.Close()
		return err
	}
	for _, rec := range records {
		if err := writeRecord(w, rec); err != nil {
			_ = file.Close()
			return err
		}
	}
	if err := w.Flush(); err != nil {
		_ = file.Close()
		return err
	}
	return file.Close()
}

func writeRecord(w io.Writer, rec record) error {
	var buf [16]byte
	binary.LittleEndian.PutUint64(buf[0:8], math.Float64bits(rec.key))
	binary.LittleEndian.PutUint32(buf[8:12], uint32(rec.id))
	binary.LittleEndian.PutUint32(buf[12:16], uint32(len(rec.payload)))
	if _, err := w.Write(buf[:]); err != nil {
		return err
	}
	_, err := w.Write(rec.payload)
	return err
}

func readRecord(r io.Reader) (record, bool, error) {
	var buf [16]byte
	_, err := io.ReadFull(r, buf[:])
	if err == io.EOF || err == io.ErrUnexpectedEOF {
		return record{}, false, nil
	}
	if err != nil {
		return record{}, false, err
	}
	rec := record{
		key: math.Float64frombits(binary.LittleEndian.Uint64(buf[0:8])),
		id:  int32(binary.LittleEndian.Uint32(buf[8:12])),
	}
	size := binary.LittleEndian.Uint32(buf[12:16])
	rec.payload = make([]byte, size)
	if _, err := io.ReadFull(r, rec.payload); err != nil {
		return record{}, false, err
	}
	return rec, true, nil
}

type heapItem struct {
	rec record
	run int
}

type recordHeap struct {
	items     []heapItem
	ascending bool
}

func (h recordHeap) Len() int           { return len(h.items) }
func (h recordHeap) Less(i, j int) bool { return less(h.items[i].rec, h.items[j].rec, h.ascending) }
func (h recordHeap) Swap(i, j int)      { h.items[i], h.items[j] = h.items[j], h.items[i] }
func (h *recordHeap) Push(x any)        { h.items = append(h.items, x.(heapItem)) }
func (h *recordHeap) Pop() any {
	old := h.items
	n := len(old)
	item := old[n-1]
	h.items = old[:n-1]
	return item
}

func itoa(n int) string {
	if n == 0 {
		return "0"
	}
	var digits [20]byte
	pos := len(digits)
	for n > 0 {
		pos--
		digits[pos] = byte('0' + n%10)
		n /= 10
	}
	return string(digits[pos:])
}
