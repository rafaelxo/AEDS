package payment

import "backend/internal/domain"

type AuthorizationInput struct {
	ReservationID int
	Amount        float64
	Method        domain.PaymentMethod
}

type AuthorizationResult struct {
	Status     domain.PaymentStatus
	ApprovedAt string
}

type Gateway interface {
	Authorize(input AuthorizationInput) (AuthorizationResult, error)
}
