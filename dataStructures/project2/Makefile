CC=g++47
CFLAGS=-std=c++11 -g -Wall

.SUFFIXES: .x

%.x: %.cpp Vector.hpp
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -f *.o *.x core.*
