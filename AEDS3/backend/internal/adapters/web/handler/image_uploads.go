package handler

import (
	"encoding/base64"
	"fmt"
	"net/http"
	"strings"
)

const maxImageSizeBytes = 8 << 20

var imageExtByContentType = map[string]string{
	"image/jpeg": ".jpg",
	"image/jpg":  ".jpg",
	"image/png":  ".png",
	"image/webp": ".webp",
	"image/gif":  ".gif",
}

func saveRequestImage(data []byte, contentType string) (string, error) {
	if len(data) == 0 {
		return "", fmt.Errorf("imagem vazia")
	}
	if len(data) > maxImageSizeBytes {
		return "", fmt.Errorf("imagem excede limite de 8MB")
	}

	detected := strings.ToLower(strings.TrimSpace(contentType))
	if idx := strings.Index(detected, ";"); idx >= 0 {
		detected = strings.TrimSpace(detected[:idx])
	}
	if detected == "" || !strings.HasPrefix(detected, "image/") {
		detected = strings.ToLower(http.DetectContentType(data))
		if idx := strings.Index(detected, ";"); idx >= 0 {
			detected = strings.TrimSpace(detected[:idx])
		}
	}

	if _, ok := imageExtByContentType[detected]; !ok {
		return "", fmt.Errorf("formato de imagem nao suportado")
	}

	return fmt.Sprintf("data:%s;base64,%s", detected, base64.StdEncoding.EncodeToString(data)), nil
}

func savePhotoFromDataURL(dataURL string) (string, error) {
	parts := strings.SplitN(strings.TrimSpace(dataURL), ",", 2)
	if len(parts) != 2 {
		return "", fmt.Errorf("foto em data URL invalida")
	}

	header := strings.ToLower(parts[0])
	if !strings.HasPrefix(header, "data:image/") || !strings.Contains(header, ";base64") {
		return "", fmt.Errorf("foto em data URL invalida")
	}

	raw, err := base64.StdEncoding.DecodeString(parts[1])
	if err != nil {
		return "", fmt.Errorf("base64 da foto invalido")
	}
	if len(raw) == 0 {
		return "", fmt.Errorf("imagem vazia")
	}
	if len(raw) > maxImageSizeBytes {
		return "", fmt.Errorf("imagem excede limite de 8MB")
	}

	mimePart := strings.TrimPrefix(strings.SplitN(parts[0], ";", 2)[0], "data:")
	if _, ok := imageExtByContentType[mimePart]; !ok {
		return "", fmt.Errorf("formato de imagem nao suportado")
	}

	return dataURL, nil
}
