#ifndef __Jeu__
#define __Jeu__

#include "Plateau.h"
#include "Graphique.h"

/*Fonction gérant les actions du joueur*/
int tour_joueur_MLV(Plateau *plateau, Character *perso, int  preci, int  appr, int *etage, Inventaire *inv);

/*Fonction gérant les actions du monstres*/
void tour_monster(Plateau *plateau, Character *perso);

/*Fonction d'attaque de mélée du joueur*/
void attack_pl(Character * player, Monster * monster, int preci);

/*Fonction de magie de mélée du joueur*/
void magic_pl(Character * player, Monster * monster, int preci);

/*Fonction d'attaque du mosntre*/
void attack_ms(Character * player, Monster * monster);

/*Fonction d'initilisastion de Tout*/
Tour initTour();

/*Fonction déclanchant les effets des potions bu par le joueur*/
void utilise_potion(Character * player, char * potion, Tour * tour, int * preci, int * appr);

/*Fonction appliquant les effets sur la durée des potions bu par le joueur*/
int verif_tour(Character * player, Tour * tour, int * preci, int * appr);

/*Fonction servant à détectant un Lv up et à ajouter ces nouvelles stats*/
void nouvelles_stats(Character * player);

/*Fonction simulant l'inventaire, pour "boire" ou "jeter" les potions présentes dedans*/
void InventaireMLV(Inventaire *inv, Character *perso, Tour *tour, int *preci, int *appr);

#endif
