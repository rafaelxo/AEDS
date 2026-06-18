package propertyamenity

import "backend/internal/domain"

type Service interface {
	Create(item domain.PropertyAmenity) (domain.PropertyAmenity, error)
	Get(propertyID, amenityID int) (domain.PropertyAmenity, error)
	ListAmenitiesByProperty(propertyID int) ([]domain.AmenityCatalogItem, error)
	ListPropertiesByAmenity(amenityID int) ([]domain.Property, error)
	ReplacePropertyAmenities(propertyID int, amenities []domain.Amenity) error
	HydratePropertyAmenities(item domain.Property) (domain.Property, error)
	HydratePropertiesAmenities(items []domain.Property) ([]domain.Property, error)
	Delete(propertyID, amenityID int) error
	DeleteByPropertyID(propertyID int) error
	DeleteByAmenityID(amenityID int) error
}

type service struct {
	repo         Repository
	propertyRepo PropertyReader
	amenityRepo  AmenityReader
}

func NewService(repo Repository, propertyRepo PropertyReader, amenityRepo AmenityReader) Service {
	return &service{repo: repo, propertyRepo: propertyRepo, amenityRepo: amenityRepo}
}
