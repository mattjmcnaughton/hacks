package main

import (
	"fmt"
	"runtime"
)

func main() {
	fmt.Println("outside a goroutine.")
	go func() {
		fmt.Println("Inside a goroutine")
	}()
	fmt.Println("outside again.")

	// Instruct the Go runtime to yield to the scheduler (most likely the
	// first chance the goroutine will get to execute, especially if on
	// single thread).
	//
	// It doesn't necessarily guarantee that the goroutine will get a chance
	// to finish, as if the function running in the goroutine pauses for
	// whatever reason (i.e. performing IO, sleeping, etc...), then
	// execution could be handed back to the main function.
	runtime.Gosched()

	fmt.Println("final outside")

	go func() {
		fmt.Println("probably never see this execute")
	}()

	// Main function will almost certainly return (terminating the
	// program), before the go scheduler gives the above go routine
	// a chance to run. We could ensure it gets a chance to run with
	// either `runtime.Gosched` or WaitGroups or creating a `done`
	// channel.
}
