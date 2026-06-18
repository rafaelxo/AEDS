package property

import "backend/internal/domain"

type ListFilter struct {
	OwnerID         *int
	City            string
	MinDailyRate    *float64
	MaxDailyRate    *float64
	Query           string
	IncludeInactive bool
	AmenityIDs      []int
}

type Service interface {
	Create(item domain.Property) (domain.Property, error)
	GetByID(id int) (domain.Property, error)
	GetAll() ([]domain.Property, error)
	GetByOwnerID(ownerID int) ([]domain.Property, error)
	List(filter ListFilter) ([]domain.Property, error)
	Update(id int, item domain.Property) (domain.Property, error)
	Patch(id int, p PropertyPatch) (domain.Property, error)
	Delete(id int) error
}

type service struct {
	repo         Repository
	userRepo     UserReader
	amenityLinks AmenityLinkManager
}

func NewService(repo Repository, userRepo UserReader, amenityLinks AmenityLinkManager) Service {
	return &service{repo: repo, userRepo: userRepo, amenityLinks: amenityLinks}
}
