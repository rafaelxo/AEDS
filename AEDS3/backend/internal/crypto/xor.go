package crypto

import "encoding/hex"

var DefaultKey = "hostly-2026"

func Encrypt(text, key string) string {
	if key == "" {
		return text
	}

	b := []byte(text)
	k := []byte(key)
	for i := range b {
		b[i] ^= k[i%len(k)]
	}

	return hex.EncodeToString(b)
}

func Decrypt(cipherHex, key string) string {
	if key == "" {
		return cipherHex
	}

	b, err := hex.DecodeString(cipherHex)
	if err != nil {
		return cipherHex
	}

	k := []byte(key)
	for i := range b {
		b[i] ^= k[i%len(k)]
	}

	return string(b)
}
