CC=g++
DDIR=include
SDIR=src
ODIR=obj
CPPFLAGS=-Wall -g -I$(DDIR) -std=c++11

PROGRAM=proj1
DEP=$(wildcard $(DDIR)/*.h)
SRC=$(wildcard $(SDIR)/*.cpp)
OBJ=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CPPFLAGS) -o $@.x $^ $@.cpp

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEP) build
	$(CC) $(CPPFLAGS) -c -o $@ $<

build:
	@mkdir -p $(ODIR)

.PHONY: clean

clean:
	rm -rf $(OBJ)
	rm -f $(PROGRAM)
