CC = gcc
CFLAGS = -Wall -ansi -pedantic
MLV = -lMLV

taquin: Main.o Plateau.o Graphique.o Jeu.o
	$(CC) -o taquin Main.o Plateau.o Graphique.o Jeu.o $(CFLAGS) $(MLV)

Main.o: Main.c Jeu.h 
	$(CC) -c Main.c

Plateau.o: Plateau.c Plateau.h
	$(CC) -c Plateau.c

Graphique.o: Graphique.c Graphique.h Plateau.h
	$(CC) -c Graphique.c

Jeu.o: Jeu.c Jeu.h Graphique.h
	$(CC) -c Jeu.c
	
clean:
	rm -f *.o
