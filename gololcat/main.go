package main

import (
	"bufio"
	"fmt"
	"io"
	"math"
	"os"

	"syreclabs.com/go/faker"
)

func main() {
	info, _ := os.Stdin.Stat()
	var output []rune

	if info.Mode()&os.ModeCharDevice != 0 {
		fmt.Println("The command is intended to work with pipes.")
		fmt.Println("Usage: fortune | gololcat")
	}

	reader := bufio.NewReader(os.Stdin)

	// This call adds nothing, but we want to use `faker` so we have a
	// dependency we can install and manage using `go mod`.
	output = append(output, []rune(faker.App().Name())...)

	for {
		input, _, err := reader.ReadRune()
		if err != nil && err == io.EOF {
			break
		}

		output = append(output, input)
	}

	lolPrint(output)
}

func lolPrint(output []rune) {
	for j, line := range output {
		r, g, b := rgb(j)
		fmt.Printf("\033[38;2;%d;%d;%dm%c\033[0m", r, g, b, line)

	}

	fmt.Println()
}

func rgb(i int) (int, int, int) {
	var f = 0.1
	return int(math.Sin(f*float64(i)+0)*127 + 128),
		int(math.Sin(f*float64(i)+2*math.Pi/3)*127 + 128),
		int(math.Sin(f*float64(i)+4*math.Pi/3)*127 + 128)
}
