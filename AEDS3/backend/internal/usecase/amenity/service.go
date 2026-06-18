package amenity

import "backend/internal/domain"

type Service interface {
	Create(item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error)
	GetByID(id int) (domain.AmenityCatalogItem, error)
	GetAll() ([]domain.AmenityCatalogItem, error)
	Update(id int, item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error)
	Delete(id int) error
	GetAllActive() ([]domain.AmenityCatalogItem, error)
	SeedCommonAmenities() error
}

type RelationCleaner interface {
	DeleteByAmenityID(amenityID int) error
}

type service struct {
	repo    Repository
	cleaner RelationCleaner
}

func NewService(repo Repository, cleaner RelationCleaner) Service {
	return &service{repo: repo, cleaner: cleaner}
}
