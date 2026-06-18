package propertyamenity

import (
	"backend/internal/domain"
	"errors"
	"strings"
	"time"
)

func (s *service) Create(item domain.PropertyAmenity) (domain.PropertyAmenity, error) {
	item.Normalize()
	if item.CreatedAt == "" {
		item.CreatedAt = time.Now().Format("2006-01-02")
	}
	item.Active = true
	if err := item.Validate(); err != nil {
		return domain.PropertyAmenity{}, err
	}
	if err := s.ensureProperty(item.PropertyID); err != nil {
		return domain.PropertyAmenity{}, err
	}
	if err := s.ensureAmenity(item.AmenityID); err != nil {
		return domain.PropertyAmenity{}, err
	}
	return s.repo.Create(item)
}

func (s *service) Get(propertyID, amenityID int) (domain.PropertyAmenity, error) {
	if propertyID <= 0 || amenityID <= 0 {
		return domain.PropertyAmenity{}, domain.ErrInvalidEntity
	}
	return s.repo.Get(propertyID, amenityID)
}

func (s *service) ListAmenitiesByProperty(propertyID int) ([]domain.AmenityCatalogItem, error) {
	if propertyID <= 0 {
		return nil, domain.ErrInvalidEntity
	}
	property, err := s.activeProperty(propertyID)
	if err != nil {
		return nil, err
	}
	relations, err := s.repo.GetByPropertyIDOrderedByAmenityID(propertyID)
	if err != nil {
		return nil, err
	}
	if len(relations) == 0 && len(property.Amenities) > 0 {
		return s.legacyAmenities(property.Amenities)
	}
	items := make([]domain.AmenityCatalogItem, 0, len(relations))
	for _, rel := range relations {
		amenity, err := s.amenityRepo.GetByID(rel.AmenityID)
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				_ = s.repo.Delete(rel.PropertyID, rel.AmenityID)
				continue
			}
			return nil, err
		}
		items = append(items, amenity)
	}
	return items, nil
}

func (s *service) ListPropertiesByAmenity(amenityID int) ([]domain.Property, error) {
	if amenityID <= 0 {
		return nil, domain.ErrInvalidEntity
	}
	amenity, err := s.activeAmenity(amenityID)
	if err != nil {
		return nil, err
	}
	relations, err := s.repo.GetByAmenityID(amenityID)
	if err != nil {
		return nil, err
	}
	seen := make(map[int]struct{}, len(relations))
	items := make([]domain.Property, 0, len(relations))
	for _, rel := range relations {
		property, err := s.propertyRepo.GetByID(rel.PropertyID)
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				_ = s.repo.Delete(rel.PropertyID, rel.AmenityID)
				continue
			}
			return nil, err
		}
		if property.Active {
			seen[property.ID] = struct{}{}
			hydrated, err := s.HydratePropertyAmenities(property)
			if err != nil {
				return nil, err
			}
			items = append(items, hydrated)
		}
	}
	if lister, ok := s.propertyRepo.(interface {
		GetAll() ([]domain.Property, error)
	}); ok {
		all, err := lister.GetAll()
		if err != nil {
			return nil, err
		}
		for _, property := range all {
			if !property.Active {
				continue
			}
			if _, ok := seen[property.ID]; ok {
				continue
			}
			if propertyHasAmenity(property, amenity) {
				hydrated, err := s.HydratePropertyAmenities(property)
				if err != nil {
					hydrated = property
				}
				items = append(items, hydrated)
			}
		}
	}
	return items, nil
}

func (s *service) ReplacePropertyAmenities(propertyID int, amenities []domain.Amenity) error {
	if propertyID <= 0 {
		return domain.ErrInvalidEntity
	}
	if err := s.ensureProperty(propertyID); err != nil {
		return err
	}
	resolved, err := s.resolveAmenities(amenities)
	if err != nil {
		return err
	}
	current, err := s.repo.GetByPropertyID(propertyID)
	if err != nil {
		return err
	}

	wanted := make(map[int]struct{}, len(resolved))
	for _, amenity := range resolved {
		wanted[amenity.ID] = struct{}{}
	}
	for _, rel := range current {
		if _, ok := wanted[rel.AmenityID]; !ok {
			if err := s.repo.Delete(propertyID, rel.AmenityID); err != nil && !errors.Is(err, domain.ErrNotFound) {
				return err
			}
		}
	}
	for _, amenity := range resolved {
		if _, err := s.repo.Get(propertyID, amenity.ID); err == nil {
			continue
		} else if !errors.Is(err, domain.ErrNotFound) {
			return err
		}
		_, err := s.repo.Create(domain.PropertyAmenity{
			PropertyID: propertyID,
			AmenityID:  amenity.ID,
			CreatedAt:  time.Now().Format("2006-01-02"),
			Active:     true,
		})
		if err != nil && !errors.Is(err, domain.ErrAlreadyExists) {
			return err
		}
	}
	return nil
}

func (s *service) HydratePropertyAmenities(item domain.Property) (domain.Property, error) {
	if item.ID <= 0 {
		return item, nil
	}
	amenities, err := s.ListAmenitiesByProperty(item.ID)
	if err != nil {
		if errors.Is(err, domain.ErrNotFound) {
			return item, nil
		}
		return domain.Property{}, err
	}
	if len(amenities) == 0 {
		return item, nil
	}
	item.Amenities = catalogToPropertyAmenities(amenities)
	return item, nil
}

func (s *service) HydratePropertiesAmenities(items []domain.Property) ([]domain.Property, error) {
	out := make([]domain.Property, 0, len(items))
	for _, item := range items {
		hydrated, err := s.HydratePropertyAmenities(item)
		if err != nil {
			return nil, err
		}
		out = append(out, hydrated)
	}
	return out, nil
}

func (s *service) Delete(propertyID, amenityID int) error {
	if propertyID <= 0 || amenityID <= 0 {
		return domain.ErrInvalidEntity
	}
	return s.repo.Delete(propertyID, amenityID)
}

func (s *service) DeleteByPropertyID(propertyID int) error {
	if propertyID <= 0 {
		return domain.ErrInvalidEntity
	}
	return s.repo.DeleteByPropertyID(propertyID)
}

func (s *service) DeleteByAmenityID(amenityID int) error {
	if amenityID <= 0 {
		return domain.ErrInvalidEntity
	}
	return s.repo.DeleteByAmenityID(amenityID)
}

func (s *service) ensureProperty(propertyID int) error {
	_, err := s.activeProperty(propertyID)
	return err
}

func (s *service) activeProperty(propertyID int) (domain.Property, error) {
	property, err := s.propertyRepo.GetByID(propertyID)
	if err != nil {
		return domain.Property{}, err
	}
	if !property.Active {
		return domain.Property{}, domain.ErrInvalidEntity
	}
	return property, nil
}

func (s *service) ensureAmenity(amenityID int) error {
	_, err := s.activeAmenity(amenityID)
	return err
}

func (s *service) activeAmenity(amenityID int) (domain.AmenityCatalogItem, error) {
	amenity, err := s.amenityRepo.GetByID(amenityID)
	if err != nil {
		return domain.AmenityCatalogItem{}, err
	}
	if !amenity.Active {
		return domain.AmenityCatalogItem{}, domain.ErrInvalidEntity
	}
	return amenity, nil
}

func (s *service) resolveAmenities(values []domain.Amenity) ([]domain.AmenityCatalogItem, error) {
	if len(values) == 0 {
		return []domain.AmenityCatalogItem{}, nil
	}
	catalog, err := s.amenityRepo.GetAll()
	if err != nil {
		return nil, err
	}
	byName := make(map[string]domain.AmenityCatalogItem, len(catalog))
	for _, item := range catalog {
		byName[normalizeAmenityName(item.Name)] = item
	}

	seen := make(map[int]struct{}, len(values))
	resolved := make([]domain.AmenityCatalogItem, 0, len(values))
	for _, value := range values {
		var item domain.AmenityCatalogItem
		if value.ID > 0 {
			item, err = s.amenityRepo.GetByID(value.ID)
			if err != nil {
				return nil, err
			}
		} else {
			var ok bool
			item, ok = byName[normalizeAmenityName(value.Name)]
			if !ok {
				return nil, domain.ErrInvalidEntity
			}
		}
		if !item.Active {
			return nil, domain.ErrInvalidEntity
		}
		if _, ok := seen[item.ID]; ok {
			continue
		}
		seen[item.ID] = struct{}{}
		resolved = append(resolved, item)
	}
	return resolved, nil
}

func (s *service) legacyAmenities(values []domain.Amenity) ([]domain.AmenityCatalogItem, error) {
	if len(values) == 0 {
		return []domain.AmenityCatalogItem{}, nil
	}
	catalog, err := s.amenityRepo.GetAll()
	if err != nil {
		return nil, err
	}
	byName := make(map[string]domain.AmenityCatalogItem, len(catalog))
	for _, item := range catalog {
		byName[normalizeAmenityName(item.Name)] = item
	}

	seen := make(map[string]struct{}, len(values))
	items := make([]domain.AmenityCatalogItem, 0, len(values))
	for _, value := range values {
		key := normalizeAmenityName(value.Name)
		if key == "" {
			continue
		}
		if _, ok := seen[key]; ok {
			continue
		}
		seen[key] = struct{}{}

		if value.ID > 0 {
			if item, err := s.amenityRepo.GetByID(value.ID); err == nil {
				items = append(items, item)
				continue
			}
		}
		if item, ok := byName[key]; ok {
			items = append(items, item)
			continue
		}
		items = append(items, domain.AmenityCatalogItem{
			Name:        value.Name,
			Description: value.Description,
			Active:      true,
		})
	}
	return items, nil
}

func catalogToPropertyAmenities(items []domain.AmenityCatalogItem) []domain.Amenity {
	out := make([]domain.Amenity, 0, len(items))
	for _, item := range items {
		out = append(out, domain.Amenity{
			ID:          item.ID,
			Name:        item.Name,
			Description: item.Description,
		})
	}
	return out
}

func normalizeAmenityName(value string) string {
	return strings.ToLower(strings.TrimSpace(value))
}

func propertyHasAmenity(property domain.Property, amenity domain.AmenityCatalogItem) bool {
	target := normalizeAmenityName(amenity.Name)
	for _, item := range property.Amenities {
		if item.ID == amenity.ID || normalizeAmenityName(item.Name) == target {
			return true
		}
	}
	return false
}
