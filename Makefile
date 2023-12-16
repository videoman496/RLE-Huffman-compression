CFLAGS= -std=c99 -g 

all: main

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

MAIN: main.o compressor.o
	gcc main.o compressor.o -o mIN

clean:
	rm *.o MAIN
