CC = gcc
CFLAGS = -Wall -ansi -pedantic
OPTION = -lreadline

calc: Main.o Option.o Liste.o
	$(CC) -o calc Main.o Option.o Liste.o $(CFLAGS) $(OPTION)

Main.o: Main.c Option.h
	$(CC) -c Main.c $(CFLAGS) $(OPTION)

Option.o: Option.c Option.h Liste.h
	$(CC) -c Option.c $(CFLAGS)

Liste.o: Liste.c Liste.h
	$(CC) -c Liste.c $(CFLAGS)

clean:
	rm*. o
	rm  exe

mrproper: clean
	rm -f calc