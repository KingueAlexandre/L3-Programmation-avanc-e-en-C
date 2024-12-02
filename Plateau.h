#ifndef __PLATEAU__
#define __PLATEAU__

#define NB_COL  4
#define NB_LIG   4 

/*Structures*/
typedef  struct carre{
	int lig; //l i g n e  o r i g i n a l e  dans  l ’ image
	int col ; //colonne  o r i g i n a l e  dans  l ’ image
}Carre;

typedef struct plateau{
	Carre bloc[NB_COL][NB_LIG ];
}Plateau;

void InitialisationPlateau(Plateau *P);

/*FONCTION D'ECHANGE.
Elle change les contenu des cases ((P->bloc)[y][x]) et ((P->bloc)[y2][x2])*/
void EchangeCasePlateau(Plateau *P, int x, int y, int x2, int y2);

/*FONCTION DE DEBUT DE PARTIE.
La fonction prépare la situation de départ du joueur, en éffectuant "nb" 
échanges avec la  cases noires symbolisée par les entiers *xn et *yn*/
void DebutdeJeuPlateau(Plateau *P, int *xn, int *yn, int nb);

#endif
