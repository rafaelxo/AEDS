package reservation

import "backend/internal/domain"

type Repository interface {
	Create(item domain.Reservation) (domain.Reservation, error)
	GetByID(id int) (domain.Reservation, error)
	GetAll() ([]domain.Reservation, error)
	GetByPropertyID(propertyID int) ([]domain.Reservation, error)
	GetByGuestID(guestID int) ([]domain.Reservation, error)
	Update(id int, item domain.Reservation) (domain.Reservation, error)
	Delete(id int) error
}

type PropertyReader interface {
	GetByID(id int) (domain.Property, error)
	GetAll() ([]domain.Property, error)
	GetByOwnerID(ownerID int) ([]domain.Property, error)
}

type GuestReader interface {
	GetByID(id int) (domain.User, error)
}
