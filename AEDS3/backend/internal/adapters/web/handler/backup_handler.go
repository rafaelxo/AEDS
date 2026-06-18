package handler

import (
	"backend/internal/adapters/compression"
	"encoding/json"
	"errors"
	"fmt"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"strings"
	"time"
)

type BackupHandler struct {
	engine *compression.Engine
}

func NewBackupHandler(e *compression.Engine) *BackupHandler {
	return &BackupHandler{engine: e}
}

type BackupResult struct {
	Arquivo       string   `json:"arquivo"`
	Algoritmo     string   `json:"algoritmo"`
	Arquivos      []string `json:"arquivos"`
	TamanhoTotal  int      `json:"tamanhoTotal"`
	TamanhoBackup int      `json:"tamanhoBackup"`
	Taxa          float64  `json:"taxa"`
}

type BackupInfo struct {
	Arquivo   string `json:"arquivo"`
	Algoritmo string `json:"algoritmo"`
	Tamanho   int64  `json:"tamanho"`
	CriadoEm  string `json:"criadoEm"`
}

type RestoreResult struct {
	Arquivo   string   `json:"arquivo"`
	Algoritmo string   `json:"algoritmo"`
	Arquivos  []string `json:"arquivos"`
}

func collectDataFiles() ([]string, error) {
	entries, err := os.ReadDir("data")
	if err != nil {
		return nil, err
	}
	var files []string
	for _, entry := range entries {
		if entry.IsDir() {
			continue
		}
		name := entry.Name()
		if strings.HasSuffix(name, ".hbak") {
			continue
		}
		if strings.Contains(name, ".sort.run.") || strings.HasSuffix(name, ".sorted.bin") {
			continue
		}
		files = append(files, filepath.Join("data", name))
	}
	return files, nil
}

func (h *BackupHandler) AutoBackup(algo string) {
	paths, err := collectDataFiles()
	if err != nil {
		log.Printf("[autobackup] erro ao listar arquivos: %v", err)
		return
	}
	var entries []compression.ArchiveEntry
	totalSize := 0
	for _, path := range paths {
		data, readErr := os.ReadFile(path)
		if readErr != nil {
			continue
		}
		entries = append(entries, compression.ArchiveEntry{Name: filepath.Base(path), Data: data})
		totalSize += len(data)
	}
	if len(entries) == 0 {
		return
	}
	raw, packErr := compression.Pack(entries)
	if packErr != nil {
		log.Printf("[autobackup] erro ao empacotar: %v", packErr)
		return
	}
	compressed, compErr := h.engine.CompressRaw(raw, algo)
	if compErr != nil {
		log.Printf("[autobackup] erro ao comprimir (%s): %v", algo, compErr)
		return
	}
	ts := time.Now().Format("20060102-150405")
	filename := fmt.Sprintf("backup-%s-%s.hbak", ts, algo)
	dest := filepath.Join("data", filename)
	if writeErr := os.WriteFile(dest, compressed, 0644); writeErr != nil {
		log.Printf("[autobackup] erro ao salvar %s: %v", filename, writeErr)
		return
	}
	log.Printf("[autobackup] %s criado — %d → %d bytes (%.1f%% do original)",
		filename, totalSize, len(compressed), float64(len(compressed))/float64(totalSize)*100)
}

func algoFromFilename(filename string) string {
	name := strings.TrimSuffix(filename, ".hbak")
	parts := strings.Split(name, "-")
	if len(parts) >= 1 {
		return parts[len(parts)-1]
	}
	return "unknown"
}

type backupCreateRequest struct {
	Algoritmo string `json:"algoritmo"`
}

func (h *BackupHandler) Create(w http.ResponseWriter, r *http.Request) {
	var req backupCreateRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	if req.Algoritmo == "" {
		req.Algoritmo = "huffman"
	}

	paths, err := collectDataFiles()
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}

	var entries []compression.ArchiveEntry
	totalSize := 0
	var names []string
	for _, path := range paths {
		data, readErr := os.ReadFile(path)
		if readErr != nil {
			continue
		}
		entries = append(entries, compression.ArchiveEntry{Name: filepath.Base(path), Data: data})
		totalSize += len(data)
		names = append(names, filepath.Base(path))
	}
	if len(entries) == 0 {
		respondError(w, http.StatusInternalServerError, errors.New("nenhum arquivo de dados encontrado"))
		return
	}

	raw, err := compression.Pack(entries)
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}

	compressed, err := h.engine.CompressRaw(raw, req.Algoritmo)
	if err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}

	ts := time.Now().Format("20060102-150405")
	filename := fmt.Sprintf("backup-%s-%s.hbak", ts, req.Algoritmo)
	dest := filepath.Join("data", filename)
	if err := os.WriteFile(dest, compressed, 0644); err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}

	ratio := 0.0
	if totalSize > 0 {
		ratio = float64(len(compressed)) / float64(totalSize)
	}

	respondJSON(w, http.StatusOK, BackupResult{
		Arquivo:       filename,
		Algoritmo:     req.Algoritmo,
		Arquivos:      names,
		TamanhoTotal:  totalSize,
		TamanhoBackup: len(compressed),
		Taxa:          ratio,
	})
}

func (h *BackupHandler) List(w http.ResponseWriter, r *http.Request) {
	entries, err := os.ReadDir("data")
	if err != nil {
		respondError(w, http.StatusInternalServerError, err)
		return
	}

	var backups []BackupInfo
	for _, entry := range entries {
		if entry.IsDir() || !strings.HasSuffix(entry.Name(), ".hbak") {
			continue
		}
		info, infoErr := entry.Info()
		if infoErr != nil {
			continue
		}
		backups = append(backups, BackupInfo{
			Arquivo:   entry.Name(),
			Algoritmo: algoFromFilename(entry.Name()),
			Tamanho:   info.Size(),
			CriadoEm:  info.ModTime().Format("2006-01-02 15:04:05"),
		})
	}
	if backups == nil {
		backups = []BackupInfo{}
	}
	respondJSON(w, http.StatusOK, backups)
}

type restoreRequest struct {
	Arquivo string `json:"arquivo"`
}

func (h *BackupHandler) Restore(w http.ResponseWriter, r *http.Request) {
	var req restoreRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		respondError(w, http.StatusBadRequest, err)
		return
	}
	if req.Arquivo == "" {
		respondError(w, http.StatusBadRequest, errors.New("arquivo obrigatório"))
		return
	}

	clean := filepath.Base(req.Arquivo)
	if !strings.HasSuffix(clean, ".hbak") {
		respondError(w, http.StatusBadRequest, errors.New("arquivo inválido: deve ter extensão .hbak"))
		return
	}

	path := filepath.Join("data", clean)
	compressedData, err := os.ReadFile(path)
	if err != nil {
		respondError(w, http.StatusNotFound, fmt.Errorf("backup não encontrado: %s", clean))
		return
	}

	raw, err := h.engine.DecompressRaw(compressedData, algoFromFilename(clean))
	if err != nil {
		respondError(w, http.StatusInternalServerError, fmt.Errorf("erro ao descomprimir: %w", err))
		return
	}

	archiveEntries, err := compression.Unpack(raw)
	if err != nil {
		respondError(w, http.StatusInternalServerError, fmt.Errorf("erro ao desempacotar: %w", err))
		return
	}

	var restored []string
	for _, entry := range archiveEntries {
		dest := filepath.Join("data", entry.Name)
		if writeErr := os.WriteFile(dest, entry.Data, 0644); writeErr != nil {
			respondError(w, http.StatusInternalServerError, fmt.Errorf("erro ao restaurar %s: %w", entry.Name, writeErr))
			return
		}
		restored = append(restored, entry.Name)
	}
	if restored == nil {
		restored = []string{}
	}

	respondJSON(w, http.StatusOK, RestoreResult{
		Arquivo:   clean,
		Algoritmo: algoFromFilename(clean),
		Arquivos:  restored,
	})
}
