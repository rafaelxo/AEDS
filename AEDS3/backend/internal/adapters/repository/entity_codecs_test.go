package repository

import (
	"bytes"
	"os"
	"path/filepath"
	"testing"

	"backend/internal/domain"
)

func TestUserCodecEncryptsPasswordAtRest(t *testing.T) {
	user := domain.User{
		ID:       1,
		Name:     "Admin",
		Email:    "admin@hostly.local",
		Password: "admin123",
		Type:     domain.UserTypeAdmin,
		Active:   true,
	}

	payload, err := encodeUser(user)
	if err != nil {
		t.Fatal(err)
	}

	if bytes.Contains(payload, []byte(user.Password)) {
		t.Fatal("encoded user payload should not contain the plaintext password")
	}

	decoded, err := decodeUser(payload, user.ID)
	if err != nil {
		t.Fatal(err)
	}

	if decoded.Password != user.Password {
		t.Fatalf("decoded password = %q, want %q", decoded.Password, user.Password)
	}
}

func TestUserRepositoryStoresEncryptedPasswordInBinaryFile(t *testing.T) {
	dbPath := filepath.Join(t.TempDir(), "usuarios.db")
	repo, err := NewUserFileRepository(dbPath)
	if err != nil {
		t.Fatal(err)
	}

	const password = "admin123"
	created, err := repo.Create(domain.User{
		Name:     "Admin",
		Email:    "admin@hostly.local",
		Password: password,
		Type:     domain.UserTypeAdmin,
		Active:   true,
	})
	if err != nil {
		t.Fatal(err)
	}

	raw, err := os.ReadFile(dbPath)
	if err != nil {
		t.Fatal(err)
	}
	if bytes.Contains(raw, []byte(password)) {
		t.Fatal("usuarios.db should not contain the plaintext password")
	}

	loaded, err := repo.GetByID(created.ID)
	if err != nil {
		t.Fatal(err)
	}
	if loaded.Password != password {
		t.Fatalf("loaded password = %q, want %q", loaded.Password, password)
	}
}
