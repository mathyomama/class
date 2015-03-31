CC=g++
CPPFLAGS=-Wall -g -std=c++11

PROGRAM=proj4_driver
DEP=$(wildcard *.h)
DEP+=$(wildcard *.hpp)
all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@.x $^ $@.cpp

%.o: %.cpp $(DEP)
	$(CC) $(CPPFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -f $(PROGRAM)
