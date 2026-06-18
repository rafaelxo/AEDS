package domain

import (
	"fmt"
	"strings"
	"time"
)

type ReservationStatus string

const (
	ReservationStatusPending   ReservationStatus = "PENDENTE"
	ReservationStatusConfirmed ReservationStatus = "CONFIRMADA"
	ReservationStatusCancelled ReservationStatus = "CANCELADA"
)

type PaymentMethod string

const (
	PaymentMethodPIX        PaymentMethod = "PIX"
	PaymentMethodCreditCard PaymentMethod = "CARTAO_CREDITO"
	PaymentMethodDebitCard  PaymentMethod = "CARTAO_DEBITO"
	PaymentMethodBankSlip   PaymentMethod = "BOLETO"
	PaymentMethodCash       PaymentMethod = "DINHEIRO"
)

type PaymentStatus string

const (
	PaymentStatusNotStarted PaymentStatus = "NAO_INICIADO"
	PaymentStatusPending    PaymentStatus = "PENDENTE"
	PaymentStatusApproved   PaymentStatus = "APROVADO"
	PaymentStatusFailed     PaymentStatus = "FALHOU"
)

type Reservation struct {
	ID            int               `json:"idReserva"`
	PropertyID    int               `json:"idImovel"`
	GuestID       int               `json:"idHospede"`
	StartDate     string            `json:"dataInicio"`
	EndDate       string            `json:"dataFim"`
	TotalValue    float64           `json:"valorTotal"`
	Status        ReservationStatus `json:"status"`
	PaymentMethod PaymentMethod     `json:"formaPagamento"`
	PaymentStatus PaymentStatus     `json:"statusPagamento"`
	ConfirmedAt   string            `json:"confirmadaEm,omitempty"`
}

func (r *Reservation) SetDefaults() {
	if r.Status == "" {
		r.Status = ReservationStatusPending
	}
	if r.PaymentStatus == "" {
		r.PaymentStatus = PaymentStatusNotStarted
	}
	r.PaymentMethod = PaymentMethod(strings.TrimSpace(string(r.PaymentMethod)))
	if r.Status != ReservationStatusConfirmed {
		r.ConfirmedAt = ""
	}
}

func (r Reservation) Validate() error {
	if r.PropertyID <= 0 {
		return fmt.Errorf("%w: idImovel invalido", ErrInvalidEntity)
	}
	if r.GuestID <= 0 {
		return fmt.Errorf("%w: idHospede invalido", ErrInvalidEntity)
	}
	if r.TotalValue < 0 {
		return fmt.Errorf("%w: valorTotal invalido", ErrInvalidEntity)
	}

	start, err := time.Parse("2006-01-02", r.StartDate)
	if err != nil {
		return fmt.Errorf("%w: dataInicio invalida (use YYYY-MM-DD)", ErrInvalidEntity)
	}
	end, err := time.Parse("2006-01-02", r.EndDate)
	if err != nil {
		return fmt.Errorf("%w: dataFim invalida (use YYYY-MM-DD)", ErrInvalidEntity)
	}
	if !end.After(start) {
		return fmt.Errorf("%w: dataFim deve ser posterior a dataInicio", ErrInvalidEntity)
	}

	if !isValidReservationStatus(r.Status) {
		return fmt.Errorf("%w: status de reserva invalido", ErrInvalidEntity)
	}

	if !isValidPaymentStatus(r.PaymentStatus) {
		return fmt.Errorf("%w: status de pagamento invalido", ErrInvalidEntity)
	}

	if r.PaymentMethod != "" && !isValidPaymentMethod(r.PaymentMethod) {
		return fmt.Errorf("%w: forma de pagamento invalida", ErrInvalidEntity)
	}

	if r.Status == ReservationStatusConfirmed {
		if !isValidPaymentMethod(r.PaymentMethod) {
			return fmt.Errorf("%w: reserva confirmada exige forma de pagamento valida", ErrInvalidEntity)
		}
		if r.PaymentStatus != PaymentStatusApproved {
			return fmt.Errorf("%w: reserva confirmada exige pagamento aprovado", ErrInvalidEntity)
		}
		if r.ConfirmedAt == "" {
			return fmt.Errorf("%w: reserva confirmada exige data de confirmacao", ErrInvalidEntity)
		}
		if _, err := time.Parse(time.RFC3339, r.ConfirmedAt); err != nil {
			return fmt.Errorf("%w: confirmadaEm invalida (use RFC3339)", ErrInvalidEntity)
		}
	}

	return nil
}

func isValidReservationStatus(value ReservationStatus) bool {
	switch value {
	case ReservationStatusPending, ReservationStatusConfirmed, ReservationStatusCancelled:
		return true
	default:
		return false
	}
}

func isValidPaymentStatus(value PaymentStatus) bool {
	switch value {
	case PaymentStatusNotStarted, PaymentStatusPending, PaymentStatusApproved, PaymentStatusFailed:
		return true
	default:
		return false
	}
}

func isValidPaymentMethod(value PaymentMethod) bool {
	switch value {
	case PaymentMethodPIX, PaymentMethodCreditCard, PaymentMethodDebitCard, PaymentMethodBankSlip, PaymentMethodCash:
		return true
	default:
		return false
	}
}
