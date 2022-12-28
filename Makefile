CC = g++
CFLAGS = -std=c++11 -Wall -lm -g

.PHONY = run clean

all: main

main: main.cpp
	$(CC) $(CFLAGS) $< -o $@

run: main
	@./main

clean:
	rm main
