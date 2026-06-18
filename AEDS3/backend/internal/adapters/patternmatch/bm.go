package patternmatch

func buildBadChar(pattern string) map[byte]int {
	table := make(map[byte]int)
	for i := 0; i < len(pattern); i++ {
		table[pattern[i]] = i
	}
	return table
}

func SearchBM(text, pattern string) []int {
	n := len(text)
	m := len(pattern)
	if m == 0 {
		return nil
	}
	badChar := buildBadChar(pattern)
	var result []int
	i := 0
	for i <= n-m {
		j := m - 1
		for j >= 0 && pattern[j] == text[i+j] {
			j--
		}
		if j < 0 {
			result = append(result, i)
			i++
		} else {
			bc, ok := badChar[text[i+j]]
			if !ok {
				bc = -1
			}
			shift := j - bc
			if shift < 1 {
				shift = 1
			}
			i += shift
		}
	}
	return result
}
