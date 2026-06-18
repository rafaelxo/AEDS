package compression

import (
	"bytes"
	"encoding/binary"
	"errors"
	"io"
)

const archiveMagic = uint32(0x484C5442)

type ArchiveEntry struct {
	Name string
	Data []byte
}

func Pack(entries []ArchiveEntry) ([]byte, error) {
	var buf bytes.Buffer
	if err := binary.Write(&buf, binary.BigEndian, archiveMagic); err != nil {
		return nil, err
	}
	if err := binary.Write(&buf, binary.BigEndian, uint16(len(entries))); err != nil {
		return nil, err
	}
	for _, e := range entries {
		nameBytes := []byte(e.Name)
		if err := binary.Write(&buf, binary.BigEndian, uint16(len(nameBytes))); err != nil {
			return nil, err
		}
		buf.Write(nameBytes)
		if err := binary.Write(&buf, binary.BigEndian, uint32(len(e.Data))); err != nil {
			return nil, err
		}
		buf.Write(e.Data)
	}
	return buf.Bytes(), nil
}

func Unpack(data []byte) ([]ArchiveEntry, error) {
	r := bytes.NewReader(data)

	var magic uint32
	if err := binary.Read(r, binary.BigEndian, &magic); err != nil || magic != archiveMagic {
		return nil, errors.New("archive: magic inválido — arquivo corrompido ou incompatível")
	}

	var count uint16
	if err := binary.Read(r, binary.BigEndian, &count); err != nil {
		return nil, errors.New("archive: cabeçalho inválido")
	}

	entries := make([]ArchiveEntry, 0, count)
	for i := 0; i < int(count); i++ {
		var nameLen uint16
		if err := binary.Read(r, binary.BigEndian, &nameLen); err != nil {
			return nil, errors.New("archive: nameLen inválido")
		}
		nameBytes := make([]byte, nameLen)
		if _, err := io.ReadFull(r, nameBytes); err != nil {
			return nil, errors.New("archive: nome inválido")
		}
		var dataLen uint32
		if err := binary.Read(r, binary.BigEndian, &dataLen); err != nil {
			return nil, errors.New("archive: dataLen inválido")
		}
		dataBytes := make([]byte, dataLen)
		if _, err := io.ReadFull(r, dataBytes); err != nil {
			return nil, errors.New("archive: dados incompletos")
		}
		entries = append(entries, ArchiveEntry{Name: string(nameBytes), Data: dataBytes})
	}
	return entries, nil
}
