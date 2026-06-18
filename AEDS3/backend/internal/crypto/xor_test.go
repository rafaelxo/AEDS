package crypto

import "testing"

func TestEncryptDecryptRoundTrip(t *testing.T) {
	plain := "admin123"

	cipher := Encrypt(plain, DefaultKey)
	if cipher == plain {
		t.Fatal("encrypted password should not match plaintext")
	}

	got := Decrypt(cipher, DefaultKey)
	if got != plain {
		t.Fatalf("Decrypt() = %q, want %q", got, plain)
	}
}

func TestEmptyKeyReturnsInput(t *testing.T) {
	input := "admin123"

	if got := Encrypt(input, ""); got != input {
		t.Fatalf("Encrypt() = %q, want %q", got, input)
	}
	if got := Decrypt(input, ""); got != input {
		t.Fatalf("Decrypt() = %q, want %q", got, input)
	}
}

func TestDecryptPlaintextFallback(t *testing.T) {
	plain := "admin123"

	if got := Decrypt(plain, DefaultKey); got != plain {
		t.Fatalf("Decrypt() = %q, want %q", got, plain)
	}
}
