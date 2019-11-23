package main

import (
	"bufio"
	"fmt"
	"net"
)

func main() {
	// Directly connect to golang.org:80 via TCP and send TCP request.
	conn, _ := net.Dial("tcp", "golang.org:80")
	fmt.Fprintf(conn, "GET / HTTP/1.0\r\n\r\n") //
	status, _ := bufio.NewReader(conn).ReadString('\n')
	fmt.Println(status)
}
