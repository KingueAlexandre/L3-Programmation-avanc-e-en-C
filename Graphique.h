#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include "Plateau.h"

#define TAILLE_FENETRE (512+(NB_LIG-1)*10)

/*FONCTION SIMULANT UN MENU.
Renvoit un MLV_Image * dépendant du choix du joueur,peut renvoyer un NULL
si le joueur veut arreter là*/
MLV_Image * Menu_MLV();

/*Affiche le Jeu sous MLV*/
void Affichage_Taquin_MLV(Plateau plateau, MLV_Image *image);

/*Affiche le Jeu avec terminal*/
void Affichage_Taquin_terminal(Plateau plateau);

/*Affiche le temps mis par le joueur*/
void Affichage_gagnant(int temps);

#endif
