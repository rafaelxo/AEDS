package reservation

import (
	"backend/internal/domain"
	paymentuc "backend/internal/usecase/payment"
)

type ListFilter struct {
	PropertyID *int
	UserID     *int
	Role       string
	Status     string
	PeriodFrom string
	PeriodTo   string
	Query      string
}

type Service interface {
	Create(item domain.Reservation) (domain.Reservation, error)
	GetByID(id int) (domain.Reservation, error)
	GetAll() ([]domain.Reservation, error)
	GetByPropertyID(propertyID int) ([]domain.Reservation, error)
	GetByGuestID(guestID int) ([]domain.Reservation, error)
	GetByHostID(hostID int) ([]domain.Reservation, error)
	GetByHostWithProperties(hostID int) (map[int][]domain.Reservation, error)
	List(filter ListFilter) ([]domain.Reservation, error)
	Update(id int, item ReservationUpdate) (domain.Reservation, error)
	Confirm(id int, input ConfirmReservationInput) (domain.Reservation, error)
	Delete(id int) error
}

type service struct {
	repo         Repository
	propertyRepo PropertyReader
	guestRepo    GuestReader
	paymentGate  paymentuc.Gateway
}

func NewService(repo Repository, propertyRepo PropertyReader, guestRepo GuestReader, paymentGate paymentuc.Gateway) Service {
	return &service{repo: repo, propertyRepo: propertyRepo, guestRepo: guestRepo, paymentGate: paymentGate}
}
