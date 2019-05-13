package main

import (
	"fmt"
	"log"
	"net"

	"github.com/mattjmcnaughton/go-grpc/api"
	"google.golang.org/grpc"
)

func main() {
	lis, err := net.Listen("tcp", fmt.Sprintf(":%d", 7777))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	// Create server instance
	s := api.Server{}

	// Create a grpc server
	grpcServer := grpc.NewServer()

	// Attach the Ping service to the server
	// We can use server because it fulfills the interface
	// for the Ping service
	api.RegisterPingServer(grpcServer, &s)

	// Start the server
	if err := grpcServer.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %s", err)
	}
}
