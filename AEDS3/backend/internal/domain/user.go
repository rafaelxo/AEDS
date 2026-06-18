package domain

import "strings"

type UserType string

const (
	UserTypeAdmin UserType = "ADMIN"
	UserTypeHost  UserType = "ANFITRIAO"
	UserTypeGuest UserType = "HOSPEDE"
)

type User struct {
	ID       int      `json:"idUsuario"`
	Name     string   `json:"nome"`
	Email    string   `json:"email"`
	Phone    string   `json:"telefone"`
	Password string   `json:"-"`
	Type     UserType `json:"tipo"`
	Active   bool     `json:"ativo"`
}

func (u User) Validate() error {
	if strings.TrimSpace(u.Name) == "" || strings.TrimSpace(u.Email) == "" {
		return ErrInvalidEntity
	}
	if u.Type != UserTypeAdmin && u.Type != UserTypeHost && u.Type != UserTypeGuest {
		return ErrInvalidEntity
	}
	return nil
}
