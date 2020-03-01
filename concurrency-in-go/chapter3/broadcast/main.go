package main

import (
	"fmt"
	"sync"
)

func main() {
	type Button struct {
		Clicked *sync.Cond
	}
	button := Button{Clicked: sync.NewCond(&sync.Mutex{})}

	// Start goroutines... all are waiting for the event to occur.
	subscribe := func(c *sync.Cond, fn func()) {
		var goroutineRunning sync.WaitGroup
		goroutineRunning.Add(1)
		go func() {
			goroutineRunning.Done()
			c.L.Lock()
			defer c.L.Unlock()
			c.Wait()
			fn()
		}()
		goroutineRunning.Wait()
	}

	// Setup click handlers
	var clickRegistered sync.WaitGroup
	clickRegistered.Add(3)

	subscribe(button.Clicked, func() {
		fmt.Println("max")
		clickRegistered.Done()
	})

	subscribe(button.Clicked, func() {
		fmt.Println("display")
		clickRegistered.Done()
	})

	subscribe(button.Clicked, func() {
		fmt.Println("mouse")
		clickRegistered.Done()
	})

	// Trigger on actual click event
	button.Clicked.Broadcast()
	clickRegistered.Wait()
}
