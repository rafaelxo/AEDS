package compression

import (
	"bytes"
	"encoding/binary"
	"errors"
)

const maxCodes = 1 << 16

func lzwEncode(data []byte) ([]byte, error) {
	dict := make(map[string]uint16, 512)
	for i := 0; i < 256; i++ {
		dict[string([]byte{byte(i)})] = uint16(i)
	}
	nextCode := 256

	codes := make([]uint16, 0, len(data)/2+1)
	var w []byte
	for _, c := range data {
		wc := append(w, c)
		if _, ok := dict[string(wc)]; ok {
			w = wc
			continue
		}
		codes = append(codes, dict[string(w)])
		if nextCode < maxCodes {
			dict[string(wc)] = uint16(nextCode)
			nextCode++
		}
		w = []byte{c}
	}
	if len(w) > 0 {
		codes = append(codes, dict[string(w)])
	}

	var buf bytes.Buffer
	if err := binary.Write(&buf, binary.BigEndian, uint32(len(codes))); err != nil {
		return nil, err
	}
	for _, code := range codes {
		if err := binary.Write(&buf, binary.BigEndian, code); err != nil {
			return nil, err
		}
	}
	return buf.Bytes(), nil
}

func lzwDecode(data []byte) ([]byte, error) {
	r := bytes.NewReader(data)

	var count uint32
	if err := binary.Read(r, binary.BigEndian, &count); err != nil {
		return nil, errors.New("lzw: cabeçalho inválido")
	}
	if count == 0 {
		return []byte{}, nil
	}

	dict := make([][]byte, 0, maxCodes)
	for i := 0; i < 256; i++ {
		dict = append(dict, []byte{byte(i)})
	}

	readCode := func() (uint16, error) {
		var code uint16
		err := binary.Read(r, binary.BigEndian, &code)
		return code, err
	}

	first, err := readCode()
	if err != nil || int(first) >= len(dict) {
		return nil, errors.New("lzw: fluxo de códigos inválido")
	}
	prev := dict[first]
	out := append([]byte(nil), prev...)

	for i := uint32(1); i < count; i++ {
		code, err := readCode()
		if err != nil {
			return nil, errors.New("lzw: fluxo de códigos incompleto")
		}

		var entry []byte
		switch {
		case int(code) < len(dict):
			entry = dict[code]
		case int(code) == len(dict):
			entry = append(append([]byte(nil), prev...), prev[0])
		default:
			return nil, errors.New("lzw: código fora de alcance")
		}

		out = append(out, entry...)
		if len(dict) < maxCodes {
			dict = append(dict, append(append([]byte(nil), prev...), entry[0]))
		}
		prev = entry
	}
	return out, nil
}
