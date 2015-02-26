CC=g++
CFLAGS=-std=c++11 -g -Wall

.SUFFIXES: .x

test.x: test.cpp Queue.hpp Queue.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o *.x core.*
