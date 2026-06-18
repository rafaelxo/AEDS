package main

import (
	"backend/internal/adapters/compression"
	"backend/internal/adapters/patternmatch"
	"backend/internal/adapters/payment"
	"backend/internal/adapters/repository"
	"backend/internal/adapters/sorting"
	web "backend/internal/adapters/web"
	aeduc "backend/internal/usecase/aed"
	amenityuc "backend/internal/usecase/amenity"
	authuc "backend/internal/usecase/auth"
	"backend/internal/usecase/property"
	propertyamenityuc "backend/internal/usecase/propertyamenity"
	reservationuc "backend/internal/usecase/reservation"
	useruc "backend/internal/usecase/user"
	"log"
	"net/http"
)

func main() {
	userRepo, err := repository.NewUserFileRepository("data/usuarios.db")
	if err != nil {
		log.Fatalf("erro ao inicializar repositorio de usuarios: %v", err)
	}

	propertyRepo, err := repository.NewPropertyFileRepository("data/imoveis.db", userRepo.GetByID)
	if err != nil {
		log.Fatalf("erro ao inicializar repositorio de imoveis: %v", err)
	}

	reservationRepo, err := repository.NewReservationFileRepository("data/reservas.db", propertyRepo.GetByID, userRepo.GetByID)
	if err != nil {
		log.Fatalf("erro ao inicializar repositorio de reservas: %v", err)
	}

	amenityRepo, err := repository.NewAmenityFileRepository("data/comodidades.db")
	if err != nil {
		log.Fatalf("erro ao inicializar repositorio de comodidades: %v", err)
	}

	propertyAmenityRepo, err := repository.NewPropertyAmenityFileRepository("data/imoveis_comodidades.db")
	if err != nil {
		log.Fatalf("erro ao inicializar repositorio de imoveis_comodidades: %v", err)
	}

	propertyAmenityService := propertyamenityuc.NewService(propertyAmenityRepo, propertyRepo, amenityRepo)
	propertyService := property.NewService(propertyRepo, userRepo, propertyAmenityService)
	userService := useruc.NewService(userRepo)
	paymentGateway := payment.NewSimulatedGateway()
	reservationService := reservationuc.NewService(reservationRepo, propertyRepo, userRepo, paymentGateway)
	amenityService := amenityuc.NewService(amenityRepo, propertyAmenityService)
	aedService := aeduc.NewService(
		propertyService,
		reservationService,
		func() aeduc.HashStats {
			stats := propertyRepo.HashStats()
			return aeduc.HashStats{GlobalDepth: stats.GlobalDepth, Buckets: stats.Buckets, Entries: stats.Entries}
		},
		func() aeduc.HashStats {
			stats := userRepo.HashStats()
			return aeduc.HashStats{GlobalDepth: stats.GlobalDepth, Buckets: stats.Buckets, Entries: stats.Entries}
		},
		func() aeduc.HashStats {
			stats := reservationRepo.HashStats()
			return aeduc.HashStats{GlobalDepth: stats.GlobalDepth, Buckets: stats.Buckets, Entries: stats.Entries}
		},
	)
	authService := authuc.NewService(userService, propertyService)

	externalSorter := sorting.NewEngine("data", 4)
	compressor := compression.NewEngine()
	matcher := patternmatch.NewEngine()

	if _, err := authService.SeedDefaultAdmin(); err != nil {
		log.Fatalf("erro ao criar admin padrao: %v", err)
	}

	if err := amenityService.SeedCommonAmenities(); err != nil {
		log.Fatalf("erro ao preparar comodidades iniciais: %v", err)
	}

	router := web.NewRouter(web.Dependencies{
		PropertyService:        propertyService,
		UserService:            userService,
		ReservationService:     reservationService,
		AuthService:            authService,
		AmenityService:         amenityService,
		PropertyAmenityService: propertyAmenityService,
		AEDService:             aedService,
		Compressor:             compressor,
		PatternMatcher:         matcher,
		SortImoveis: func(attr string, asc bool) error {
			return propertyRepo.SortFileBy(externalSorter, attr, asc)
		},
		SortReservas: func(attr string, asc bool) error {
			return reservationRepo.SortFileBy(externalSorter, attr, asc)
		},
	})

	addr := ":8080"
	log.Printf("Hostly backend iniciado em %s", addr)
	if err := http.ListenAndServe(addr, router); err != nil {
		log.Fatalf("erro ao iniciar servidor: %v", err)
	}
}
