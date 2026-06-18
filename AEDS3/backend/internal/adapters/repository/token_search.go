package repository

import (
	"hash/fnv"
	"strings"
	"unicode"
)

var accentReplacer = strings.NewReplacer(
	"á", "a", "à", "a", "â", "a", "ã", "a", "ä", "a",
	"é", "e", "è", "e", "ê", "e", "ë", "e",
	"í", "i", "ì", "i", "î", "i", "ï", "i",
	"ó", "o", "ò", "o", "ô", "o", "õ", "o", "ö", "o",
	"ú", "u", "ù", "u", "û", "u", "ü", "u",
	"ç", "c",
)

func normalizeForSearch(value string) string {
	trimmed := strings.TrimSpace(strings.ToLower(value))
	if trimmed == "" {
		return ""
	}
	return accentReplacer.Replace(trimmed)
}

func tokenizeForSearch(values ...string) []string {
	terms := make(map[string]struct{})
	for _, value := range values {
		normalized := normalizeForSearch(value)
		if normalized == "" {
			continue
		}
		for _, token := range strings.FieldsFunc(normalized, func(r rune) bool {
			return !(unicode.IsLetter(r) || unicode.IsDigit(r))
		}) {
			if token == "" {
				continue
			}
			terms[token] = struct{}{}
		}
	}

	out := make([]string, 0, len(terms))
	for token := range terms {
		out = append(out, token)
	}
	return out
}

func tokenKey(token string) int {
	hasher := fnv.New32a()
	_, _ = hasher.Write([]byte(token))
	return int(hasher.Sum32())
}

func splitQueryTokens(query string) []string {
	return tokenizeForSearch(query)
}
