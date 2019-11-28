package main

/**
When a server shuts down, we want to stop receiving new requests, save any data to disk,
and cleanly end connections. The `http` package will shut down immediately (unclear which exact signal)
and doesn't provide an opportunity to handle these situations.

This program shows an example using the `braintree/manners` package to support graceful shutdowns.
*/

import (
	"fmt"
	"github.com/braintree/manners"
	"net/http"
	"os"
	"os/signal"
	"time"
)

func main() {
	handler := newHandler()

	ch := make(chan os.Signal)
	// Send an `os.Signal` event on `ch` when the program receives either
	// the `os.Interrupt` or `os.Kill` signal.
	signal.Notify(ch, os.Interrupt, os.Kill)
	go listenForShutdown(ch)

	manners.ListenAndServe(":8080", handler)
}

func newHandler() *handler {
	return &handler{}
}

// handlers conforms to Handler interface.
type handler struct{}

func (h *handler) ServeHTTP(res http.ResponseWriter, req *http.Request) {
	query := req.URL.Query()
	name := query.Get("name")
	if name == "" {
		name = "Matt"
	}

	time.Sleep(10 * time.Second)

	fmt.Fprint(res, "Hello my name is ", name)
}

func listenForShutdown(ch <-chan os.Signal) {
	// Block until we receive an os.Signal on the `ch` channel.
	<-ch
	fmt.Println("Starting graceful shutdown")

	// Shut down the default http server started by `ListenAndServe`. "Shut
	// down" equates to stopping accepting connections, finishing any
	// remaining requests, and then stopping.
	manners.Close()
}
