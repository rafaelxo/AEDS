package domain

import (
	"fmt"
	"strings"
	"time"
)

type PropertyAmenity struct {
	PropertyID int    `json:"idImovel"`
	AmenityID  int    `json:"idComodidade"`
	CreatedAt  string `json:"dataCadastro"`
	Active     bool   `json:"ativo"`
}

func (r PropertyAmenity) Validate() error {
	if r.PropertyID <= 0 {
		return fmt.Errorf("%w: idImovel invalido", ErrInvalidEntity)
	}
	if r.AmenityID <= 0 {
		return fmt.Errorf("%w: idComodidade invalido", ErrInvalidEntity)
	}
	if strings.TrimSpace(r.CreatedAt) == "" {
		return fmt.Errorf("%w: dataCadastro obrigatoria", ErrInvalidEntity)
	}
	if _, err := time.Parse("2006-01-02", r.CreatedAt); err != nil {
		return fmt.Errorf("%w: dataCadastro deve estar no formato YYYY-MM-DD", ErrInvalidEntity)
	}
	return nil
}

func (r *PropertyAmenity) Normalize() {
	r.CreatedAt = strings.TrimSpace(r.CreatedAt)
}
