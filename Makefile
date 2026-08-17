CC = gcc

CFLAGS = -Wall -Wextra -std=c17 -Iinclude

LDFLAGS = -lraylib -lm

SRC = $(wildcard src/*.c)

TARGET = simulation

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
