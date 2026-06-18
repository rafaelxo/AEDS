package auth

import (
	"backend/internal/domain"
	"crypto/rand"
	"encoding/hex"
	"strings"
	"sync"
	"time"
)

type service struct {
	userSvc     UserService
	propertySvc PropertyService
	sessions    map[string]int
	mu          sync.RWMutex
}

func NewService(userSvc UserService, propertySvc PropertyService) Service {
	return &service{
		userSvc:     userSvc,
		propertySvc: propertySvc,
		sessions:    map[string]int{},
	}
}

func (s *service) Register(input RegisterInput) (Session, error) {
	userType := domain.UserTypeGuest
	if input.CreateAsHost {
		userType = domain.UserTypeHost
		if input.InitialProperty == nil {
			return Session{}, domain.ErrInvalidEntity
		}

		previewProperty := *input.InitialProperty
		previewProperty.UserID = 1
		previewProperty.Active = true
		if previewProperty.CreatedAt == "" {
			previewProperty.CreatedAt = time.Now().Format("2006-01-02")
		}
		if err := previewProperty.Validate(); err != nil {
			return Session{}, err
		}
	}

	user, err := s.userSvc.Create(domain.User{
		Name:     strings.TrimSpace(input.Name),
		Email:    strings.TrimSpace(strings.ToLower(input.Email)),
		Phone:    strings.TrimSpace(input.Phone),
		Password: input.Password,
		Type:     userType,
		Active:   true,
	})
	if err != nil {
		return Session{}, err
	}

	if input.CreateAsHost && input.InitialProperty != nil {
		propertyPayload := *input.InitialProperty
		propertyPayload.UserID = user.ID
		propertyPayload.Active = true
		if propertyPayload.CreatedAt == "" {
			propertyPayload.CreatedAt = time.Now().Format("2006-01-02")
		}
		createdProperty, err := s.propertySvc.Create(propertyPayload)
		if err != nil {
			_ = s.userSvc.Delete(user.ID)
			return Session{}, err
		}
		if createdProperty.UserID != user.ID {
			_ = s.propertySvc.Delete(createdProperty.ID)
			_ = s.userSvc.Delete(user.ID)
			return Session{}, domain.ErrInvalidEntity
		}
	}

	token, err := generateToken()
	if err != nil {
		return Session{}, err
	}

	s.mu.Lock()
	s.sessions[token] = user.ID
	s.mu.Unlock()

	return Session{Token: token, User: user}, nil
}

func (s *service) Login(input LoginInput) (Session, error) {
	user, err := s.userSvc.GetByEmail(strings.TrimSpace(strings.ToLower(input.Email)))
	if err != nil {
		return Session{}, err
	}
	if !user.Active || user.Password != input.Password {
		return Session{}, domain.ErrInvalidEntity
	}

	token, err := generateToken()
	if err != nil {
		return Session{}, err
	}

	s.mu.Lock()
	s.sessions[token] = user.ID
	s.mu.Unlock()

	return Session{Token: token, User: user}, nil
}

func (s *service) GetUserByToken(token string) (domain.User, error) {
	s.mu.RLock()
	userID, ok := s.sessions[token]
	s.mu.RUnlock()
	if !ok {
		return domain.User{}, domain.ErrNotFound
	}
	return s.userSvc.GetByID(userID)
}

func (s *service) SeedDefaultAdmin() (domain.User, error) {
	return s.userSvc.SeedAdmin("Administrador", "admin@hostly.local", "admin123")
}

func generateToken() (string, error) {
	bytes := make([]byte, 24)
	if _, err := rand.Read(bytes); err != nil {
		return "", err
	}
	return hex.EncodeToString(bytes), nil
}
