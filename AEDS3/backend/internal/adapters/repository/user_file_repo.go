package repository

import (
	"backend/internal/domain"
	"errors"
	"strconv"
	"strings"
	"sync"
)

type UserFileRepository struct {
	store  *binaryEntityStore[domain.User]
	byTerm *multiExtensibleHashIndex
	mu     sync.Mutex
}

func NewUserFileRepository(path string) (*UserFileRepository, error) {
	store, err := newBinaryEntityStore(
		path,
		func(u domain.User) int { return u.ID },
		func(u *domain.User, id int) { u.ID = id },
		userPayloadCodec(),
	)
	if err != nil {
		return nil, err
	}

	byTerm, err := newMultiExtensibleHashIndex(path+".byterm.ridx", 8)
	if err != nil {
		return nil, err
	}

	repo := &UserFileRepository{
		store:  store,
		byTerm: byTerm,
	}
	if err := repo.rebuildIndexes(); err != nil {
		return nil, err
	}
	return repo, nil
}

func (r *UserFileRepository) HashStats() HashIndexStats {
	return r.store.HashStats()
}

func (r *UserFileRepository) Create(item domain.User) (domain.User, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	created, err := r.store.Create(item)
	if err != nil {
		return domain.User{}, err
	}
	r.indexTermsLocked(created)
	r.syncIndexesLocked()
	return created, nil
}

func (r *UserFileRepository) GetByID(id int) (domain.User, error) {
	return r.store.GetByID(id)
}

func (r *UserFileRepository) GetByEmail(email string) (domain.User, error) {
	all, err := r.store.GetAll()
	if err != nil {
		return domain.User{}, err
	}

	normalized := strings.TrimSpace(strings.ToLower(email))
	for _, item := range all {
		if !item.Active {
			continue
		}
		if strings.ToLower(strings.TrimSpace(item.Email)) == normalized {
			return item, nil
		}
	}

	return domain.User{}, domain.ErrNotFound
}

func (r *UserFileRepository) GetAll() ([]domain.User, error) {
	return r.store.GetAll()
}

func (r *UserFileRepository) Update(id int, item domain.User) (domain.User, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return domain.User{}, err
	}
	updated, err := r.store.Update(id, item)
	if err != nil {
		return domain.User{}, err
	}
	r.unindexTermsLocked(existing)
	r.indexTermsLocked(updated)
	r.syncIndexesLocked()
	return updated, nil
}

func (r *UserFileRepository) Delete(id int) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return err
	}
	if err := r.store.Delete(id); err != nil {
		return err
	}
	r.unindexTermsLocked(existing)
	r.syncIndexesLocked()
	return nil
}

func (r *UserFileRepository) Search(query string) ([]domain.User, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	query = strings.TrimSpace(query)
	if query != "" {
		if err := r.rebuildTermIndexLocked(); err != nil {
			return nil, err
		}
	}

	var candidates map[int]struct{}
	terms := splitQueryTokens(query)
	for _, term := range terms {
		ids, ok := r.byTerm.Get(tokenKey(term))
		next := make(map[int]struct{}, len(ids))
		if ok {
			for _, id := range ids {
				next[int(id)] = struct{}{}
			}
		}
		candidates = intersectIDs(candidates, next)
	}

	var items []domain.User
	if candidates == nil {
		all, err := r.store.GetAll()
		if err != nil {
			return nil, err
		}
		items = all
	} else {
		loaded, err := r.loadUsersByIDsLocked(candidates)
		if err != nil {
			return nil, err
		}
		items = loaded
	}

	filtered := make([]domain.User, 0, len(items))
	for _, item := range items {
		if len(terms) > 0 && !r.matchesUserTerms(item, terms) {
			continue
		}
		filtered = append(filtered, item)
	}
	return filtered, nil
}

func (r *UserFileRepository) rebuildIndexes() error {
	r.byTerm.Reset()
	items, err := r.store.GetAll()
	if err != nil {
		return err
	}
	for _, item := range items {
		r.indexTermsLocked(item)
	}
	return r.flushIndexes()
}

func (r *UserFileRepository) rebuildTermIndexLocked() error {
	r.byTerm.Reset()
	items, err := r.store.GetAll()
	if err != nil {
		return err
	}
	for _, item := range items {
		r.indexTermsLocked(item)
	}
	return r.byTerm.persistToFile()
}

func (r *UserFileRepository) loadUsersByIDsLocked(ids map[int]struct{}) ([]domain.User, error) {
	items := make([]domain.User, 0, len(ids))
	dirty := false
	for id := range ids {
		item, err := r.store.GetByID(id)
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				dirty = true
				continue
			}
			return nil, err
		}
		items = append(items, item)
	}
	if dirty {
		_ = r.rebuildIndexes()
	}
	return items, nil
}

func (r *UserFileRepository) matchesUserTerms(item domain.User, terms []string) bool {
	tokens := make(map[string]struct{})
	for _, token := range r.userTokens(item) {
		tokens[token] = struct{}{}
	}
	for _, term := range terms {
		if _, ok := tokens[term]; !ok {
			return false
		}
	}
	return true
}

func (r *UserFileRepository) userTokens(item domain.User) []string {
	fields := []string{
		item.Name,
		item.Email,
		strconv.Itoa(item.ID),
		string(item.Type),
	}
	return tokenizeForSearch(fields...)
}

func (r *UserFileRepository) indexTermsLocked(item domain.User) {
	for _, token := range r.userTokens(item) {
		r.byTerm.Insert(tokenKey(token), int64(item.ID))
	}
}

func (r *UserFileRepository) unindexTermsLocked(item domain.User) {
	for _, token := range r.userTokens(item) {
		r.byTerm.Delete(tokenKey(token), int64(item.ID))
	}
}

func (r *UserFileRepository) flushIndexes() error {
	return r.byTerm.persistToFile()
}

func (r *UserFileRepository) syncIndexesLocked() {
	if err := r.flushIndexes(); err == nil {
		return
	}
	_ = r.rebuildIndexes()
}
