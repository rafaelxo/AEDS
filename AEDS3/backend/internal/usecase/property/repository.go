package property

import "backend/internal/domain"

type Repository interface {
	Create(item domain.Property) (domain.Property, error)
	GetByID(id int) (domain.Property, error)
	GetByOwnerID(ownerID int) ([]domain.Property, error)
	GetAll() ([]domain.Property, error)
	Update(id int, item domain.Property) (domain.Property, error)
	Delete(id int) error
}

type UserReader interface {
	GetByID(id int) (domain.User, error)
	Update(id int, item domain.User) (domain.User, error)
}

type AmenityLinkManager interface {
	ReplacePropertyAmenities(propertyID int, amenities []domain.Amenity) error
	HydratePropertyAmenities(item domain.Property) (domain.Property, error)
	HydratePropertiesAmenities(items []domain.Property) ([]domain.Property, error)
	DeleteByPropertyID(propertyID int) error
}
