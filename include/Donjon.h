#ifndef __DONJON__
#define __DONJON__

#include "Plateau.h"

/*
Structure Donjon
Liste chianée simulant l'entièreté du donjon.
*/
typedef struct donjon{
    int etage;
    Plateau plateau;
    struct donjon *suivant;
    Case pos_stair_down;
}Niveau,*Donjon;

/*
Structure Save
Possédant les structures importantes, elle sert à sauvegarder les données importantes dans un fichier.
*/
typedef struct savedata{
    Donjon donjon;
    Character player;
    int etage_max;
}Save;

/* Fonction d'allocation de la mémoire pour
la creation d'une cellule de donjon*/
Niveau *AlloueCellule(int etage);

/* Fonction d'insertion d'une nouvelle cellule*/
int insererC(Donjon *donjon, int etage);

/* Fonction de suppresion de la liste chainée 
donjon et de sa mémoire alloué*/
void freePile(Donjon *donjon);

/*Fonction de recherche qui renvoit une 
cellule de la liste chainée*/
Donjon etage_donjon(Donjon donjon, int etage);

int sauvegarde_partie(Save sauvegarde);

int lecture_partie(Save * sauvegarde);

#endif