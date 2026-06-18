package aed

import (
	"backend/internal/domain"
)

type PropertyReader interface {
	GetByID(id int) (domain.Property, error)
	GetAll() ([]domain.Property, error)
	GetByOwnerID(ownerID int) ([]domain.Property, error)
}

type ReservationReader interface {
	GetByPropertyID(propertyID int) ([]domain.Reservation, error)
}

type HashStats struct {
	GlobalDepth int `json:"globalDepth"`
	Buckets     int `json:"buckets"`
	Entries     int `json:"entries"`
}

type HashDiagnostics struct {
	Imoveis  HashStats `json:"imoveis"`
	Usuarios HashStats `json:"usuarios"`
	Reservas HashStats `json:"reservas"`
}

type PropertyWithReservations struct {
	Imovel   domain.Property      `json:"imovel"`
	Reservas []domain.Reservation `json:"reservas"`
}

type HostRelationship struct {
	HostID             int                        `json:"idAnfitriao"`
	QuantidadeImoveis  int                        `json:"quantidadeImoveis"`
	QuantidadeReservas int                        `json:"quantidadeReservas"`
	ImoveisComReservas []PropertyWithReservations `json:"imoveisComReservas"`
}

type Service interface {
	HashDiagnostics() HashDiagnostics
	RelationshipByHost(hostID int) (HostRelationship, error)
}

type service struct {
	propertyReader    PropertyReader
	reservationReader ReservationReader
	propertyHash      func() HashStats
	userHash          func() HashStats
	reservationHash   func() HashStats
}

func NewService(
	propertyReader PropertyReader,
	reservationReader ReservationReader,
	propertyHash func() HashStats,
	userHash func() HashStats,
	reservationHash func() HashStats,
) Service {
	return &service{
		propertyReader:    propertyReader,
		reservationReader: reservationReader,
		propertyHash:      propertyHash,
		userHash:          userHash,
		reservationHash:   reservationHash,
	}
}

func (s *service) HashDiagnostics() HashDiagnostics {
	return HashDiagnostics{
		Imoveis:  s.propertyHash(),
		Usuarios: s.userHash(),
		Reservas: s.reservationHash(),
	}
}

func (s *service) RelationshipByHost(hostID int) (HostRelationship, error) {
	if hostID <= 0 {
		return HostRelationship{}, domain.ErrInvalidEntity
	}

	properties, err := s.propertyReader.GetByOwnerID(hostID)
	if err != nil {
		return HostRelationship{}, err
	}

	result := HostRelationship{
		HostID:             hostID,
		ImoveisComReservas: make([]PropertyWithReservations, 0, len(properties)),
	}

	for _, property := range properties {
		reservations, err := s.reservationReader.GetByPropertyID(property.ID)
		if err != nil {
			return HostRelationship{}, err
		}
		result.QuantidadeImoveis++
		result.QuantidadeReservas += len(reservations)
		result.ImoveisComReservas = append(result.ImoveisComReservas, PropertyWithReservations{
			Imovel:   property,
			Reservas: reservations,
		})
	}

	return result, nil
}
