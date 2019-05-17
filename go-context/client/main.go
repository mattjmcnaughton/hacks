package main

import (
	"context"
	"flag"
	"fmt"
	"io/ioutil"
	"net/http"
	"time"
)

func main() {
	t := flag.Int("timeout", 2, "Timeout, in seconds")
	flag.Parse()

	d := time.Duration(*t)
	ctx, cancel := context.WithTimeout(context.Background(), d*time.Second)
	defer cancel()

	body, err := doWork(ctx)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(string(body))
}

func doWork(ctx context.Context) ([]byte, error) {
	req, err := http.NewRequest("GET", "http://localhost:8080", nil)
	if err != nil {
		return nil, err
	}

	var b []byte
	err = httpDo(ctx, req, func(res *http.Response, err error) error {
		if err != nil {
			return err
		}
		defer res.Body.Close()
		if b, err = ioutil.ReadAll(res.Body); err != nil {
			return err
		}

		return nil
	})

	return b, err
}

func httpDo(ctx context.Context, req *http.Request, f func(*http.Response, error) error) error {
	tr := &http.Transport{}
	client := http.Client{Transport: tr}
	c := make(chan error, 1)

	go func() { c <- f(client.Do(req)) }()

	select {
	case <-ctx.Done():
		tr.CancelRequest(req)
		<-c
		return ctx.Err()
	case err := <-c:
		return err
	}
}
