package user

import (
	"backend/internal/domain"
	"strings"
)

type ListFilter struct {
	Query string
}

type UserPatch struct {
	Name     *string
	Email    *string
	Phone    *string
	Password *string
	Type     *domain.UserType
	Active   *bool
}

func (s *service) Create(item domain.User) (domain.User, error) {
	if item.Type == "" {
		item.Type = domain.UserTypeGuest
	}
	if item.Password == "" {
		return domain.User{}, domain.ErrInvalidEntity
	}
	if exists, err := s.emailInUse(item.Email, 0); err != nil {
		return domain.User{}, err
	} else if exists {
		return domain.User{}, domain.ErrEmailInUse
	}

	if err := item.Validate(); err != nil {
		return domain.User{}, err
	}
	return s.repo.Create(item)
}

func (s *service) GetByID(id int) (domain.User, error) {
	if id <= 0 {
		return domain.User{}, domain.ErrInvalidEntity
	}
	return s.repo.GetByID(id)
}

func (s *service) GetByEmail(email string) (domain.User, error) {
	if email == "" {
		return domain.User{}, domain.ErrInvalidEntity
	}
	return s.repo.GetByEmail(email)
}

func (s *service) GetAllHosts() ([]domain.User, error) {
	users, err := s.repo.GetAll()
	if err != nil {
		return nil, err
	}

	hosts := make([]domain.User, 0, len(users))
	seen := make(map[string]struct{}, len(users))
	for _, u := range users {
		if u.Type == domain.UserTypeHost && u.Active {
			key := userEmailKey(u.Email)
			if _, ok := seen[key]; ok {
				continue
			}
			seen[key] = struct{}{}
			hosts = append(hosts, u)
		}
	}
	return hosts, nil
}

func (s *service) GetAll() ([]domain.User, error) {
	users, err := s.repo.GetAll()
	if err != nil {
		return nil, err
	}

	activeUsers := make([]domain.User, 0, len(users))
	seen := make(map[string]struct{}, len(users))
	for _, u := range users {
		if u.Active {
			key := userEmailKey(u.Email)
			if _, ok := seen[key]; ok {
				continue
			}
			seen[key] = struct{}{}
			activeUsers = append(activeUsers, u)
		}
	}
	return activeUsers, nil
}

type userSearcher interface {
	Search(query string) ([]domain.User, error)
}

func (s *service) List(filter ListFilter) ([]domain.User, error) {
	var (
		users []domain.User
		err   error
	)

	if searcher, ok := s.repo.(userSearcher); ok {
		users, err = searcher.Search(filter.Query)
	} else {
		users, err = s.repo.GetAll()
	}
	if err != nil {
		return nil, err
	}

	activeUsers := make([]domain.User, 0, len(users))
	seen := make(map[string]struct{}, len(users))
	for _, u := range users {
		if u.Active {
			key := userEmailKey(u.Email)
			if _, ok := seen[key]; ok {
				continue
			}
			seen[key] = struct{}{}
			activeUsers = append(activeUsers, u)
		}
	}
	return activeUsers, nil
}

func (s *service) Update(id int, item domain.User) (domain.User, error) {
	if id <= 0 {
		return domain.User{}, domain.ErrInvalidEntity
	}
	item.ID = id
	if item.Type == "" {
		item.Type = domain.UserTypeHost
	}
	if exists, err := s.emailInUse(item.Email, id); err != nil {
		return domain.User{}, err
	} else if exists {
		return domain.User{}, domain.ErrEmailInUse
	}
	if err := item.Validate(); err != nil {
		return domain.User{}, err
	}
	return s.repo.Update(id, item)
}

func (s *service) Patch(id int, p UserPatch) (domain.User, error) {
	existing, err := s.repo.GetByID(id)
	if err != nil {
		return domain.User{}, err
	}
	if p.Name != nil {
		existing.Name = *p.Name
	}
	if p.Email != nil {
		existing.Email = *p.Email
	}
	if p.Phone != nil {
		existing.Phone = *p.Phone
	}
	if p.Password != nil {
		existing.Password = *p.Password
	}
	if p.Type != nil {
		existing.Type = *p.Type
	}
	if p.Active != nil {
		existing.Active = *p.Active
	}
	return s.Update(id, existing)
}

func (s *service) Delete(id int) error {
	if id <= 0 {
		return domain.ErrInvalidEntity
	}
	return s.repo.Delete(id)
}

func (s *service) SeedAdmin(name string, email string, password string) (domain.User, error) {
	existing, err := s.repo.GetByEmail(email)
	if err == nil {
		return existing, nil
	}

	admin := domain.User{
		Name:     name,
		Email:    email,
		Phone:    "",
		Password: password,
		Type:     domain.UserTypeAdmin,
		Active:   true,
	}

	if err := admin.Validate(); err != nil {
		return domain.User{}, err
	}

	return s.repo.Create(admin)
}

func (s *service) emailInUse(email string, ignoreID int) (bool, error) {
	key := userEmailKey(email)
	users, err := s.repo.GetAll()
	if err != nil {
		return false, err
	}
	for _, existing := range users {
		if existing.ID == ignoreID || !existing.Active {
			continue
		}
		if userEmailKey(existing.Email) == key {
			return true, nil
		}
	}
	return false, nil
}

func userEmailKey(email string) string {
	return strings.ToLower(strings.TrimSpace(email))
}
