package domain

import "errors"

var (
	ErrNotFound      = errors.New("Registro não encontrado")
	ErrInvalidEntity = errors.New("Entidade inválida")
	ErrAlreadyExists = errors.New("Registro já existe")
	ErrEmailInUse    = errors.New("E-mail já cadastrado")
)
