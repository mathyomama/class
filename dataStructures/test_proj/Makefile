CC=g++47
CPPFLAGS=-Wall -g -std=c++11

PROGRAM=proj3
DEP=$(wildcard *.h)
SRC=flight.cpp
OBJ=$(patsubst %.cpp, %.o, $(SRC))

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@.x $^ $@.cpp

%.o: %.cpp $(DEP)
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -f $(PROGRAM)
