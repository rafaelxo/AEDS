package handler

import (
	aeduc "backend/internal/usecase/aed"
	"net/http"
	"strconv"
)

type AEDHandler struct {
	svc aeduc.Service
}

func NewAEDHandler(svc aeduc.Service) *AEDHandler {
	return &AEDHandler{svc: svc}
}

func (h *AEDHandler) Diagnostico(w http.ResponseWriter, r *http.Request) {
	respondJSON(w, http.StatusOK, h.svc.HashDiagnostics())
}

func (h *AEDHandler) RelacaoAnfitriao(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	result, err := h.svc.RelationshipByHost(id)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, result)
}
