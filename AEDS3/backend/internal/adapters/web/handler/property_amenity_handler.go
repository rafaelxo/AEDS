package handler

import (
	"backend/internal/domain"
	propertyamenityuc "backend/internal/usecase/propertyamenity"
	"encoding/json"
	"net/http"
	"strconv"
)

type propertyAmenityRequest struct {
	PropertyID int    `json:"idImovel"`
	AmenityID  int    `json:"idComodidade"`
	CreatedAt  string `json:"dataCadastro"`
	Active     bool   `json:"ativo"`
}

type PropertyAmenityHandler struct {
	svc propertyamenityuc.Service
}

func NewPropertyAmenityHandler(svc propertyamenityuc.Service) *PropertyAmenityHandler {
	return &PropertyAmenityHandler{svc: svc}
}

func (h *PropertyAmenityHandler) Create(w http.ResponseWriter, r *http.Request) {
	var req propertyAmenityRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	created, err := h.svc.Create(domain.PropertyAmenity{
		PropertyID: req.PropertyID,
		AmenityID:  req.AmenityID,
		CreatedAt:  req.CreatedAt,
		Active:     req.Active,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusCreated, created)
}

func (h *PropertyAmenityHandler) Get(w http.ResponseWriter, r *http.Request) {
	propertyID, amenityID, ok := parsePropertyAmenityPathIDs(w, r)
	if !ok {
		return
	}
	item, err := h.svc.Get(propertyID, amenityID)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, item)
}

func (h *PropertyAmenityHandler) ListAmenitiesByProperty(w http.ResponseWriter, r *http.Request) {
	propertyID, err := strconv.Atoi(r.PathValue("idImovel"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	items, err := h.svc.ListAmenitiesByProperty(propertyID)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, items)
}

func (h *PropertyAmenityHandler) ListPropertiesByAmenity(w http.ResponseWriter, r *http.Request) {
	amenityID, err := strconv.Atoi(r.PathValue("idComodidade"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	items, err := h.svc.ListPropertiesByAmenity(amenityID)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, items)
}

func (h *PropertyAmenityHandler) Delete(w http.ResponseWriter, r *http.Request) {
	propertyID, amenityID, ok := parsePropertyAmenityPathIDs(w, r)
	if !ok {
		return
	}
	if err := h.svc.Delete(propertyID, amenityID); err != nil {
		respondDomainError(w, err)
		return
	}
	w.WriteHeader(http.StatusNoContent)
}

func parsePropertyAmenityPathIDs(w http.ResponseWriter, r *http.Request) (int, int, bool) {
	propertyID, err := strconv.Atoi(r.PathValue("idImovel"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return 0, 0, false
	}
	amenityID, err := strconv.Atoi(r.PathValue("idComodidade"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return 0, 0, false
	}
	return propertyID, amenityID, true
}
