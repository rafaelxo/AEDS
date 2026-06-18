package handler

import (
	"backend/internal/adapters/patternmatch"
	"backend/internal/domain"
	reservationuc "backend/internal/usecase/reservation"
	"encoding/json"
	"fmt"
	"net/http"
	"strconv"
)

type createReservationRequest struct {
	PropertyID    int                  `json:"idImovel"`
	GuestID       int                  `json:"idHospede"`
	StartDate     string               `json:"dataInicio"`
	EndDate       string               `json:"dataFim"`
	PaymentMethod domain.PaymentMethod `json:"formaPagamento"`
}

type reservationUpdatePayload struct {
	PropertyID    *int                      `json:"idImovel"`
	GuestID       *int                      `json:"idHospede"`
	StartDate     *string                   `json:"dataInicio"`
	EndDate       *string                   `json:"dataFim"`
	PaymentMethod *domain.PaymentMethod     `json:"formaPagamento"`
	Status        *domain.ReservationStatus `json:"status"`
}

type confirmReservationPayload struct {
	PaymentMethod domain.PaymentMethod `json:"formaPagamento"`
}

type ReservationHandler struct {
	svc    reservationuc.Service
	sortFn func(attr string, asc bool) error
}

func NewReservationHandler(svc reservationuc.Service, sortFn func(attr string, asc bool) error) *ReservationHandler {
	return &ReservationHandler{svc: svc, sortFn: sortFn}
}

func (h *ReservationHandler) List(w http.ResponseWriter, r *http.Request) {
	query := r.URL.Query()
	algo := query.Get("algoritmo")
	filter, err := parseReservationListFilter(
		query.Get("idImovel"),
		query.Get("idUsuario"),
		query.Get("papel"),
		query.Get("status"),
		firstNonEmpty(query.Get("periodoDe"), query.Get("dataInicioDe")),
		firstNonEmpty(query.Get("periodoAte"), query.Get("dataFimAte")),
		query.Get("busca"),
	)
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	if sortBy := query.Get("ordenarPor"); sortBy != "" {
		asc := query.Get("ordem") != "desc"
		if err := h.sortFn(sortBy, asc); err != nil {
			respondError(w, http.StatusInternalServerError, err)
			return
		}
	}

	filtered, err := h.svc.List(filter)
	if err != nil {
		respondDomainError(w, err)
		return
	}

	if q := filter.Query; q != "" {
		matchFn := patternmatch.MatchBM
		if algo == "kmp" {
			matchFn = patternmatch.MatchKMP
		}
		var matched []domain.Reservation
		for _, res := range filtered {
			if matchFn(string(res.Status), q) ||
				matchFn(res.StartDate, q) ||
				matchFn(res.EndDate, q) {
				matched = append(matched, res)
			}
		}
		if matched == nil {
			matched = []domain.Reservation{}
		}
		filtered = matched
	}

	respondJSON(w, http.StatusOK, filtered)
}

func parseReservationListFilter(rawPropertyID, rawUserID, role, status, periodFrom, periodTo, query string) (reservationuc.ListFilter, error) {
	filter := reservationuc.ListFilter{
		Role:       role,
		Status:     status,
		PeriodFrom: periodFrom,
		PeriodTo:   periodTo,
		Query:      query,
	}
	if rawPropertyID != "" {
		propertyID, err := strconv.Atoi(rawPropertyID)
		if err != nil {
			return reservationuc.ListFilter{}, err
		}
		filter.PropertyID = &propertyID
	}
	if rawUserID != "" {
		userID, err := strconv.Atoi(rawUserID)
		if err != nil {
			return reservationuc.ListFilter{}, err
		}
		filter.UserID = &userID
	}
	if filter.UserID != nil && filter.Role != "" && filter.Role != "hospede" && filter.Role != "anfitriao" {
		return reservationuc.ListFilter{}, fmt.Errorf("campo papel obrigatorio para filtro por usuario")
	}
	return filter, nil
}

func firstNonEmpty(values ...string) string {
	for _, value := range values {
		if value != "" {
			return value
		}
	}
	return ""
}

func (h *ReservationHandler) ListByGuest(w http.ResponseWriter, r *http.Request) {
	guestID, err := strconv.Atoi(r.PathValue("idHospede"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	items, err := h.svc.GetByGuestID(guestID)
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, items)
}

func (h *ReservationHandler) ListByHost(w http.ResponseWriter, r *http.Request) {
	hostID, err := strconv.Atoi(r.PathValue("idAnfitriao"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	items, err := h.svc.GetByHostID(hostID)
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, items)
}

func (h *ReservationHandler) Create(w http.ResponseWriter, r *http.Request) {
	var req createReservationRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	payload := domain.Reservation{
		PropertyID:    req.PropertyID,
		GuestID:       req.GuestID,
		StartDate:     req.StartDate,
		EndDate:       req.EndDate,
		PaymentMethod: req.PaymentMethod,
	}
	created, err := h.svc.Create(payload)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusCreated, created)
}

func (h *ReservationHandler) GetByID(w http.ResponseWriter, r *http.Request) {
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

func (h *ReservationHandler) Update(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	var payload reservationUpdatePayload
	if err := json.NewDecoder(r.Body).Decode(&payload); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	updated, err := h.svc.Update(id, reservationuc.ReservationUpdate(payload))
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, updated)
}

func (h *ReservationHandler) Confirm(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	var payload confirmReservationPayload
	if err := json.NewDecoder(r.Body).Decode(&payload); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	confirmed, err := h.svc.Confirm(id, reservationuc.ConfirmReservationInput{
		PaymentMethod: payload.PaymentMethod,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, confirmed)
}

func (h *ReservationHandler) Delete(w http.ResponseWriter, r *http.Request) {
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
