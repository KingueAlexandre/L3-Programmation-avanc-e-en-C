EXEC = game
CC = gcc
CFLAGS = -Wall -ansi -pedantic
MLV = -lMLV
SRC = src/
BIN = bin/
INC = include/

all: $(EXEC)
	mv Main.o bin
	mv Jeu.o bin
	mv Plateau.o bin
	mv Graphique.o bin
	mv Elements.o bin
	mv Donjon.o bin

$(EXEC): Main.o Jeu.o Plateau.o Elements.o Graphique.o Donjon.o
	$(CC) -o $(EXEC) Main.o Jeu.o Plateau.o Elements.o Graphique.o Donjon.o $(CFLAGS) $(MLV)

Main.o: $(SRC)Main.c $(INC)Jeu.h $(INC)Graphique.h
	$(CC) -c $(SRC)Main.c -o $@ $(CFLAGS)
	
Jeu.o: $(SRC)Jeu.c $(INC)Jeu.h $(INC)Plateau.h $(INC)Graphique.h
	$(CC) -c $(SRC)Jeu.c $(CFLAGS) $(MLV)

Plateau.o: $(SRC)Plateau.c $(INC)Plateau.h $(INC)Elements.h
	$(CC) -c $(SRC)Plateau.c $(CFLAGS)

Elements.o: $(SRC)Elements.c $(INC)Elements.h
	$(CC) -c $(SRC)Elements.c $(CFLAGS)

Graphique.o: $(SRC)Graphique.c $(INC)Graphique.h $(INC)Plateau.h
	$(CC) -c $(SRC)Graphique.c $(CFLAGS) $(MLV)

Donjon.o: $(SRC)Donjon.c $(INC)Donjon.h $(INC)Plateau.h
	$(CC) -c $(SRC)Donjon.c $(CFLAGS)

clean:
	rm $(BIN)Main.o $(BIN)Jeu.o $(BIN)Plateau.o $(BIN)Elements.o $(BIN)Graphique.o $(BIN)Donjon.o