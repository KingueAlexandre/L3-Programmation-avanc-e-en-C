CC=gcc
CFLAGS=-Wall -ansi -pedantic
EXEC=larger_file

$(EXEC):  Main.o
	$(CC) -o $@ $^ $(CFLAGS)

Main.o: Main.c
	gcc -c Main.c