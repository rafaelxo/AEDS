package handler

import (
	"backend/internal/domain"
	authuc "backend/internal/usecase/auth"
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
)

type AuthHandler struct {
	svc authuc.Service
}

type registerRequest struct {
	Name     string `json:"nome"`
	Email    string `json:"email"`
	Phone    string `json:"telefone"`
	Password string `json:"senha"`
	AsHost   bool   `json:"comoAnfitriao"`
	Property *struct {
		Title       string `json:"titulo"`
		Description string `json:"descricao"`
		Address     struct {
			Street       string `json:"rua"`
			Number       string `json:"numero"`
			Neighborhood string `json:"bairro"`
			City         string `json:"cidade"`
			State        string `json:"estado"`
			ZipCode      string `json:"cep"`
		} `json:"endereco"`
		Amenities []struct {
			ID          int    `json:"idComodidade"`
			Name        string `json:"nome"`
			Description string `json:"descricao"`
		} `json:"comodidades"`
		City      string   `json:"cidade"`
		DailyRate float64  `json:"valorDiaria"`
		CreatedAt string   `json:"dataCadastro"`
		Photos    []string `json:"fotos"`
		Active    bool     `json:"ativo"`
	} `json:"imovelInicial"`
}

type loginRequest struct {
	Email    string `json:"email"`
	Password string `json:"senha"`
}

func NewAuthHandler(svc authuc.Service) *AuthHandler {
	return &AuthHandler{svc: svc}
}

func (h *AuthHandler) Register(w http.ResponseWriter, r *http.Request) {
	var req registerRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	var initialProperty *domain.Property
	if req.AsHost && req.Property != nil {
		photos, err := normalizeInitialPropertyPhotos(req.Property.Photos)
		if err != nil {
			respondError(w, http.StatusBadRequest, err)
			return
		}

		initialProperty = &domain.Property{
			Title:       req.Property.Title,
			Description: req.Property.Description,
			Address: domain.Address{
				Street:       req.Property.Address.Street,
				Number:       req.Property.Address.Number,
				Neighborhood: req.Property.Address.Neighborhood,
				City:         req.Property.Address.City,
				State:        req.Property.Address.State,
				ZipCode:      req.Property.Address.ZipCode,
			},
			Amenities: mapAmenities(req.Property.Amenities),
			City:      req.Property.City,
			DailyRate: req.Property.DailyRate,
			CreatedAt: req.Property.CreatedAt,
			Photos:    photos,
			Active:    req.Property.Active,
		}
	}

	session, err := h.svc.Register(authuc.RegisterInput{
		Name:            req.Name,
		Email:           req.Email,
		Phone:           req.Phone,
		Password:        req.Password,
		CreateAsHost:    req.AsHost,
		InitialProperty: initialProperty,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusCreated, session)
}

func normalizeInitialPropertyPhotos(values []string) ([]string, error) {
	if len(values) == 0 {
		return nil, fmt.Errorf("foto obrigatoria")
	}

	value := strings.TrimSpace(values[0])
	if value == "" {
		return nil, fmt.Errorf("foto obrigatoria")
	}

	if strings.HasPrefix(strings.ToLower(value), "data:image/") {
		dataURL, err := savePhotoFromDataURL(value)
		if err != nil {
			return nil, err
		}
		return []string{dataURL}, nil
	}

	if strings.HasPrefix(strings.ToLower(value), "http://") || strings.HasPrefix(strings.ToLower(value), "https://") {
		return []string{value}, nil
	}

	return nil, fmt.Errorf("formato de foto invalido")
}

func mapAmenities(values []struct {
	ID          int    `json:"idComodidade"`
	Name        string `json:"nome"`
	Description string `json:"descricao"`
}) []domain.Amenity {
	if len(values) == 0 {
		return []domain.Amenity{}
	}
	items := make([]domain.Amenity, 0, len(values))
	for _, item := range values {
		items = append(items, domain.Amenity{ID: item.ID, Name: item.Name, Description: item.Description})
	}
	return items
}

func (h *AuthHandler) Login(w http.ResponseWriter, r *http.Request) {
	var req loginRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	session, err := h.svc.Login(authuc.LoginInput{
		Email:    req.Email,
		Password: req.Password,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, session)
}

func (h *AuthHandler) Me(w http.ResponseWriter, r *http.Request) {
	token := extractBearerToken(r.Header.Get("Authorization"))
	if token == "" {
		respondError(w, http.StatusUnauthorized, domain.ErrNotFound)
		return
	}

	user, err := h.svc.GetUserByToken(token)
	if err != nil {
		respondError(w, http.StatusUnauthorized, err)
		return
	}

	respondJSON(w, http.StatusOK, user)
}

func extractBearerToken(header string) string {
	trimmed := strings.TrimSpace(header)
	if trimmed == "" {
		return ""
	}
	const prefix = "Bearer "
	if !strings.HasPrefix(trimmed, prefix) {
		return ""
	}
	return strings.TrimSpace(strings.TrimPrefix(trimmed, prefix))
}
