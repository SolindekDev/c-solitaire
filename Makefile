#
# Copyright (c) 2024 SolindekDev
#

CC = gcc
CFLAGS = -D __DEBUG__ -O3 -g3 -Wshadow -Wundef -Wcast-align -Wstrict-overflow=5 -Wcast-qual -Wconversion -Wunreachable-code -std=c18 -Iinclude $(shell pkg-config --cflags sdl2)
LDFLAGS =  -lm $(shell pkg-config --libs sdl2 sdl2_ttf sdl2_image)

SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = c-solitaire

all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ)
