package handler

import (
	"backend/internal/adapters/patternmatch"
	"backend/internal/usecase/property"
	reservationuc "backend/internal/usecase/reservation"
	useruc "backend/internal/usecase/user"
	"errors"
	"net/http"
)

type patternMatchHandler struct {
	engine  *patternmatch.Engine
	props   property.Service
	users   useruc.Service
	reservs reservationuc.Service
}

func NewPatternMatchHandler(
	pm *patternmatch.Engine,
	ps property.Service,
	us useruc.Service,
	rs reservationuc.Service,
) *patternMatchHandler {
	return &patternMatchHandler{engine: pm, props: ps, users: us, reservs: rs}
}

func (h *patternMatchHandler) Search(w http.ResponseWriter, r *http.Request) {
	pattern := r.URL.Query().Get("q")
	entity := r.URL.Query().Get("entidade")

	var records []patternmatch.SearchableRecord

	switch entity {
	case "imoveis":
		props, err := h.props.GetAll()
		if err != nil {
			respondError(w, http.StatusInternalServerError, err)
			return
		}
		for _, p := range props {
			records = append(records, patternmatch.SearchableRecord{
				ID: p.ID,
				Fields: map[string]string{
					"titulo":          p.Title,
					"descricao":       p.Description,
					"cidade":          p.City,
					"endereco.rua":    p.Address.Street,
					"endereco.bairro": p.Address.Neighborhood,
				},
			})
		}
	case "usuarios":
		users, err := h.users.GetAll()
		if err != nil {
			respondError(w, http.StatusInternalServerError, err)
			return
		}
		for _, u := range users {
			records = append(records, patternmatch.SearchableRecord{
				ID: u.ID,
				Fields: map[string]string{
					"nome":  u.Name,
					"email": u.Email,
				},
			})
		}
	case "reservas":
		reservs, err := h.reservs.GetAll()
		if err != nil {
			respondError(w, http.StatusInternalServerError, err)
			return
		}
		for _, res := range reservs {
			records = append(records, patternmatch.SearchableRecord{
				ID: res.ID,
				Fields: map[string]string{
					"status": string(res.Status),
				},
			})
		}
	default:
		respondError(w, http.StatusBadRequest, errors.New("entidade invalida: use imoveis, usuarios ou reservas"))
		return
	}

	result := h.engine.Search(pattern, entity, records)
	respondJSON(w, http.StatusOK, result)
}
