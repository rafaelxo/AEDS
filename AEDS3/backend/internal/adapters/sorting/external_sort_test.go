package sorting

import (
	"math/rand"
	"sort"
	"testing"
)

type sample struct {
	ID    int     `json:"id"`
	Value float64 `json:"value"`
}

func keyFn(s sample) (float64, int) { return s.Value, s.ID }

func baseline(items []sample, ascending bool) []sample {
	out := append([]sample(nil), items...)
	sort.Slice(out, func(i, j int) bool {
		if out[i].Value != out[j].Value {
			if ascending {
				return out[i].Value < out[j].Value
			}
			return out[i].Value > out[j].Value
		}
		return out[i].ID < out[j].ID
	})
	return out
}

func TestSortExternalMatchesBaseline(t *testing.T) {
	rng := rand.New(rand.NewSource(42))
	items := make([]sample, 100)
	for i := range items {
		items[i] = sample{ID: i + 1, Value: float64(rng.Intn(10))}
	}

	engine := NewEngine(t.TempDir(), 16)

	for _, ascending := range []bool{true, false} {
		got, err := SortExternal(engine, "sample", items, keyFn, ascending)
		if err != nil {
			t.Fatalf("ascending=%v: %v", ascending, err)
		}
		want := baseline(items, ascending)
		if len(got) != len(want) {
			t.Fatalf("ascending=%v: len=%d want %d", ascending, len(got), len(want))
		}
		for i := range want {
			if got[i] != want[i] {
				t.Fatalf("ascending=%v: at %d got %+v want %+v", ascending, i, got[i], want[i])
			}
		}
	}
}

func TestSortExternalEmpty(t *testing.T) {
	engine := NewEngine(t.TempDir(), 16)
	got, err := SortExternal(engine, "empty", []sample{}, keyFn, true)
	if err != nil {
		t.Fatal(err)
	}
	if len(got) != 0 {
		t.Fatalf("want empty, got %d", len(got))
	}
}

func TestSortExternalSingleRun(t *testing.T) {
	engine := NewEngine(t.TempDir(), 16)
	items := []sample{{ID: 1, Value: 3}, {ID: 2, Value: 1}, {ID: 3, Value: 2}}
	got, err := SortExternal(engine, "single", items, keyFn, true)
	if err != nil {
		t.Fatal(err)
	}
	want := baseline(items, true)
	for i := range want {
		if got[i] != want[i] {
			t.Fatalf("at %d got %+v want %+v", i, got[i], want[i])
		}
	}
}
