package gobenchmarktesting

import (
	"testing"
)

func BenchmarkGenerateHashedString(b *testing.B) {
	b.StopTimer()
	b.StartTimer()
	for i := 0; i < b.N; i++ {
		GenerateHashedString()
	}
}
