CC = gcc
CFLAGS = -Wall -g

all: program

program: main.o compressor.o
    $(CC) $(CFLAGS) -o program main.o compressor.o

main.o: main.c compressor.h
    $(CC) $(CFLAGS) -c main.c

compressor.o: compressor.c compressor.h
    $(CC) $(CFLAGS) -c compressor.c

clean:
    rm -f *.o program
