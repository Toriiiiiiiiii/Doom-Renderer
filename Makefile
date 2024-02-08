CC = g++

CFLAGS = -g -c -Wall -Wpedantic -Werror -std=c++20
LDFLAGS = -lSDL2

SRC = $(wildcard src/*.cc)
HDR = $(wildcard src/*.h)
OBJ = $(SRC:src/%.cc=bin/obj/%.o)
BIN = bin/exec

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

bin/obj/%.o: src/%.cc $(HDR)
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -rf bin/*
	mkdir bin/obj
