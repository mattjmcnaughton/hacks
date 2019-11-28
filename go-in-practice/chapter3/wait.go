package main

import (
	"compress/gzip"
	"io"
	"os"
	"sync"
)

func main() {
	var wg sync.WaitGroup
	for _, file := range os.Args[1:] {
		wg.Add(1)
		go func(filename string) {
			compress(filename)
			wg.Done()
		}(file) // We pass `file` to the function, because we want to preserve it at the time we called the function.
	}

	wg.Wait()
}

func compress(filename string) error {
	in, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer in.Close()

	out, err := os.Create(filename + ".gz")
	if err != nil {
		return err
	}
	defer out.Close()

	// gzip.Writer compresses data and writes it to the underlying file.
	gzout := gzip.NewWriter(out)
	// io.Copy copys the data to the writer, which will compress it
	// automatically.
	_, err = io.Copy(gzout, in)
	gzout.Close()

	return err
}
