package handler

import (
	"backend/internal/adapters/patternmatch"
	"backend/internal/domain"
	"backend/internal/usecase/property"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"strconv"
	"strings"
)

type createPropertyRequest struct {
	UserID      int    `json:"idUsuario"`
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
	Latitude  float64  `json:"latitude"`
	Longitude float64  `json:"longitude"`
	DailyRate float64  `json:"valorDiaria"`
	CreatedAt string   `json:"dataCadastro"`
	Photos    []string `json:"fotos"`
	Active    bool     `json:"ativo"`
}

type propertyUpdatePayload struct {
	UserID      *int    `json:"idUsuario"`
	Title       *string `json:"titulo"`
	Description *string `json:"descricao"`
	Address     *struct {
		Street       string `json:"rua"`
		Number       string `json:"numero"`
		Neighborhood string `json:"bairro"`
		City         string `json:"cidade"`
		State        string `json:"estado"`
		ZipCode      string `json:"cep"`
	} `json:"endereco"`
	Amenities *[]struct {
		ID          int    `json:"idComodidade"`
		Name        string `json:"nome"`
		Description string `json:"descricao"`
	} `json:"comodidades"`
	City      *string   `json:"cidade"`
	Latitude  *float64  `json:"latitude"`
	Longitude *float64  `json:"longitude"`
	DailyRate *float64  `json:"valorDiaria"`
	CreatedAt *string   `json:"dataCadastro"`
	Photos    *[]string `json:"fotos"`
	Active    *bool     `json:"ativo"`
}

type PropertyHandler struct {
	svc    property.Service
	sortFn func(attr string, asc bool) error
}

func NewPropertyHandler(svc property.Service, sortFn func(attr string, asc bool) error) *PropertyHandler {
	return &PropertyHandler{svc: svc, sortFn: sortFn}
}

func (h *PropertyHandler) List(w http.ResponseWriter, r *http.Request) {
	query := r.URL.Query()
	algo := query.Get("algoritmo")
	filter, err := parsePropertyListFilter(
		query.Get("idUsuario"),
		query.Get("cidade"),
		query.Get("valorDiariaMin"),
		query.Get("valorDiariaMax"),
		query.Get("busca"),
		query.Get("ativo"),
		query.Get("comodidades"),
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

	if q := strings.TrimSpace(filter.Query); q != "" {
		matchFn := patternmatch.MatchBM
		if algo == "kmp" {
			matchFn = patternmatch.MatchKMP
		}
		matched := filtered[:0]
		for _, p := range filtered {
			if matchFn(p.Title, q) ||
				matchFn(p.Description, q) ||
				matchFn(p.City, q) ||
				matchFn(p.Address.Street, q) ||
				matchFn(p.Address.Neighborhood, q) {
				matched = append(matched, p)
			}
		}
		filtered = matched
	}

	respondJSON(w, http.StatusOK, filtered)
}

func parsePropertyListFilter(ownerIDRaw, cityRaw, minRateRaw, maxRateRaw, queryRaw, activeRaw, amenityIDsRaw string) (property.ListFilter, error) {
	filter := property.ListFilter{
		City:  cityRaw,
		Query: queryRaw,
	}
	if ownerIDRaw != "" {
		ownerID, err := strconv.Atoi(ownerIDRaw)
		if err != nil {
			return property.ListFilter{}, err
		}
		filter.OwnerID = &ownerID
	}
	if minRateRaw != "" {
		minRate, err := strconv.ParseFloat(minRateRaw, 64)
		if err != nil {
			return property.ListFilter{}, err
		}
		filter.MinDailyRate = &minRate
	}
	if maxRateRaw != "" {
		maxRate, err := strconv.ParseFloat(maxRateRaw, 64)
		if err != nil {
			return property.ListFilter{}, err
		}
		filter.MaxDailyRate = &maxRate
	}
	if activeRaw != "" {
		onlyActive, err := strconv.ParseBool(activeRaw)
		if err != nil {
			return property.ListFilter{}, err
		}
		if !onlyActive {
			filter.IncludeInactive = true
		}
	}
	if amenityIDsRaw != "" {
		for _, part := range strings.Split(amenityIDsRaw, ",") {
			part = strings.TrimSpace(part)
			if part == "" {
				continue
			}
			id, err := strconv.Atoi(part)
			if err != nil {
				return property.ListFilter{}, fmt.Errorf("comodidade inválida: %s", part)
			}
			filter.AmenityIDs = append(filter.AmenityIDs, id)
		}
	}
	return filter, nil
}

func (h *PropertyHandler) ListByOwner(w http.ResponseWriter, r *http.Request) {
	ownerID, err := strconv.Atoi(r.PathValue("idUsuario"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	items, err := h.svc.GetByOwnerID(ownerID)
	if err != nil {
		respondDomainError(w, err)
		return
	}

	respondJSON(w, http.StatusOK, items)
}

func (h *PropertyHandler) Create(w http.ResponseWriter, r *http.Request) {
	if strings.Contains(r.Header.Get("Content-Type"), "multipart/form-data") {
		payload, err := parsePropertyFromMultipart(r)
		if err != nil {
			respondError(w, http.StatusBadRequest, err)
			return
		}

		created, err := h.svc.Create(payload)
		if err != nil {
			respondDomainError(w, err)
			return
		}
		respondJSON(w, http.StatusCreated, created)
		return
	}

	var req createPropertyRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	payload := domain.Property{
		UserID:      req.UserID,
		Title:       req.Title,
		Description: req.Description,
		Address:     toDomainAddress(req.Address),
		Amenities:   toDomainAmenities(req.Amenities),
		City:        req.City,
		Latitude:    req.Latitude,
		Longitude:   req.Longitude,
		DailyRate:   req.DailyRate,
		CreatedAt:   req.CreatedAt,
		Photos:      req.Photos,
		Active:      req.Active,
	}
	created, err := h.svc.Create(payload)
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusCreated, created)
}

func (h *PropertyHandler) GetByID(w http.ResponseWriter, r *http.Request) {
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

func (h *PropertyHandler) Update(w http.ResponseWriter, r *http.Request) {
	id, err := strconv.Atoi(r.PathValue("id"))
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	if strings.Contains(r.Header.Get("Content-Type"), "multipart/form-data") {
		patch, err := parsePropertyPatchFromMultipart(r)
		if err != nil {
			respondError(w, http.StatusBadRequest, err)
			return
		}

		updated, err := h.svc.Patch(id, patch)
		if err != nil {
			respondDomainError(w, err)
			return
		}
		respondJSON(w, http.StatusOK, updated)
		return
	}

	var payload propertyUpdatePayload
	if err := json.NewDecoder(r.Body).Decode(&payload); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	updated, err := h.svc.Patch(id, property.PropertyPatch{
		UserID:      payload.UserID,
		Title:       payload.Title,
		Description: payload.Description,
		Address:     toDomainAddressPtr(payload.Address),
		Amenities:   toDomainAmenitiesPtr(payload.Amenities),
		City:        payload.City,
		Latitude:    payload.Latitude,
		Longitude:   payload.Longitude,
		DailyRate:   payload.DailyRate,
		CreatedAt:   payload.CreatedAt,
		Photos:      payload.Photos,
		Active:      payload.Active,
	})
	if err != nil {
		respondDomainError(w, err)
		return
	}
	respondJSON(w, http.StatusOK, updated)
}

func toDomainAddress(value struct {
	Street       string `json:"rua"`
	Number       string `json:"numero"`
	Neighborhood string `json:"bairro"`
	City         string `json:"cidade"`
	State        string `json:"estado"`
	ZipCode      string `json:"cep"`
}) domain.Address {
	return domain.Address{
		Street:       value.Street,
		Number:       value.Number,
		Neighborhood: value.Neighborhood,
		City:         value.City,
		State:        value.State,
		ZipCode:      value.ZipCode,
	}
}

func toDomainAddressPtr(value *struct {
	Street       string `json:"rua"`
	Number       string `json:"numero"`
	Neighborhood string `json:"bairro"`
	City         string `json:"cidade"`
	State        string `json:"estado"`
	ZipCode      string `json:"cep"`
}) *domain.Address {
	if value == nil {
		return nil
	}
	parsed := toDomainAddress(*value)
	return &parsed
}

func toDomainAmenities(values []struct {
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

func toDomainAmenitiesPtr(values *[]struct {
	ID          int    `json:"idComodidade"`
	Name        string `json:"nome"`
	Description string `json:"descricao"`
}) *[]domain.Amenity {
	if values == nil {
		return nil
	}
	parsed := toDomainAmenities(*values)
	return &parsed
}

func (h *PropertyHandler) Delete(w http.ResponseWriter, r *http.Request) {
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

func parsePropertyFromMultipart(r *http.Request) (domain.Property, error) {
	if err := r.ParseMultipartForm(20 << 20); err != nil {
		return domain.Property{}, err
	}

	toInt := func(key string) (int, error) {
		value := strings.TrimSpace(r.FormValue(key))
		if value == "" {
			return 0, fmt.Errorf("campo %s obrigatorio", key)
		}
		return strconv.Atoi(value)
	}

	toFloat := func(key string) (float64, error) {
		value := strings.TrimSpace(r.FormValue(key))
		if value == "" {
			return 0, nil
		}
		return strconv.ParseFloat(value, 64)
	}

	userID, err := toInt("idUsuario")
	if err != nil {
		return domain.Property{}, err
	}

	dailyRate, err := strconv.ParseFloat(strings.TrimSpace(r.FormValue("valorDiaria")), 64)
	if err != nil {
		return domain.Property{}, err
	}

	active := true
	if raw := strings.TrimSpace(r.FormValue("ativo")); raw != "" {
		active, err = strconv.ParseBool(raw)
		if err != nil {
			return domain.Property{}, err
		}
	}

	latitude, err := toFloat("latitude")
	if err != nil {
		return domain.Property{}, err
	}
	longitude, err := toFloat("longitude")
	if err != nil {
		return domain.Property{}, err
	}

	amenitiesRaw := strings.TrimSpace(r.FormValue("comodidades"))
	amenities := []domain.Amenity{}
	if amenitiesRaw != "" {
		if err := json.Unmarshal([]byte(amenitiesRaw), &amenities); err != nil {
			return domain.Property{}, err
		}
	}

	photos, err := extractUploadedPhotos(r)
	if err != nil {
		return domain.Property{}, err
	}

	return domain.Property{
		UserID:      userID,
		Title:       strings.TrimSpace(r.FormValue("titulo")),
		Description: strings.TrimSpace(r.FormValue("descricao")),
		Address: domain.Address{
			Street:       strings.TrimSpace(r.FormValue("endereco.rua")),
			Number:       strings.TrimSpace(r.FormValue("endereco.numero")),
			Neighborhood: strings.TrimSpace(r.FormValue("endereco.bairro")),
			City:         strings.TrimSpace(r.FormValue("endereco.cidade")),
			State:        strings.TrimSpace(r.FormValue("endereco.estado")),
			ZipCode:      strings.TrimSpace(r.FormValue("endereco.cep")),
		},
		Amenities: amenities,
		City:      strings.TrimSpace(r.FormValue("cidade")),
		Latitude:  latitude,
		Longitude: longitude,
		DailyRate: dailyRate,
		CreatedAt: strings.TrimSpace(r.FormValue("dataCadastro")),
		Photos:    photos,
		Active:    active,
	}, nil
}

func parsePropertyPatchFromMultipart(r *http.Request) (property.PropertyPatch, error) {
	if err := r.ParseMultipartForm(20 << 20); err != nil {
		return property.PropertyPatch{}, err
	}

	mustInt := func(key string) (*int, error) {
		value := strings.TrimSpace(r.FormValue(key))
		if value == "" {
			return nil, fmt.Errorf("campo %s obrigatorio", key)
		}
		parsed, err := strconv.Atoi(value)
		if err != nil {
			return nil, err
		}
		return &parsed, nil
	}

	mustFloat := func(key string) (*float64, error) {
		value := strings.TrimSpace(r.FormValue(key))
		if value == "" {
			return nil, fmt.Errorf("campo %s obrigatorio", key)
		}
		parsed, err := strconv.ParseFloat(value, 64)
		if err != nil {
			return nil, err
		}
		return &parsed, nil
	}

	mustString := func(key string) (*string, error) {
		value := strings.TrimSpace(r.FormValue(key))
		if value == "" {
			return nil, fmt.Errorf("campo %s obrigatorio", key)
		}
		return &value, nil
	}

	userID, err := mustInt("idUsuario")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	title, err := mustString("titulo")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	description, err := mustString("descricao")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	city, err := mustString("cidade")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	dailyRate, err := mustFloat("valorDiaria")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	createdAt, err := mustString("dataCadastro")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	latitude, err := mustFloat("latitude")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	longitude, err := mustFloat("longitude")
	if err != nil {
		return property.PropertyPatch{}, err
	}

	activeRaw := strings.TrimSpace(r.FormValue("ativo"))
	if activeRaw == "" {
		return property.PropertyPatch{}, fmt.Errorf("campo ativo obrigatorio")
	}
	active, err := strconv.ParseBool(activeRaw)
	if err != nil {
		return property.PropertyPatch{}, err
	}

	amenitiesRaw := strings.TrimSpace(r.FormValue("comodidades"))
	amenities := []domain.Amenity{}
	if amenitiesRaw != "" {
		if err := json.Unmarshal([]byte(amenitiesRaw), &amenities); err != nil {
			return property.PropertyPatch{}, err
		}
	}

	photos, err := extractUploadedPhotosOptional(r)
	if err != nil {
		return property.PropertyPatch{}, err
	}

	address := &domain.Address{
		Street:       strings.TrimSpace(r.FormValue("endereco.rua")),
		Number:       strings.TrimSpace(r.FormValue("endereco.numero")),
		Neighborhood: strings.TrimSpace(r.FormValue("endereco.bairro")),
		City:         strings.TrimSpace(r.FormValue("endereco.cidade")),
		State:        strings.TrimSpace(r.FormValue("endereco.estado")),
		ZipCode:      strings.TrimSpace(r.FormValue("endereco.cep")),
	}

	patch := property.PropertyPatch{
		UserID:      userID,
		Title:       title,
		Description: description,
		Address:     address,
		Amenities:   &amenities,
		City:        city,
		Latitude:    latitude,
		Longitude:   longitude,
		DailyRate:   dailyRate,
		CreatedAt:   createdAt,
		Active:      &active,
	}

	if photos != nil {
		patch.Photos = photos
	}

	return patch, nil
}

func extractUploadedPhotos(r *http.Request) ([]string, error) {
	files := r.MultipartForm.File["fotos"]
	if len(files) == 0 {
		return nil, fmt.Errorf("foto obrigatoria")
	}
	if len(files) > 5 {
		files = files[:5]
	}

	var photos []string
	for _, header := range files {
		file, err := header.Open()
		if err != nil {
			return nil, err
		}
		data, err := io.ReadAll(file)
		file.Close()
		if err != nil {
			return nil, err
		}
		if len(data) == 0 {
			return nil, fmt.Errorf("foto vazia")
		}
		contentType := header.Header.Get("Content-Type")
		if contentType == "" {
			contentType = http.DetectContentType(data)
		}
		if !strings.HasPrefix(contentType, "image/") {
			return nil, fmt.Errorf("arquivo %s nao e imagem valida", header.Filename)
		}
		dataURL, err := saveRequestImage(data, contentType)
		if err != nil {
			return nil, err
		}
		photos = append(photos, dataURL)
	}
	return photos, nil
}

func extractUploadedPhotosOptional(r *http.Request) (*[]string, error) {
	if len(r.MultipartForm.File["fotos"]) == 0 {
		return nil, nil
	}
	photos, err := extractUploadedPhotos(r)
	if err != nil {
		return nil, err
	}
	return &photos, nil
}
