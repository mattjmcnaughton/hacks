package main

import (
	"fmt"
	"time"
)

func main() {
	doneCh := make(chan bool)
	stopCh := make(chan bool)

	go func() {
		timeoutCh := time.After(5 * time.Second)

		for {
			select {
			case <-doneCh:
				fmt.Println("weeeee!")
			case <-timeoutCh:
				fmt.Println("timeout!")
				stopCh <- true
			}
		}
	}()

	time.Sleep(3 * time.Second)

	doneCh <- true

	<-stopCh
}
