#ifndef __PLATEAU__
#define __PLATEAU__

#include "Elements.h"
/*
Structure TOUR
Simulant les tours restant des différent effets des potions.
*/
typedef struct{
    int regeneration;
    int precision;
    int apprentissage;
}Tour;
/*
Structure Cell
Simulant les cases de plateau.
Possédant un type de cellule et une entité pouvant être soit un monstre soit un coffre.
*/
typedef struct {
    Celltype type ;
    Entity entity ;
}Cell;

/*
Structure Plateau
Simulant l'étage dans lequel le joueur circule.
*/
typedef struct plateau{
    Cell carte[NB_LIG][NB_COL];
}Plateau;

/*Fonction d'initailisation de Cell pour 
la structure Plateau*/
Cell initCell(Celltype type);

/*Fonction d'initialisation de plateau*/
void initialisationPlateau(Plateau *plateau);

/*Fonction d'initailisation de Case*/
Case initCase(int x, int y);

/*Fonction vérifiant la présence ou non de la Case (x,y) dans toexpand*/
int present_in_toexpand(Case * toexpand, int taille_toexpand, int x, int y);

/*Fonction ajoutant la Case (x,y) dans toexpand si elle n'est pas déjà présente*/
void addadjacents(Case * toexpand, int *taille_toexpand, int x, int y, Plateau plateau);

/*Fonction de suppresion du Case à l'indice ind dans toexpand*/
void deleteCase(Case * toexpand, int *taille_toexpand, int ind);

/*Fonction d'étectant si cette case est une salle ou un escalier*/
int room_or_not(Plateau plateau, int x, int y);

/*Fonction donnant le nombre de Case salle a distance 2, de la Case (x,y) dans plateau*/
int nb_room_distance_2(Plateau plateau, int x, int y);

/*Fonction donnant le nombre de Case salle a distance 1, de la Case (x,y) dans plateau*/
int nb_room_distance_1(Plateau plateau, int x, int y);

/*Fonction déterminant si une case (x,y) est admissible dans plateau*/
int addmissible(Plateau plateau, int x, int y);

/*Fonction de génération du terreain selon la méthode du Sujet*/
void generationaleaPlateau(Plateau *plateau);

/*Fonction de générant un trésor sur le terrain*/
void generation_tresor(Plateau *plateau, int x, int y, int etage);

/*Fonction de générant un monstre sur le terrain*/
void generation_monstre(Plateau *plateau, int x, int y, int etage);

/*Fonction de génération des monstres et des coffres sur le terrain*/
int generationentite(Plateau *plateau, int etage);

/*Fonction de générant un escalier descendant sur le terrain*/
void generation_stair_down(Plateau *plateau, int *x, int *y, int etage);

/*Fonction mettant à jour les monstres et trésors (mort ou ouvert)*/
void m_a_j_monster_treasure(Plateau *plateau, Character *perso);


#endif
