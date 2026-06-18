package handler

import (
	"backend/internal/domain"
	"encoding/json"
	"net/http"
	"strconv"

	amenityuc "backend/internal/usecase/amenity"
)

type createAmenityRequest struct {
	Name        string `json:"nome"`
	Description string `json:"descricao"`
	Icon        string `json:"icone"`
	Active      bool   `json:"ativo"`
}

type updateAmenityRequest struct {
	Name        string `json:"nome"`
	Description string `json:"descricao"`
	Icon        string `json:"icone"`
	Active      bool   `json:"ativo"`
}

type AmenityHandler struct {
	svc amenityuc.Service
}

func NewAmenityHandler(svc amenityuc.Service) *AmenityHandler {
	return &AmenityHandler{svc: svc}
}

func (h *AmenityHandler) List(w http.ResponseWriter, r *http.Request) {
	includeInactive := r.URL.Query().Get("incluirInativas") == "true"

	var (
		items []domain.AmenityCatalogItem
		err   error
	)

	if includeInactive {
		items, err = h.svc.GetAll()
	} else {
		items, err = h.svc.GetAllActive()
	}
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}
	respondJSON(w, http.StatusOK, items)
}

func (h *AmenityHandler) Create(w http.ResponseWriter, r *http.Request) {
	var req createAmenityRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	created, err := h.svc.Create(domain.AmenityCatalogItem{
		Name:        req.Name,
		Description: req.Description,
		Icon:        req.Icon,
		Active:      req.Active,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusCreated, created)
}

func (h *AmenityHandler) GetByID(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	item, err := h.svc.GetByID(id)
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, item)
}

func (h *AmenityHandler) Update(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	var req updateAmenityRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	updated, err := h.svc.Update(id, domain.AmenityCatalogItem{
		Name:        req.Name,
		Description: req.Description,
		Icon:        req.Icon,
		Active:      req.Active,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, updated)
}

func (h *AmenityHandler) Delete(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	if err := h.svc.Delete(id); err != nil {
		respondDomainError(w, err)
		return
	}

	w.WriteHeader(http.StatusNoContent)
}
