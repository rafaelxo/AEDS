package reservation

import (
	"backend/internal/domain"
	paymentuc "backend/internal/usecase/payment"
	"errors"
	"fmt"
	"math"
	"strings"
	"time"
)

type ReservationUpdate struct {
	PropertyID    *int
	GuestID       *int
	StartDate     *string
	EndDate       *string
	PaymentMethod *domain.PaymentMethod
	Status        *domain.ReservationStatus
}

type ConfirmReservationInput struct {
	PaymentMethod domain.PaymentMethod
}

func (s *service) Create(item domain.Reservation) (domain.Reservation, error) {
	item.SetDefaults()
	if err := item.Validate(); err != nil {
		return domain.Reservation{}, err
	}

	property, err := s.propertyRepo.GetByID(item.PropertyID)
	if err != nil {
		return domain.Reservation{}, err
	}
	if !property.Active {
		return domain.Reservation{}, fmt.Errorf("%w: imovel inativo", domain.ErrInvalidEntity)
	}

	guest, err := s.guestRepo.GetByID(item.GuestID)
	if err != nil {
		return domain.Reservation{}, err
	}
	if !guest.Active {
		return domain.Reservation{}, fmt.Errorf("%w: hospede inativo", domain.ErrInvalidEntity)
	}

	totalValue, err := calculateTotalValue(property.DailyRate, item.StartDate, item.EndDate)
	if err != nil {
		return domain.Reservation{}, err
	}

	hasOverlap, err := s.hasOverlap(0, item.PropertyID, item.StartDate, item.EndDate)
	if err != nil {
		return domain.Reservation{}, err
	}
	if hasOverlap {
		return domain.Reservation{}, domain.ErrAlreadyExists
	}

	item.TotalValue = totalValue

	return s.repo.Create(item)
}

func (s *service) GetByID(id int) (domain.Reservation, error) {
	if id <= 0 {
		return domain.Reservation{}, domain.ErrInvalidEntity
	}
	return s.repo.GetByID(id)
}

func (s *service) GetAll() ([]domain.Reservation, error) {
	return s.repo.GetAll()
}

func (s *service) GetByPropertyID(propertyID int) ([]domain.Reservation, error) {
	if propertyID <= 0 {
		return nil, domain.ErrInvalidEntity
	}
	if _, err := s.propertyRepo.GetByID(propertyID); err != nil {
		return nil, err
	}
	return s.repo.GetByPropertyID(propertyID)
}

func (s *service) GetByGuestID(guestID int) ([]domain.Reservation, error) {
	if guestID <= 0 {
		return nil, domain.ErrInvalidEntity
	}
	if _, err := s.guestRepo.GetByID(guestID); err != nil {
		return nil, err
	}
	return s.repo.GetByGuestID(guestID)
}

func (s *service) GetByHostID(hostID int) ([]domain.Reservation, error) {
	if hostID <= 0 {
		return nil, domain.ErrInvalidEntity
	}
	host, err := s.guestRepo.GetByID(hostID)
	if err != nil {
		return nil, err
	}
	if host.Type != domain.UserTypeHost && host.Type != domain.UserTypeAdmin {
		return nil, domain.ErrInvalidEntity
	}

	properties, err := s.propertyRepo.GetByOwnerID(hostID)
	if err != nil {
		return nil, err
	}
	owned := make(map[int]struct{}, len(properties))
	for _, p := range properties {
		owned[p.ID] = struct{}{}
	}

	filtered := make([]domain.Reservation, 0)
	for propertyID := range owned {
		items, err := s.repo.GetByPropertyID(propertyID)
		if err != nil {
			return nil, err
		}
		filtered = append(filtered, items...)
	}
	return filtered, nil
}

func (s *service) GetByHostWithProperties(hostID int) (map[int][]domain.Reservation, error) {
	if hostID <= 0 {
		return nil, domain.ErrInvalidEntity
	}

	properties, err := s.propertyRepo.GetByOwnerID(hostID)
	if err != nil {
		return nil, err
	}

	owned := make(map[int]struct{})
	for _, p := range properties {
		owned[p.ID] = struct{}{}
	}

	grouped := make(map[int][]domain.Reservation)
	for propertyID := range owned {
		items, err := s.repo.GetByPropertyID(propertyID)
		if err != nil {
			return nil, err
		}
		if len(items) > 0 {
			grouped[propertyID] = append(grouped[propertyID], items...)
		}
	}

	return grouped, nil
}

type reservationSearcher interface {
	Search(query string, status string) ([]domain.Reservation, error)
}

func (s *service) List(filter ListFilter) ([]domain.Reservation, error) {
	var (
		items []domain.Reservation
		err   error
	)

	if filter.PropertyID != nil {
		items, err = s.GetByPropertyID(*filter.PropertyID)
	} else if filter.UserID != nil {
		switch filter.Role {
		case "hospede":
			items, err = s.GetByGuestID(*filter.UserID)
		case "anfitriao":
			items, err = s.GetByHostID(*filter.UserID)
		case "":
			guestItems, guestErr := s.GetByGuestID(*filter.UserID)
			if guestErr != nil {
				return nil, guestErr
			}
			hostItems, hostErr := s.GetByHostID(*filter.UserID)
			if hostErr != nil && !errors.Is(hostErr, domain.ErrInvalidEntity) {
				return nil, hostErr
			}
			merged := make(map[int]domain.Reservation, len(guestItems)+len(hostItems))
			for _, item := range guestItems {
				merged[item.ID] = item
			}
			for _, item := range hostItems {
				merged[item.ID] = item
			}
			items = make([]domain.Reservation, 0, len(merged))
			for _, item := range merged {
				items = append(items, item)
			}
		default:
			return nil, fmt.Errorf("%w: campo papel obrigatorio para filtro por usuario", domain.ErrInvalidEntity)
		}
	} else {
		items, err = s.repo.GetAll()
	}
	if err != nil {
		return nil, err
	}

	if searcher, ok := s.repo.(reservationSearcher); ok && (strings.TrimSpace(filter.Query) != "" || strings.TrimSpace(filter.Status) != "") {
		indexed, searchErr := searcher.Search(filter.Query, filter.Status)
		if searchErr != nil {
			return nil, searchErr
		}
		items = intersectReservationsByID(items, indexed)
	}

	return filterReservations(items, filter.Status, filter.PeriodFrom, filter.PeriodTo)
}

func intersectReservationsByID(left []domain.Reservation, right []domain.Reservation) []domain.Reservation {
	if len(left) == 0 || len(right) == 0 {
		return []domain.Reservation{}
	}
	set := make(map[int]domain.Reservation, len(right))
	for _, item := range right {
		set[item.ID] = item
	}
	out := make([]domain.Reservation, 0, len(left))
	for _, item := range left {
		if candidate, ok := set[item.ID]; ok {
			out = append(out, candidate)
		}
	}
	return out
}

func (s *service) Update(id int, item ReservationUpdate) (domain.Reservation, error) {
	if id <= 0 {
		return domain.Reservation{}, domain.ErrInvalidEntity
	}
	existing, err := s.repo.GetByID(id)
	if err != nil {
		return domain.Reservation{}, err
	}
	if item.PropertyID != nil {
		existing.PropertyID = *item.PropertyID
	}
	if item.GuestID != nil {
		existing.GuestID = *item.GuestID
	}
	if item.StartDate != nil {
		existing.StartDate = *item.StartDate
	}
	if item.EndDate != nil {
		existing.EndDate = *item.EndDate
	}
	if item.PaymentMethod != nil {
		existing.PaymentMethod = *item.PaymentMethod
	}
	if item.Status != nil {
		existing.Status = *item.Status
	}
	existing.SetDefaults()
	if err := existing.Validate(); err != nil {
		return domain.Reservation{}, err
	}

	property, err := s.propertyRepo.GetByID(existing.PropertyID)
	if err != nil {
		return domain.Reservation{}, err
	}
	if !property.Active {
		return domain.Reservation{}, fmt.Errorf("%w: imovel inativo", domain.ErrInvalidEntity)
	}

	guest, err := s.guestRepo.GetByID(existing.GuestID)
	if err != nil {
		return domain.Reservation{}, err
	}
	if !guest.Active {
		return domain.Reservation{}, fmt.Errorf("%w: hospede inativo", domain.ErrInvalidEntity)
	}

	totalValue, err := calculateTotalValue(property.DailyRate, existing.StartDate, existing.EndDate)
	if err != nil {
		return domain.Reservation{}, err
	}

	hasOverlap, err := s.hasOverlap(id, existing.PropertyID, existing.StartDate, existing.EndDate)
	if err != nil {
		return domain.Reservation{}, err
	}
	if hasOverlap {
		return domain.Reservation{}, domain.ErrAlreadyExists
	}

	existing.TotalValue = totalValue

	return s.repo.Update(id, existing)
}

func (s *service) Confirm(id int, input ConfirmReservationInput) (domain.Reservation, error) {
	if id <= 0 {
		return domain.Reservation{}, domain.ErrInvalidEntity
	}

	item, err := s.repo.GetByID(id)
	if err != nil {
		return domain.Reservation{}, err
	}

	if item.Status == domain.ReservationStatusCancelled {
		return domain.Reservation{}, domain.ErrInvalidEntity
	}

	if s.paymentGate == nil {
		return domain.Reservation{}, domain.ErrInvalidEntity
	}

	payment, err := s.paymentGate.Authorize(paymentuc.AuthorizationInput{
		ReservationID: item.ID,
		Amount:        item.TotalValue,
		Method:        input.PaymentMethod,
	})
	if err != nil {
		return domain.Reservation{}, err
	}

	item.PaymentMethod = input.PaymentMethod
	item.PaymentStatus = payment.Status
	if payment.Status != domain.PaymentStatusApproved {
		item.Status = domain.ReservationStatusPending
		item.ConfirmedAt = ""
		item.SetDefaults()
		if err := item.Validate(); err != nil {
			return domain.Reservation{}, err
		}
		return s.repo.Update(id, item)
	}

	item.Status = domain.ReservationStatusConfirmed
	item.ConfirmedAt = payment.ApprovedAt
	item.SetDefaults()

	if err := item.Validate(); err != nil {
		return domain.Reservation{}, err
	}

	return s.repo.Update(id, item)
}

func (s *service) Delete(id int) error {
	if id <= 0 {
		return domain.ErrInvalidEntity
	}
	return s.repo.Delete(id)
}

func filterReservations(items []domain.Reservation, statusRaw, periodFromRaw, periodToRaw string) ([]domain.Reservation, error) {
	var periodFrom *time.Time
	if periodFromRaw != "" {
		parsed, err := time.Parse("2006-01-02", periodFromRaw)
		if err != nil {
			return nil, err
		}
		periodFrom = &parsed
	}

	var periodTo *time.Time
	if periodToRaw != "" {
		parsed, err := time.Parse("2006-01-02", periodToRaw)
		if err != nil {
			return nil, err
		}
		periodTo = &parsed
	}

	filtered := make([]domain.Reservation, 0, len(items))
	for _, item := range items {
		if statusRaw != "" && string(item.Status) != statusRaw {
			continue
		}

		if periodFrom != nil || periodTo != nil {
			startDate, startErr := time.Parse("2006-01-02", item.StartDate)
			endDate, endErr := time.Parse("2006-01-02", item.EndDate)
			if startErr != nil || endErr != nil {
				continue
			}
			if periodFrom != nil && endDate.Before(*periodFrom) {
				continue
			}
			if periodTo != nil && startDate.After(*periodTo) {
				continue
			}
		}

		filtered = append(filtered, item)
	}

	return filtered, nil
}

func calculateTotalValue(dailyRate float64, startDate string, endDate string) (float64, error) {
	start, err := time.Parse("2006-01-02", startDate)
	if err != nil {
		return 0, domain.ErrInvalidEntity
	}

	end, err := time.Parse("2006-01-02", endDate)
	if err != nil {
		return 0, domain.ErrInvalidEntity
	}

	nights := math.Ceil(end.Sub(start).Hours() / 24)
	if nights < 0 {
		return 0, domain.ErrInvalidEntity
	}

	return nights * dailyRate, nil
}

func (s *service) hasOverlap(excludeID int, propertyID int, startDate string, endDate string) (bool, error) {
	current, err := s.repo.GetByPropertyID(propertyID)
	if err != nil {
		return false, err
	}

	for _, item := range current {
		if item.ID == excludeID || item.Status == domain.ReservationStatusCancelled {
			continue
		}

		overlap, err := datesOverlap(startDate, endDate, item.StartDate, item.EndDate)
		if err != nil {
			return false, err
		}
		if overlap {
			return true, nil
		}
	}

	return false, nil
}

func datesOverlap(startA string, endA string, startB string, endB string) (bool, error) {
	parsedStartA, err := time.Parse("2006-01-02", startA)
	if err != nil {
		return false, domain.ErrInvalidEntity
	}
	parsedEndA, err := time.Parse("2006-01-02", endA)
	if err != nil {
		return false, domain.ErrInvalidEntity
	}
	parsedStartB, err := time.Parse("2006-01-02", startB)
	if err != nil {
		return false, domain.ErrInvalidEntity
	}
	parsedEndB, err := time.Parse("2006-01-02", endB)
	if err != nil {
		return false, domain.ErrInvalidEntity
	}

	return parsedStartA.Before(parsedEndB) && parsedEndA.After(parsedStartB), nil
}
