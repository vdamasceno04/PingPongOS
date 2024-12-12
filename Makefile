TARGET = pingpongos

SRC = ./ppos-core-aux.c ./pingpong-semaphore.c

OBJ = $(wildcard ./*.o)

LIB = ./libppos_static.a

CC = gcc

CFLAGS = -o $(TARGET) -Wall

all: build run

build:build_lib
	$(CC) $(CFLAGS) $(SRC) $(LIB)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

build_lib:
	ar rcs libppos_static.a $(OBJ)


.PHONY: all build run clean