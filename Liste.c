#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Liste.h"

Pile AlloueCellule(int entier){
	Cellule *ret;
	ret = (Pile)malloc(sizeof(Pile));
	if(ret != NULL){
		ret->valeur = entier;
		ret->suivant = NULL;
		return ret;
	}
	return NULL;
}

void affichePile(Pile pile){
	Pile index = pile;
	/*DEBUT AFFICHAGE*/
	while(index != NULL){
		printf("%d\n",index->valeur);
		index=index->suivant;
	}
	/*FIN AFFICHAGE*/
}

int insererC(Pile *pile, int entier){
	Cellule * cel;
	cel = AlloueCellule(entier);
	if(cel == NULL){
		printf("Erreur mémoire.\n");
		return -1;
	}
	if(*pile == NULL){
		*pile = cel;
		return 1;
	}
	cel->suivant = *pile;
	*pile = cel;
	return 1;
}

void freePile(Pile *pile){
	Cellule *iter = *pile;
    Cellule *temp = iter;
    while (iter != NULL) {
        temp = iter->suivant;
        free(iter);
        iter = temp;
    }
    *pile = NULL;
}

void supprimetetePile(Pile *pile){
	Pile index = *pile;
	*pile = (*pile)->suivant;
	index->suivant = NULL;
	freePile(&index);
}

int reversePile(Pile *pile){
	Pile index = (*pile)->suivant;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return -1;
	}
	(*pile)->suivant = (*pile)->suivant->suivant;
	index->suivant = (*pile);
	(*pile) = index;
	return 1;
}