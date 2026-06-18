package amenity

import (
	"backend/internal/domain"
	"strings"
)

var commonAmenities = []domain.AmenityCatalogItem{
	{Name: "Wi-Fi", Description: "Internet sem fio", Icon: "wifi", Active: true},
	{Name: "Ar-condicionado", Description: "Climatização do ambiente", Icon: "snowflake", Active: true},
	{Name: "Cozinha equipada", Description: "Fogão, geladeira e utensílios", Icon: "utensils", Active: true},
	{Name: "Máquina de lavar", Description: "Lavanderia disponível", Icon: "shirt", Active: true},
	{Name: "Estacionamento", Description: "Vaga para veículo", Icon: "car", Active: true},
	{Name: "Piscina", Description: "Área de lazer com piscina", Icon: "waves", Active: true},
	{Name: "Academia", Description: "Espaço fitness", Icon: "dumbbell", Active: true},
	{Name: "TV", Description: "Televisão no imóvel", Icon: "tv", Active: true},
	{Name: "Pet-friendly", Description: "Aceita animais de estimação", Icon: "paw-print", Active: true},
	{Name: "Churrasqueira", Description: "Área gourmet com churrasqueira", Icon: "flame", Active: true},
	{Name: "Varanda", Description: "Espaço externo privativo", Icon: "sun", Active: true},
	{Name: "Vista para o mar", Description: "Visual privilegiado", Icon: "mountain", Active: true},
}

func (s *service) Create(item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error) {
	item.Normalize()
	if !item.Active {
		item.Active = true
	}
	if err := item.Validate(); err != nil {
		return domain.AmenityCatalogItem{}, err
	}
	if exists, err := s.existsByName(item.Name, 0); err != nil {
		return domain.AmenityCatalogItem{}, err
	} else if exists {
		return domain.AmenityCatalogItem{}, domain.ErrAlreadyExists
	}
	return s.repo.Create(item)
}

func (s *service) GetByID(id int) (domain.AmenityCatalogItem, error) {
	if id <= 0 {
		return domain.AmenityCatalogItem{}, domain.ErrInvalidEntity
	}
	return s.repo.GetByID(id)
}

func (s *service) GetAll() ([]domain.AmenityCatalogItem, error) {
	return s.repo.GetAll()
}

func (s *service) Update(id int, item domain.AmenityCatalogItem) (domain.AmenityCatalogItem, error) {
	if id <= 0 {
		return domain.AmenityCatalogItem{}, domain.ErrInvalidEntity
	}
	item.ID = id
	item.Normalize()
	if err := item.Validate(); err != nil {
		return domain.AmenityCatalogItem{}, err
	}
	if exists, err := s.existsByName(item.Name, id); err != nil {
		return domain.AmenityCatalogItem{}, err
	} else if exists {
		return domain.AmenityCatalogItem{}, domain.ErrAlreadyExists
	}
	return s.repo.Update(id, item)
}

func (s *service) Delete(id int) error {
	if id <= 0 {
		return domain.ErrInvalidEntity
	}
	if err := s.repo.Delete(id); err != nil {
		return err
	}
	if s.cleaner != nil {
		return s.cleaner.DeleteByAmenityID(id)
	}
	return nil
}

func (s *service) GetAllActive() ([]domain.AmenityCatalogItem, error) {
	items, err := s.repo.GetAll()
	if err != nil {
		return nil, err
	}

	active := make([]domain.AmenityCatalogItem, 0, len(items))
	seen := make(map[string]struct{}, len(items))
	for _, item := range items {
		if item.Active {
			key := amenityNameKey(item.Name)
			if key == "" {
				continue
			}
			if _, ok := seen[key]; ok {
				continue
			}
			seen[key] = struct{}{}
			active = append(active, item)
		}
	}
	return active, nil
}

func (s *service) SeedCommonAmenities() error {
	current, err := s.repo.GetAll()
	if err != nil {
		return err
	}
	existing := make(map[string]struct{}, len(current))
	for _, item := range current {
		if item.Active {
			existing[amenityNameKey(item.Name)] = struct{}{}
		}
	}

	for _, amenity := range commonAmenities {
		amenity.Normalize()
		if err := amenity.Validate(); err != nil {
			continue
		}
		key := amenityNameKey(amenity.Name)
		if _, ok := existing[key]; ok {
			continue
		}
		if _, err := s.repo.Create(amenity); err != nil {
			return err
		}
		existing[key] = struct{}{}
	}

	return nil
}

func (s *service) existsByName(name string, ignoreID int) (bool, error) {
	key := amenityNameKey(name)
	items, err := s.repo.GetAll()
	if err != nil {
		return false, err
	}
	for _, item := range items {
		if item.ID == ignoreID || !item.Active {
			continue
		}
		if amenityNameKey(item.Name) == key {
			return true, nil
		}
	}
	return false, nil
}

func amenityNameKey(value string) string {
	return strings.ToLower(strings.TrimSpace(value))
}
