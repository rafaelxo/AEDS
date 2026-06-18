package repository

import (
	"backend/internal/domain"
	amenityuc "backend/internal/usecase/amenity"
)

type AmenityFileRepository struct {
	store *binaryEntityStore[domain.AmenityCatalogItem]
}

func NewAmenityFileRepository(path string) (*AmenityFileRepository, error) {
	store, err := newBinaryEntityStore(
		path,
		func(a domain.AmenityCatalogItem) int { return a.ID },
		func(a *domain.AmenityCatalogItem, id int) { a.ID = id },
		amenityPayloadCodec(),
	)
	if err != nil {
		return nil, err
	}
	return &AmenityFileRepository{store: store}, nil
}

func (r *AmenityFileRepository) Create(item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error) {
	return r.store.Create(item)
}

func (r *AmenityFileRepository) GetByID(id int) (domain.AmenityCatalogItem, error) {
	return r.store.GetByID(id)
}

func (r *AmenityFileRepository) GetAll() ([]domain.AmenityCatalogItem, error) {
	return r.store.GetAll()
}

func (r *AmenityFileRepository) Update(id int, item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error) {
	return r.store.Update(id, item)
}

func (r *AmenityFileRepository) Delete(id int) error {
	return r.store.Delete(id)
}

var _ amenityuc.Repository = (*AmenityFileRepository)(nil)
