package payment

import (
	"time"

	"backend/internal/domain"
	paymentuc "backend/internal/usecase/payment"
)

type SimulatedGateway struct{}

func NewSimulatedGateway() paymentuc.Gateway {
	return &SimulatedGateway{}
}

func (g *SimulatedGateway) Authorize(input paymentuc.AuthorizationInput) (paymentuc.AuthorizationResult, error) {
	return paymentuc.AuthorizationResult{
		Status:     domain.PaymentStatusApproved,
		ApprovedAt: time.Now().Format(time.RFC3339),
	}, nil
}
