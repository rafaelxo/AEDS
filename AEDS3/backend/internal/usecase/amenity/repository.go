package amenity

import "backend/internal/domain"

type Repository interface {
	Create(item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error)
	GetByID(id int) (domain.AmenityCatalogItem, error)
	GetAll() ([]domain.AmenityCatalogItem, error)
	Update(id int, item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error)
	Delete(id int) error
}
