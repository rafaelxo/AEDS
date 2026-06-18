package domain

import "strings"

type AmenityCatalogItem struct {
	ID          int    `json:"idComodidade"`
	Name        string `json:"nome"`
	Description string `json:"descricao,omitempty"`
	Icon        string `json:"icone,omitempty"`
	Active      bool   `json:"ativo"`
}

func (a *AmenityCatalogItem) Normalize() {
	a.Name = strings.TrimSpace(a.Name)
	a.Description = strings.TrimSpace(a.Description)
	a.Icon = strings.TrimSpace(a.Icon)
}

func (a AmenityCatalogItem) Validate() error {
	a.Normalize()
	if len(a.Name) < 2 {
		return ErrInvalidEntity
	}
	return nil
}
