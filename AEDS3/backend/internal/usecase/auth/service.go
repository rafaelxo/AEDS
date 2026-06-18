package auth

import "backend/internal/domain"

type UserService interface {
	Create(item domain.User) (domain.User, error)
	GetByID(id int) (domain.User, error)
	GetByEmail(email string) (domain.User, error)
	SeedAdmin(name string, email string, password string) (domain.User, error)
	Delete(id int) error
}

type PropertyService interface {
	Create(item domain.Property) (domain.Property, error)
	Delete(id int) error
}

type RegisterInput struct {
	Name            string
	Email           string
	Phone           string
	Password        string
	CreateAsHost    bool
	InitialProperty *domain.Property
}

type LoginInput struct {
	Email    string
	Password string
}

type Session struct {
	Token string      `json:"token"`
	User  domain.User `json:"usuario"`
}

type Service interface {
	Register(input RegisterInput) (Session, error)
	Login(input LoginInput) (Session, error)
	GetUserByToken(token string) (domain.User, error)
	SeedDefaultAdmin() (domain.User, error)
}
