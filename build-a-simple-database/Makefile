build_main:
	gcc -o main *.c

build: build_main

test: clean build
	bundle exec rspec

clean:
	rm main

fmt:
	bundle exec rbprettier --write 'spec/*.rb'
