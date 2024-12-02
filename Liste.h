#ifndef LISTE

#define LISTE


typedef struct  cell{
	int valeur;
	struct cell *suivant;

}Cellule,*Pile;

Pile AlloueCellule(int entier);

void affichePile(Pile pile);

int insererC(Pile *pile, int entier);

void freePile(Pile *pile);

void supprimetetePile(Pile *pile);

int reversePile(Pile *pile);

#endif