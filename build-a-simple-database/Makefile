build_main:
	gcc -o main *.c

build: build_main

test: clean build
	bundle exec rspec

clean:
	rm main || true

rubyfmt:
	bundle exec rbprettier --write 'spec/*.rb'

clangfmt:
	VERSION_CONTROL=none indent $(wildcard *.c) $(wildcard *.h)

fmt: rubyfmt clangfmt
