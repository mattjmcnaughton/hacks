package main

import (
	"context"
	"fmt"
	"time"

	kafka "github.com/segmentio/kafka-go"
)

func main() {
	topic := "myTopic"
	partition := 0

	conn, err := kafka.DialLeader(context.Background(), "tcp", "localhost:9092", topic, partition)

	if err != nil {
		panic(err)
	}

	defer conn.Close()

	conn.SetReadDeadline(time.Now().Add(10 * time.Second))
	batch := conn.ReadBatch(10e3, 1e6) // fetch 10kb min, 1MB max

	b := make([]byte, 10e3)

	for {
		_, err := batch.Read(b)
		if err != nil {
			break
		}

		fmt.Println(string(b))
	}

	batch.Close()
}
