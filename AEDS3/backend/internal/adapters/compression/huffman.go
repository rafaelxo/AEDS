package compression

import (
	"bytes"
	"container/heap"
	"encoding/binary"
	"errors"
	"io"
	"sort"
)

type huffNode struct {
	sym   byte
	freq  int
	left  *huffNode
	right *huffNode
}

func (n *huffNode) isLeaf() bool { return n.left == nil && n.right == nil }

type huffHeap []*huffNode

func (h huffHeap) Len() int { return len(h) }
func (h huffHeap) Less(i, j int) bool {
	if h[i].freq != h[j].freq {
		return h[i].freq < h[j].freq
	}
	return h[i].sym < h[j].sym
}
func (h huffHeap) Swap(i, j int) { h[i], h[j] = h[j], h[i] }
func (h *huffHeap) Push(x any)   { *h = append(*h, x.(*huffNode)) }
func (h *huffHeap) Pop() any {
	old := *h
	n := len(old)
	node := old[n-1]
	*h = old[:n-1]
	return node
}

func sortedSymbols(freq map[byte]int) []int {
	syms := make([]int, 0, len(freq))
	for s := range freq {
		syms = append(syms, int(s))
	}
	sort.Ints(syms)
	return syms
}

func buildTree(freq map[byte]int) *huffNode {
	h := &huffHeap{}
	heap.Init(h)
	for _, s := range sortedSymbols(freq) {
		heap.Push(h, &huffNode{sym: byte(s), freq: freq[byte(s)]})
	}
	if h.Len() == 0 {
		return nil
	}
	if h.Len() == 1 {
		only := heap.Pop(h).(*huffNode)
		return &huffNode{freq: only.freq, left: only}
	}
	for h.Len() > 1 {
		a := heap.Pop(h).(*huffNode)
		b := heap.Pop(h).(*huffNode)
		heap.Push(h, &huffNode{freq: a.freq + b.freq, left: a, right: b})
	}
	return heap.Pop(h).(*huffNode)
}

func buildCodes(node *huffNode, prefix string, codes map[byte]string) {
	if node == nil {
		return
	}
	if node.isLeaf() {
		codes[node.sym] = prefix
		return
	}
	buildCodes(node.left, prefix+"0", codes)
	buildCodes(node.right, prefix+"1", codes)
}

func huffmanEncode(data []byte) ([]byte, error) {
	freq := make(map[byte]int)
	for _, b := range data {
		freq[b]++
	}

	var buf bytes.Buffer
	if err := binary.Write(&buf, binary.BigEndian, uint16(len(freq))); err != nil {
		return nil, err
	}
	for _, s := range sortedSymbols(freq) {
		buf.WriteByte(byte(s))
		if err := binary.Write(&buf, binary.BigEndian, uint32(freq[byte(s)])); err != nil {
			return nil, err
		}
	}

	if len(data) == 0 {
		buf.WriteByte(0)
		return buf.Bytes(), nil
	}

	codes := make(map[byte]string)
	buildCodes(buildTree(freq), "", codes)

	var (
		body  bytes.Buffer
		cur   byte
		nBits uint8
	)
	for _, b := range data {
		for _, c := range codes[b] {
			cur <<= 1
			if c == '1' {
				cur |= 1
			}
			nBits++
			if nBits == 8 {
				body.WriteByte(cur)
				cur, nBits = 0, 0
			}
		}
	}
	var padding byte
	if nBits > 0 {
		padding = 8 - nBits
		cur <<= padding
		body.WriteByte(cur)
	}
	buf.WriteByte(padding)
	buf.Write(body.Bytes())
	return buf.Bytes(), nil
}

func huffmanDecode(data []byte) ([]byte, error) {
	r := bytes.NewReader(data)

	var numSymbols uint16
	if err := binary.Read(r, binary.BigEndian, &numSymbols); err != nil {
		return nil, errors.New("huffman: cabeçalho inválido")
	}

	freq := make(map[byte]int, numSymbols)
	total := 0
	for i := 0; i < int(numSymbols); i++ {
		sym, err := r.ReadByte()
		if err != nil {
			return nil, errors.New("huffman: tabela de frequência inválida")
		}
		var f uint32
		if err := binary.Read(r, binary.BigEndian, &f); err != nil {
			return nil, errors.New("huffman: tabela de frequência inválida")
		}
		freq[sym] = int(f)
		total += int(f)
	}

	if _, err := r.ReadByte(); err != nil {
		return nil, errors.New("huffman: padding ausente")
	}

	if numSymbols == 0 || total == 0 {
		return []byte{}, nil
	}

	tree := buildTree(freq)
	body, err := io.ReadAll(r)
	if err != nil {
		return nil, err
	}

	out := make([]byte, 0, total)
	node := tree
	for _, bb := range body {
		for bit := 7; bit >= 0 && len(out) < total; bit-- {
			if (bb>>uint(bit))&1 == 1 {
				node = node.right
			} else {
				node = node.left
			}
			if node == nil {
				return nil, errors.New("huffman: bitstream corrompido")
			}
			if node.isLeaf() {
				out = append(out, node.sym)
				node = tree
			}
		}
	}
	if len(out) != total {
		return nil, errors.New("huffman: dados incompletos")
	}
	return out, nil
}
