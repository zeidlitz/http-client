CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Wno-unused-parameter
LDFLAGS = -lcurl
TARGET = http-client
SRC = src/http-client.c
all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)
