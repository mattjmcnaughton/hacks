package main

import (
	"flag"
	"fmt"
	"net/http"
	"time"
)

func main() {
	t := flag.Int("timeout", 5, "Sleep duration, in seconds")
	flag.Parse()

	http.HandleFunc("/", handler(time.Duration(*t)))

	fmt.Println("Listening on port 8080")
	http.ListenAndServe(":8080", nil)
}

func handler(d time.Duration) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		time.Sleep(d * time.Second)
		fmt.Fprint(w, "I finished before context deadline exceeded")
	}
}
