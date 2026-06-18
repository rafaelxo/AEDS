package web

import (
	"backend/internal/adapters/compression"
	"backend/internal/adapters/patternmatch"
	"backend/internal/adapters/web/handler"
	aeduc "backend/internal/usecase/aed"
	amenityuc "backend/internal/usecase/amenity"
	authuc "backend/internal/usecase/auth"
	"backend/internal/usecase/property"
	propertyamenityuc "backend/internal/usecase/propertyamenity"
	reservationuc "backend/internal/usecase/reservation"
	useruc "backend/internal/usecase/user"
	"net/http"
	"sync"
)

type Dependencies struct {
	PropertyService        property.Service
	UserService            useruc.Service
	ReservationService     reservationuc.Service
	AuthService            authuc.Service
	AmenityService         amenityuc.Service
	PropertyAmenityService propertyamenityuc.Service
	AEDService             aeduc.Service
	Compressor             *compression.Engine
	PatternMatcher         *patternmatch.Engine
	SortImoveis            func(attr string, asc bool) error
	SortReservas           func(attr string, asc bool) error
}

func NewRouter(deps Dependencies) http.Handler {
	props := handler.NewPropertyHandler(deps.PropertyService, deps.SortImoveis)
	users := handler.NewUserHandler(deps.UserService)
	reservs := handler.NewReservationHandler(deps.ReservationService, deps.SortReservas)
	dash := handler.NewDashboardHandler(deps.PropertyService, deps.UserService, deps.ReservationService)
	auth := handler.NewAuthHandler(deps.AuthService)
	amenities := handler.NewAmenityHandler(deps.AmenityService)
	propertyAmenities := handler.NewPropertyAmenityHandler(deps.PropertyAmenityService)
	aed := handler.NewAEDHandler(deps.AEDService)
	backup := handler.NewBackupHandler(deps.Compressor)
	pm := handler.NewPatternMatchHandler(deps.PatternMatcher, deps.PropertyService, deps.UserService, deps.ReservationService)

	mux := http.NewServeMux()
	mux.HandleFunc("GET /health", func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusOK)
		_, _ = w.Write([]byte("ok"))
	})

	mux.HandleFunc("GET /imoveis", props.List)
	mux.HandleFunc("GET /imoveis/usuario/{idUsuario}", props.ListByOwner)
	mux.HandleFunc("POST /imoveis", props.Create)
	mux.HandleFunc("GET /imoveis/{id}", props.GetByID)
	mux.HandleFunc("PUT /imoveis/{id}", props.Update)
	mux.HandleFunc("DELETE /imoveis/{id}", props.Delete)

	mux.HandleFunc("GET /usuarios", users.List)
	mux.HandleFunc("POST /usuarios", users.Create)
	mux.HandleFunc("GET /usuarios/anfitrioes", users.ListHosts)
	mux.HandleFunc("GET /usuarios/{id}", users.GetByID)
	mux.HandleFunc("PUT /usuarios/{id}", users.Update)
	mux.HandleFunc("DELETE /usuarios/{id}", users.Delete)

	mux.HandleFunc("GET /reservas", reservs.List)
	mux.HandleFunc("GET /reservas/hospede/{idHospede}", reservs.ListByGuest)
	mux.HandleFunc("GET /reservas/anfitriao/{idAnfitriao}", reservs.ListByHost)
	mux.HandleFunc("POST /reservas", reservs.Create)
	mux.HandleFunc("GET /reservas/{id}", reservs.GetByID)
	mux.HandleFunc("PUT /reservas/{id}", reservs.Update)
	mux.HandleFunc("PUT /reservas/{id}/confirmar", reservs.Confirm)
	mux.HandleFunc("DELETE /reservas/{id}", reservs.Delete)

	mux.HandleFunc("POST /auth/register", auth.Register)
	mux.HandleFunc("POST /auth/login", auth.Login)
	mux.HandleFunc("GET /auth/me", auth.Me)

	mux.HandleFunc("GET /aed/diagnostico", aed.Diagnostico)
	mux.HandleFunc("GET /aed/anfitriao/{id}", aed.RelacaoAnfitriao)

	mux.HandleFunc("GET /backups", backup.List)
	mux.HandleFunc("POST /backup", backup.Create)
	mux.HandleFunc("POST /restaurar", backup.Restore)

	mux.HandleFunc("GET /busca/padrao", pm.Search)

	mux.HandleFunc("GET /dashboard/stats", dash.Stats)
	mux.HandleFunc("POST /imoveis-comodidades", propertyAmenities.Create)
	mux.HandleFunc("GET /imoveis-comodidades/imovel/{idImovel}", propertyAmenities.ListAmenitiesByProperty)
	mux.HandleFunc("GET /imoveis-comodidades/imovel/{idImovel}/comodidade/{idComodidade}", propertyAmenities.Get)
	mux.HandleFunc("DELETE /imoveis-comodidades/imovel/{idImovel}/comodidade/{idComodidade}", propertyAmenities.Delete)
	mux.HandleFunc("GET /imoveis-comodidades/comodidade/{idComodidade}/imoveis", propertyAmenities.ListPropertiesByAmenity)
	mux.HandleFunc("GET /comodidades", amenities.List)
	mux.HandleFunc("POST /comodidades", amenities.Create)
	mux.HandleFunc("GET /comodidades/{id}", amenities.GetByID)
	mux.HandleFunc("PUT /comodidades/{id}", amenities.Update)
	mux.HandleFunc("DELETE /comodidades/{id}", amenities.Delete)

	return withAutoBackup(withCORS(mux), backup)
}

type statusRecorder struct {
	http.ResponseWriter
	status int
}

func (sr *statusRecorder) WriteHeader(code int) {
	sr.status = code
	sr.ResponseWriter.WriteHeader(code)
}

var autoBackupState = struct {
	mu    sync.Mutex
	count int
	algos []string
	idx   int
}{
	algos: []string{"huffman", "lzw"},
}

const autoBackupThreshold = 5

func withAutoBackup(h http.Handler, b *handler.BackupHandler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodPost && r.Method != http.MethodPut && r.Method != http.MethodDelete {
			h.ServeHTTP(w, r)
			return
		}

		rw := &statusRecorder{ResponseWriter: w, status: http.StatusOK}
		h.ServeHTTP(rw, r)

		if rw.status < 200 || rw.status >= 300 {
			return
		}

		autoBackupState.mu.Lock()
		autoBackupState.count++
		trigger := autoBackupState.count >= autoBackupThreshold
		var algo string
		if trigger {
			autoBackupState.count = 0
			algo = autoBackupState.algos[autoBackupState.idx%len(autoBackupState.algos)]
			autoBackupState.idx++
		}
		autoBackupState.mu.Unlock()

		if trigger {
			go b.AutoBackup(algo)
		}
	})
}

func withCORS(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Headers", "Content-Type, Authorization")
		w.Header().Set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")

		if r.Method == http.MethodOptions {
			w.WriteHeader(http.StatusNoContent)
			return
		}

		next.ServeHTTP(w, r)
	})
}
