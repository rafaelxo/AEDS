package repository

import (
	"backend/internal/adapters/sorting"
	"backend/internal/domain"
	reservationuc "backend/internal/usecase/reservation"
	"errors"
	"strconv"
	"strings"
	"sync"
	"time"
)

type ReservationFileRepository struct {
	store          *binaryEntityStore[domain.Reservation]
	byPropertyID   *multiExtensibleHashIndex
	byGuestID      *multiExtensibleHashIndex
	byTerm         *multiExtensibleHashIndex
	propertyLookup func(id int) (domain.Property, error)
	userLookup     func(id int) (domain.User, error)
	mu             sync.Mutex
}

func NewReservationFileRepository(
	path string,
	propertyLookup func(id int) (domain.Property, error),
	userLookup func(id int) (domain.User, error),
) (*ReservationFileRepository, error) {
	store, err := newBinaryEntityStore(
		path,
		func(r domain.Reservation) int { return r.ID },
		func(r *domain.Reservation, id int) { r.ID = id },
		reservationPayloadCodec(),
	)
	if err != nil {
		return nil, err
	}

	byPropertyID, err := newMultiExtensibleHashIndex(path+".byproperty.ridx", 8)
	if err != nil {
		return nil, err
	}
	byGuestID, err := newMultiExtensibleHashIndex(path+".byguest.ridx", 8)
	if err != nil {
		return nil, err
	}
	byTerm, err := newMultiExtensibleHashIndex(path+".byterm.ridx", 8)
	if err != nil {
		return nil, err
	}

	repo := &ReservationFileRepository{
		store:          store,
		byPropertyID:   byPropertyID,
		byGuestID:      byGuestID,
		byTerm:         byTerm,
		propertyLookup: propertyLookup,
		userLookup:     userLookup,
	}
	if err := repo.rebuildIndexes(); err != nil {
		return nil, err
	}
	return repo, nil
}

func (r *ReservationFileRepository) HashStats() HashIndexStats {
	return r.store.HashStats()
}

func (r *ReservationFileRepository) Create(item domain.Reservation) (domain.Reservation, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	created, err := r.store.Create(item)
	if err != nil {
		return domain.Reservation{}, err
	}
	r.byPropertyID.Insert(created.PropertyID, int64(created.ID))
	r.byGuestID.Insert(created.GuestID, int64(created.ID))
	r.indexTermsLocked(created)
	r.syncIndexesLocked()
	return created, nil
}

func (r *ReservationFileRepository) GetByID(id int) (domain.Reservation, error) {
	return r.store.GetByID(id)
}

func (r *ReservationFileRepository) GetAll() ([]domain.Reservation, error) {
	return r.store.GetAll()
}

func (r *ReservationFileRepository) GetByPropertyID(propertyID int) ([]domain.Reservation, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	ids, ok := r.byPropertyID.Get(propertyID)
	if !ok {
		return []domain.Reservation{}, nil
	}
	items := make([]domain.Reservation, 0, len(ids))
	dirty := false
	for _, id := range ids {
		item, err := r.store.GetByID(int(id))
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				r.byPropertyID.Delete(propertyID, id)
				dirty = true
				continue
			}
			return nil, err
		}
		items = append(items, item)
	}
	if dirty {
		r.syncIndexesLocked()
	}
	return items, nil
}

func (r *ReservationFileRepository) GetByGuestID(guestID int) ([]domain.Reservation, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	ids, ok := r.byGuestID.Get(guestID)
	if !ok {
		return []domain.Reservation{}, nil
	}
	items := make([]domain.Reservation, 0, len(ids))
	dirty := false
	for _, id := range ids {
		item, err := r.store.GetByID(int(id))
		if err != nil {
			if errors.Is(err, domain.ErrNotFound) {
				r.byGuestID.Delete(guestID, id)
				dirty = true
				continue
			}
			return nil, err
		}
		items = append(items, item)
	}
	if dirty {
		r.syncIndexesLocked()
	}
	return items, nil
}

func (r *ReservationFileRepository) Update(id int, item domain.Reservation) (domain.Reservation, error) {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return domain.Reservation{}, err
	}
	updated, err := r.store.Update(id, item)
	if err != nil {
		return domain.Reservation{}, err
	}
	if existing.PropertyID != updated.PropertyID {
		r.byPropertyID.Delete(existing.PropertyID, int64(existing.ID))
		r.byPropertyID.Insert(updated.PropertyID, int64(updated.ID))
	}
	if existing.GuestID != updated.GuestID {
		r.byGuestID.Delete(existing.GuestID, int64(existing.ID))
		r.byGuestID.Insert(updated.GuestID, int64(updated.ID))
	}
	r.unindexTermsLocked(existing)
	r.indexTermsLocked(updated)
	r.syncIndexesLocked()
	return updated, nil
}

func (r *ReservationFileRepository) Delete(id int) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	existing, err := r.store.GetByID(id)
	if err != nil {
		return err
	}
	if err := r.store.Delete(id); err != nil {
		return err
	}
	r.byPropertyID.Delete(existing.PropertyID, int64(existing.ID))
	r.byGuestID.Delete(existing.GuestID, int64(existing.ID))
	r.unindexTermsLocked(existing)
	r.syncIndexesLocked()
	return nil
}

func (r *ReservationFileRepository) Search(query string, status string) ([]domain.Reservation, error) {
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

	var items []domain.Reservation
	if candidates == nil {
		all, err := r.store.GetAll()
		if err != nil {
			return nil, err
		}
		items = all
	} else {
		loaded, err := r.loadReservationsByIDsLocked(candidates)
		if err != nil {
			return nil, err
		}
		items = loaded
	}

	status = strings.TrimSpace(status)
	filtered := make([]domain.Reservation, 0, len(items))
	for _, item := range items {
		if status != "" && string(item.Status) != status {
			continue
		}
		if len(terms) > 0 && !r.matchesReservationTerms(item, terms) {
			continue
		}
		filtered = append(filtered, item)
	}
	return filtered, nil
}

func (r *ReservationFileRepository) SortFileBy(e *sorting.Engine, attr string, asc bool) error {
	r.mu.Lock()
	defer r.mu.Unlock()

	all, err := r.store.GetAll()
	if err != nil {
		return err
	}

	sorted, err := sorting.SortExternal(e, "reservas", all, reservationSortKeyFn(attr), asc)
	if err != nil {
		return err
	}

	if err := r.store.RewriteSorted(sorted); err != nil {
		return err
	}

	return r.rebuildIndexes()
}

func reservationSortKeyFn(attr string) func(domain.Reservation) (float64, int) {
	parseDate := func(s string) float64 {
		t, err := time.Parse("2006-01-02", s)
		if err != nil {
			return 0
		}
		return float64(t.Unix())
	}
	switch attr {
	case "valorTotal":
		return func(r domain.Reservation) (float64, int) { return r.TotalValue, r.ID }
	case "dataFim":
		return func(r domain.Reservation) (float64, int) { return parseDate(r.EndDate), r.ID }
	default:
		return func(r domain.Reservation) (float64, int) { return parseDate(r.StartDate), r.ID }
	}
}

func (r *ReservationFileRepository) rebuildIndexes() error {
	items, err := r.store.GetAll()
	if err != nil {
		return err
	}
	r.byPropertyID.Reset()
	r.byGuestID.Reset()
	r.byTerm.Reset()
	for _, item := range items {
		r.byPropertyID.Insert(item.PropertyID, int64(item.ID))
		r.byGuestID.Insert(item.GuestID, int64(item.ID))
		r.indexTermsLocked(item)
	}
	return r.flushIndexes()
}

func (r *ReservationFileRepository) rebuildTermIndexLocked() error {
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

func (r *ReservationFileRepository) loadReservationsByIDsLocked(ids map[int]struct{}) ([]domain.Reservation, error) {
	items := make([]domain.Reservation, 0, len(ids))
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

func (r *ReservationFileRepository) matchesReservationTerms(item domain.Reservation, terms []string) bool {
	tokens := make(map[string]struct{})
	for _, token := range r.reservationTokens(item) {
		tokens[token] = struct{}{}
	}
	for _, term := range terms {
		if _, ok := tokens[term]; !ok {
			return false
		}
	}
	return true
}

func (r *ReservationFileRepository) reservationTokens(item domain.Reservation) []string {
	fields := []string{
		strconv.Itoa(item.ID),
		strconv.Itoa(item.PropertyID),
		strconv.Itoa(item.GuestID),
		string(item.Status),
		item.StartDate,
		item.EndDate,
	}

	if r.propertyLookup != nil {
		if property, err := r.propertyLookup(item.PropertyID); err == nil {
			fields = append(fields, property.Title)
			if r.userLookup != nil {
				if host, hostErr := r.userLookup(property.UserID); hostErr == nil {
					fields = append(fields, host.Name, strconv.Itoa(host.ID))
				}
			}
		}
	}
	if r.userLookup != nil {
		if guest, err := r.userLookup(item.GuestID); err == nil {
			fields = append(fields, guest.Name, strconv.Itoa(guest.ID))
		}
	}

	return tokenizeForSearch(fields...)
}

func (r *ReservationFileRepository) indexTermsLocked(item domain.Reservation) {
	for _, token := range r.reservationTokens(item) {
		r.byTerm.Insert(tokenKey(token), int64(item.ID))
	}
}

func (r *ReservationFileRepository) unindexTermsLocked(item domain.Reservation) {
	for _, token := range r.reservationTokens(item) {
		r.byTerm.Delete(tokenKey(token), int64(item.ID))
	}
}

func (r *ReservationFileRepository) flushIndexes() error {
	if err := r.byPropertyID.persistToFile(); err != nil {
		return err
	}
	if err := r.byGuestID.persistToFile(); err != nil {
		return err
	}
	return r.byTerm.persistToFile()
}

func (r *ReservationFileRepository) syncIndexesLocked() {
	if err := r.flushIndexes(); err == nil {
		return
	}
	_ = r.rebuildIndexes()
}

var _ reservationuc.Repository = (*ReservationFileRepository)(nil)
