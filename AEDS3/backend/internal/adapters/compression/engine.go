package compression

import (
	"errors"
	"strings"
)

const (
	AlgoHuffman = "huffman"
	AlgoLZW     = "lzw"
)

var errUnknownAlgo = errors.New("algoritmo desconhecido")

type Engine struct{}

func NewEngine() *Engine { return &Engine{} }

func runEncode(data []byte, algo string) ([]byte, error) {
	switch algo {
	case AlgoHuffman:
		return huffmanEncode(data)
	case AlgoLZW:
		return lzwEncode(data)
	default:
		return nil, errUnknownAlgo
	}
}

func runDecode(data []byte, algo string) ([]byte, error) {
	switch algo {
	case AlgoHuffman:
		return huffmanDecode(data)
	case AlgoLZW:
		return lzwDecode(data)
	default:
		return nil, errUnknownAlgo
	}
}

func (e *Engine) CompressRaw(data []byte, algo string) ([]byte, error) {
	return runEncode(data, strings.ToLower(strings.TrimSpace(algo)))
}

func (e *Engine) DecompressRaw(data []byte, algo string) ([]byte, error) {
	return runDecode(data, strings.ToLower(strings.TrimSpace(algo)))
}
