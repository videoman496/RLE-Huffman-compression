CFLAGS=-std=c99 -g 

all: main

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

main: main.o 
	gcc main.o  -o main
clean:
	rm -f *.o main
run: main
	./main
