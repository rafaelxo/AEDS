package handler

import (
	"backend/internal/domain"
	"encoding/json"
	"errors"
	"net/http"
)

func respondJSON(w http.ResponseWriter, status int, payload any) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(status)
	_ = json.NewEncoder(w).Encode(payload)
}

func respondError(w http.ResponseWriter, status int, err error) {
	respondJSON(w, status, map[string]string{"error": err.Error()})
}

func respondDomainError(w http.ResponseWriter, err error) {
	switch {
	case errors.Is(err, domain.ErrNotFound):
		respondError(w, http.StatusNotFound, err)
	case errors.Is(err, domain.ErrAlreadyExists), errors.Is(err, domain.ErrEmailInUse):
		respondError(w, http.StatusConflict, err)
	case errors.Is(err, domain.ErrInvalidEntity):
		respondError(w, http.StatusBadRequest, err)
	default:
		respondError(w, http.StatusInternalServerError, err)
	}
}
