package main

import (
	"bufio"
	"errors"
	"fmt"
	"net"
)

func main() {
	listen()
}

func listen() {
	listener, err := net.Listen("tcp", ":1026")
	if err != nil {
		fmt.Println("Failed to open port 1026")
		return
	}

	// Listen for connections forever and create a goroutine to handle when
	// one arrives.
	for {
		// Will block until there's a connection to accept.
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("error accepting connection")
			continue
		}

		go handle(conn)
	}
}

func handle(conn net.Conn) {
	// Handle if there are any panics in the goroutine or the methods the
	// goroutine calls.
	defer func() {
		if err := recover(); err != nil {
			fmt.Printf("Fatal error: %s", err)
		}

		// Close the connection before the goroutine returns (i.e. stops
		// executing).
		conn.Close()
	}()
	reader := bufio.NewReader(conn)

	data, err := reader.ReadBytes('\n')
	if err != nil {
		fmt.Println("failed to read from socket.")
		conn.Close()
	}

	response(data, conn)
}

func response(data []byte, conn net.Conn) {
	defer func() {
		conn.Close()
	}()

	conn.Write(data)
	//panic(errors.New("I'm an error"))
}
