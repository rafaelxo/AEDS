package handler

import (
	"backend/internal/usecase/property"
	reservationuc "backend/internal/usecase/reservation"
	useruc "backend/internal/usecase/user"
	"net/http"
)

type dashboardStats struct {
	TotalProperties int     `json:"totalImoveis"`
	TotalHosts      int     `json:"totalAnfitrioes"`
	TotalBookings   int     `json:"totalReservas"`
	TotalRevenue    float64 `json:"receitaTotal"`
}

type DashboardHandler struct {
	propertySvc    property.Service
	userSvc        useruc.Service
	reservationSvc reservationuc.Service
}

func NewDashboardHandler(propertySvc property.Service, userSvc useruc.Service, reservationSvc reservationuc.Service) *DashboardHandler {
	return &DashboardHandler{
		propertySvc:    propertySvc,
		userSvc:        userSvc,
		reservationSvc: reservationSvc,
	}
}

func (h *DashboardHandler) Stats(w http.ResponseWriter, r *http.Request) {
	properties, err := h.propertySvc.GetAll()
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}
	hosts, err := h.userSvc.GetAllHosts()
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}
	reservations, err := h.reservationSvc.GetAll()
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}

	stats := dashboardStats{
		TotalProperties: len(properties),
		TotalHosts:      len(hosts),
		TotalBookings:   len(reservations),
	}

	for _, res := range reservations {
		stats.TotalRevenue += res.TotalValue
	}

	respondJSON(w, http.StatusOK, stats)
}
