CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Iinclude
TARGET = inventory
SRC = src/main.c src/login.c src/product.c src/history.c src/utils.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

ifeq ($(OS),Windows_NT)
clean:
	del /Q $(TARGET).exe 2>NUL || rm -f $(TARGET)
else
clean:
	rm -f $(TARGET)
endif
