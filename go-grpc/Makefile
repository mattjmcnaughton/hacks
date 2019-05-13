build-server:
	go build -o server-bin server/main.go

build-client:
	go build -o client-bin client/main.go

build: build-server build-client

clean:
	rm server-bin client-bin

