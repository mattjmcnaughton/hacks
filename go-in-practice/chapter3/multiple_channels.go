package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	// Creates a new channel which will receive a message when 30 seconds
	// has elapsed.
	//
	// <-chan time.Time is the type, which symbolizes a read only channel.
	done := time.After(30 * time.Second)
	// Because we haven't specified a size, this channel can only hold one
	// message at a time.
	echo := make(chan []byte)

	go readStdin(echo)

	// `for {}` essentially says run the code block forever.
	for {
		// If select sees an event on either one of the channels, it
		// executes the relevant code block. If not, it will hang (or
		// execute the `default:` block)
		select {
		case buf := <-echo:
			os.Stdout.Write(buf)
		case <-done:
			fmt.Println("Timed out")
			os.Exit(0)
		}
	}
}

// chan<- []byte symbolizes a write only channel.
func readStdin(out chan<- []byte) {
	for {
		data := make([]byte, 1024)
		l, _ := os.Stdin.Read(data)
		if l > 0 {
			out <- data
		}
	}
}
