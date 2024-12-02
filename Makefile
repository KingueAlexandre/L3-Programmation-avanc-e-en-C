CC = gcc
CFLAGS = -Wall -ansi -pedantic


prog: Main.o code.o 
	$(CC) -o prog Main.o code.o $(CFLAGS)

Main.o: Main.c
	$(CC) -c Main.c $(CFLAGS)

clean:
	rm -f Main.o
	rm -f prog
