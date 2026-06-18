package patternmatch

func buildFailure(pattern string) []int {
	m := len(pattern)
	fail := make([]int, m)
	fail[0] = 0
	k := 0
	for i := 1; i < m; i++ {
		for k > 0 && pattern[k] != pattern[i] {
			k = fail[k-1]
		}
		if pattern[k] == pattern[i] {
			k++
		}
		fail[i] = k
	}
	return fail
}

func SearchKMP(text, pattern string) []int {
	if len(pattern) == 0 {
		return nil
	}
	fail := buildFailure(pattern)
	var result []int
	j := 0
	for i := 0; i < len(text); i++ {
		for j > 0 && text[i] != pattern[j] {
			j = fail[j-1]
		}
		if text[i] == pattern[j] {
			j++
		}
		if j == len(pattern) {
			result = append(result, i-j+1)
			j = fail[j-1]
		}
	}
	return result
}
