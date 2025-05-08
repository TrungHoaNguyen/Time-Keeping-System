.PHONY: build run clean

build: main.c mock.c
	gcc -o main.exe main.c mock.c -I.

run:
	./main.exe

clean:
	rm main.exe