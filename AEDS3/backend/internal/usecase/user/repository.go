package user

import "backend/internal/domain"

type Repository interface {
	Create(item domain.User) (domain.User, error)
	GetByID(id int) (domain.User, error)
	GetByEmail(email string) (domain.User, error)
	GetAll() ([]domain.User, error)
	Update(id int, item domain.User) (domain.User, error)
	Delete(id int) error
}
