#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Option.h"

int additionPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		printf("Pas assez d'élément dans ta pile\n");
		return 1;
	}
	val = (*pile)->valeur + (*pile)->suivant->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);

	return insererC(pile,val);
}

int soustractionPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return 1;
	}
	val = (*pile)->suivant->valeur - (*pile)->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);
	
	return insererC(pile,val);
}

int multiplicationPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return 1;
	}
	val = (*pile)->valeur * (*pile)->suivant->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);
	
	return insererC(pile,val);
}

int divisionPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return 1;
	}
	if((*pile)->valeur == 0){
		printf("Division par zéro!\n");
		return 1;
	}
	val = (*pile)->suivant->valeur / (*pile)->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);
	
	return insererC(pile,val);
}

int moduloPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return 1;
	}
	if((*pile)->valeur == 0){
		printf("Division par zéro!\n");
		return 1;
	}
	val = (*pile)->suivant->valeur % (*pile)->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);
	
	return insererC(pile,val);

}


int factoriellePile(Pile *pile){	
	int i,val;
	if((*pile) == NULL){
		return 1;
	}
	if((*pile)->valeur < 0){
		printf("Les factorielles de nombre négatif n'existent pas!\n");
		return 1;
	}

	val = 1;
	for(i=1; i<=(*pile)->valeur; i++){
		val*=i;
	}
	supprimetetePile(pile);
	
	return insererC(pile,val);
}



int puissancePile(Pile *pile){	
	int i,val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return 1;
	}
	if((*pile)->valeur < 0){
		printf("Les puissances de nombre négatif n'existent pas!\n");
		return 1;
	}

	val = 1;
	for(i=0; i<(*pile)->valeur; i++){
		val*=(*pile)->suivant->valeur;
	}
	supprimetetePile(pile);
	supprimetetePile(pile);
	
	return insererC(pile,val);
}