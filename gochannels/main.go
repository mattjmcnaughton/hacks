package main

import (
	"sync"
)

// Ensure that we only attempt to close a channel once.
func main() {
	c := make(chan struct{})

	var once sync.Once

	closeFunc := func() { close(c) }
	go func() {
		once.Do(closeFunc)
	}()
	go func() {
		once.Do(closeFunc)
	}()

	<-c
}
