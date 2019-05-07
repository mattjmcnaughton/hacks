package gobenchmarktesting

import (
	"crypto/sha1"
	"syreclabs.com/go/faker"
)

func GenerateHashedString() string {
	stringToHash := faker.App().Name()

	hash := sha1.New()
	hash.Write([]byte(stringToHash))

	return string(hash.Sum(nil))
}
