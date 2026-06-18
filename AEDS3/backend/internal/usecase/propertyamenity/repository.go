package propertyamenity

import "backend/internal/domain"

type Repository interface {
	Create(item domain.PropertyAmenity) (domain.PropertyAmenity, error)
	Get(propertyID, amenityID int) (domain.PropertyAmenity, error)
	GetByPropertyID(propertyID int) ([]domain.PropertyAmenity, error)
	GetByPropertyIDOrderedByAmenityID(propertyID int) ([]domain.PropertyAmenity, error)
	GetByAmenityID(amenityID int) ([]domain.PropertyAmenity, error)
	Delete(propertyID, amenityID int) error
	DeleteByPropertyID(propertyID int) error
	DeleteByAmenityID(amenityID int) error
}

type PropertyReader interface {
	GetByID(id int) (domain.Property, error)
}

type AmenityReader interface {
	GetByID(id int) (domain.AmenityCatalogItem, error)
	GetAll() ([]domain.AmenityCatalogItem, error)
}
