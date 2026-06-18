package repository

import (
	"backend/internal/adapters/sorting"
	"backend/internal/domain"
	"errors"
	"strconv"
	"strings"
	"sync"
	"time"
)

type PropertyFileRepository struct {
	store       *binaryEntityStore[domain.Property]
	byUserID    *multiExtensibleHashIndex
	byTerm      *multiExtensibleHashIndex
	ownerLookup func(id int) (domain.User, error)
	mu          sync.Mutex
}

func NewPropertyFileRepository(path string, ownerLookup func(id int) (domain.User, error)) (*PropertyFileRepository, error) {
	store, err := newBinaryEntityStore(
		path,
		func(p domain.Property) int { return p.ID },
		func(p *domain.Property, id int) { p.ID = id },
		propertyPayloadCodec(),
	)
	if err != nil {
		return nil, err
	}

	byUserID, err := newMultiExtensibleHashIndex(path+".byuser.ridx", 8)
	if err != nil {
		return nil, err
	}
	byTerm, err := newMultiExtensibleHashIndex(path+".byterm.ridx", 8)
	if err != nil {
		return nil, err
	}

	repo := &PropertyFileRepository{
		store:       store,
		byUserID:    byUserID,
		byTerm:      byTerm,
		ownerLookup: ownerLookup,
	}
	if err := repo.rebuildRelationIndexes(); err != nil {
		return nil, err
	}
	return repo, nil
}

func (r *PropertyFileRepository) HashStats() HashIndexStats {
	return r.store.HashStats()
}

func (r *PropertyFileRepository) Create(item domain.Property) (domain.Property, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	created, err := r.store.Create(item)
	if err != nil {
		return domain.Property{}, err
	}
	r.byUserID.Insert(created.UserID, int64(created.ID))
	r.indexTermsLocked(created)
	r.syncRelationIndexesLocked()
	return created, nil
}

func (r *PropertyFileRepository) GetByID(id int) (domain.Property, error) {
	return r.store.GetByID(id)
}

func (r *PropertyFileRepository) GetAll() ([]domain.Property, error) {
	return r.store.GetAll()
}

func (r *PropertyFileRepository) GetByOwnerID(ownerID int) ([]domain.Property, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	ids, ok := r.byUserID.Get(ownerID)
	if !ok {
		return []domain.Property{}, nil
	}
	items := make([]domain.Property, 0, len(ids))
	dirty := false
	for _, id := range ids {
		item, err := r.store.GetByID(int(id))
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				r.byUserID.Delete(ownerID, id)
				dirty = true
				continue
			}
			return nil, err
		}
		items = append(items, item)
	}
	if dirty {
		r.syncRelationIndexesLocked()
	}
	return items, nil
}

func (r *PropertyFileRepository) Update(id int, item domain.Property) (domain.Property, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return domain.Property{}, err
	}
	updated, err := r.store.Update(id, item)
	if err != nil {
		return domain.Property{}, err
	}
	r.byUserID.Delete(existing.UserID, int64(existing.ID))
	r.byUserID.Insert(updated.UserID, int64(updated.ID))
	r.unindexTermsLocked(existing)
	r.indexTermsLocked(updated)
	r.syncRelationIndexesLocked()
	return updated, nil
}

func (r *PropertyFileRepository) Delete(id int) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return err
	}
	if err := r.store.Delete(id); err != nil {
		return err
	}
	r.byUserID.Delete(existing.UserID, int64(existing.ID))
	r.unindexTermsLocked(existing)
	r.syncRelationIndexesLocked()
	return nil
}

func (r *PropertyFileRepository) Search(ownerID *int, city string, minRate *float64, maxRate *float64, query string, includeInactive bool) ([]domain.Property, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	if strings.TrimSpace(query) != "" {
		if err := r.rebuildTermIndexLocked(); err != nil {
			return nil, err
		}
	}

	var candidateIDs map[int]struct{}
	if ownerID != nil {
		ids, ok := r.byUserID.Get(*ownerID)
		candidateIDs = make(map[int]struct{}, len(ids))
		if ok {
			for _, id := range ids {
				candidateIDs[int(id)] = struct{}{}
			}
		}
	}

	terms := splitQueryTokens(query)
	for _, term := range terms {
		ids, ok := r.byTerm.Get(tokenKey(term))
		next := make(map[int]struct{}, len(ids))
		if ok {
			for _, id := range ids {
				next[int(id)] = struct{}{}
			}
		}
		candidateIDs = intersectIDs(candidateIDs, next)
	}

	var items []domain.Property
	if candidateIDs == nil {
		all, err := r.store.GetAll()
		if err != nil {
			return nil, err
		}
		items = all
	} else {
		loaded, err := r.loadPropertiesByIDsLocked(candidateIDs)
		if err != nil {
			return nil, err
		}
		items = loaded
	}

	city = normalizeForSearch(city)
	filtered := make([]domain.Property, 0, len(items))
	for _, item := range items {
		if ownerID != nil && item.UserID != *ownerID {
			continue
		}
		if !includeInactive && !item.Active {
			continue
		}
		if city != "" && !strings.Contains(normalizeForSearch(item.City), city) {
			continue
		}
		if minRate != nil && item.DailyRate < *minRate {
			continue
		}
		if maxRate != nil && item.DailyRate > *maxRate {
			continue
		}
		if len(terms) > 0 && !r.matchesPropertyTerms(item, terms) {
			continue
		}
		filtered = append(filtered, item)
	}
	return filtered, nil
}

func (r *PropertyFileRepository) rebuildRelationIndexes() error {
	items, err := r.store.GetAll()
	if err != nil {
		return err
	}
	r.byUserID.Reset()
	r.byTerm.Reset()
	for _, item := range items {
		r.byUserID.Insert(item.UserID, int64(item.ID))
		r.indexTermsLocked(item)
	}
	return r.flushRelationIndexes()
}

func (r *PropertyFileRepository) rebuildTermIndexLocked() error {
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

func (r *PropertyFileRepository) loadPropertiesByIDsLocked(ids map[int]struct{}) ([]domain.Property, error) {
	items := make([]domain.Property, 0, len(ids))
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
		_ = r.rebuildRelationIndexes()
	}
	return items, nil
}

func (r *PropertyFileRepository) matchesPropertyTerms(item domain.Property, terms []string) bool {
	tokens := make(map[string]struct{})
	for _, token := range r.propertyTokens(item) {
		tokens[token] = struct{}{}
	}
	for _, term := range terms {
		if _, ok := tokens[term]; !ok {
			return false
		}
	}
	return true
}

func (r *PropertyFileRepository) propertyTokens(item domain.Property) []string {
	fields := []string{
		item.Title,
		item.City,
		item.Address.Street,
		item.Address.Neighborhood,
		strconv.Itoa(item.UserID),
	}
	if r.ownerLookup != nil {
		if owner, err := r.ownerLookup(item.UserID); err == nil {
			fields = append(fields, owner.Name)
		}
	}
	return tokenizeForSearch(fields...)
}

func (r *PropertyFileRepository) indexTermsLocked(item domain.Property) {
	for _, token := range r.propertyTokens(item) {
		r.byTerm.Insert(tokenKey(token), int64(item.ID))
	}
}

func (r *PropertyFileRepository) unindexTermsLocked(item domain.Property) {
	for _, token := range r.propertyTokens(item) {
		r.byTerm.Delete(tokenKey(token), int64(item.ID))
	}
}

func (r *PropertyFileRepository) flushRelationIndexes() error {
	if err := r.byUserID.persistToFile(); err != nil {
		return err
	}
	return r.byTerm.persistToFile()
}

func intersectIDs(left map[int]struct{}, right map[int]struct{}) map[int]struct{} {
	if left == nil {
		return right
	}
	if right == nil {
		return left
	}
	if len(left) > len(right) {
		left, right = right, left
	}
	out := make(map[int]struct{})
	for id := range left {
		if _, ok := right[id]; ok {
			out[id] = struct{}{}
		}
	}
	return out
}

func (r *PropertyFileRepository) rebuildByUserIndex() error {
	r.byUserID.Reset()
	items, err := r.store.GetAll()
	if err != nil {
		return err
	}
	for _, item := range items {
		r.byUserID.Insert(item.UserID, int64(item.ID))
	}
	return r.byUserID.persistToFile()
}

func (r *PropertyFileRepository) SortFileBy(e *sorting.Engine, attr string, asc bool) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	all, err := r.store.GetAll()
	if err != nil {
		return err
	}

	sorted, err := sorting.SortExternal(e, "imoveis", all, propertySortKeyFn(attr), asc)
	if err != nil {
		return err
	}

	if err := r.store.RewriteSorted(sorted); err != nil {
		return err
	}

	return r.rebuildRelationIndexes()
}

func propertySortKeyFn(attr string) func(domain.Property) (float64, int) {
	switch attr {
	case "dataCadastro":
		return func(p domain.Property) (float64, int) {
			t, err := time.Parse("2006-01-02", p.CreatedAt)
			if err != nil {
				return 0, p.ID
			}
			return float64(t.Unix()), p.ID
		}
	default:
		return func(p domain.Property) (float64, int) { return p.DailyRate, p.ID }
	}
}

func (r *PropertyFileRepository) syncRelationIndexesLocked() {
	if err := r.flushRelationIndexes(); err == nil {
		return
	}
	_ = r.rebuildRelationIndexes()
}
