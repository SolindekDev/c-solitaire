#
# Copyright (c) 2024 SolindekDev
#

CC = gcc
CFLAGS = -D __DEBUG__ -O3 -g3 -Wshadow -Wundef -Wcast-align -Wstrict-overflow=5 -Wcast-qual -Wconversion -Wunreachable-code -std=c99 -Iinclude -lm -lSDL2 -lSDL2_image -lSDL2_ttf

SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = csolitare

all: $(TARGET) clean

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ)
