package user

import "backend/internal/domain"

type Service interface {
	Create(item domain.User) (domain.User, error)
	GetByID(id int) (domain.User, error)
	GetByEmail(email string) (domain.User, error)
	GetAllHosts() ([]domain.User, error)
	GetAll() ([]domain.User, error)
	List(filter ListFilter) ([]domain.User, error)
	Update(id int, item domain.User) (domain.User, error)
	Patch(id int, p UserPatch) (domain.User, error)
	Delete(id int) error
	SeedAdmin(name string, email string, password string) (domain.User, error)
}

type service struct {
	repo Repository
}

func NewService(repo Repository) Service {
	return &service{repo: repo}
}
