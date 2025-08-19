CC = gcc
CFLAGS = -Wall -Wextra -std=c17
OBJ = main.o fileio.o utils.o rle.o
TARGET = fomp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c headers.h
	$(CC) $(CFLAGS) -c main.c

rle.o: rle.c rle.h headers.h
	$(CC) $(CFLAGS) -c rle.c

fileio.o: fileio.c fileio.h headers.h
	$(CC) $(CFLAGS) -c fileio.c

utils.o: utils.c utils.h headers.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean