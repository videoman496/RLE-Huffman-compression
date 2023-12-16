CFLAGS= -std=c99 -g 

all: main

main: main.o compressor.o
	gcc main.o compressor.o -o main

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o main
