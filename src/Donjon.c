#include <stdio.h>
#include <stdlib.h>

#include "../include/Donjon.h"

Niveau *AlloueCellule(int etage){
	Niveau *ret;
	ret = (Niveau*)malloc(sizeof(Niveau));
	if(ret != NULL){
		ret->etage = etage;
		initialisationPlateau(&(ret->plateau));							/*On place les murs*/
		generationaleaPlateau(&(ret->plateau));							/*On fait la génération du terreain*/
		if(generationentite(&(ret->plateau), etage) != 1){				/*On ajoute les monstres et coffres*/
	        fprintf(stderr, "Plateau mal généré\n");
	        return NULL;
	    }
	    generation_stair_down(&(ret->plateau),&(ret->pos_stair_down.x),&(ret->pos_stair_down.y),etage);			/*On ajoute l'escalier descendant*/
		ret->suivant = NULL;
		return ret;
	}
	return NULL;
}

int insererC(Donjon *donjon, int etage){
	Niveau * cel;
	cel = AlloueCellule(etage);
	if(cel == NULL){													/*Problème mémoire on arrete tout*/
		printf("Erreur mémoire.\n");
		return -1;
	}
	if(*donjon == NULL){
		*donjon = cel;
		return 1;
	}
	cel->suivant = *donjon;
	*donjon = cel;
	return 1;
}

void freePile(Donjon *donjon){
	Niveau *iter = *donjon;
    Niveau *temp = iter;
    while (iter != NULL) {
        temp = iter->suivant;
        free(iter);
        iter = temp;
    }
    *donjon = NULL;
}

Donjon etage_donjon(Donjon donjon, int etage){
	Niveau *ret=donjon;
	while(ret!=NULL){													/*Parcours de la liste chainée*/	
		if((*ret).etage == etage){										/*On a trouvé ce qu'on cherchait*/
			return ret;
		}
		
		ret = (*ret).suivant;
	}
	return NULL;														/*Rien n'a était trouvé*/
}

int sauvegarde_partie(Save sauvegarde){
    FILE * file;
        
    Save save[1];
    
    save[0] = sauvegarde;
    
    file = fopen("SaveDate.bin", "wb");
    if(file == NULL){
        fprintf(stderr, "Erreur d'ouverture de fichier\n");
        return 0;
    }
    
    fwrite(save, sizeof(Save), 1, file);
    fclose(file);
    
    return 1;
}

int lecture_partie(Save * sauvegarde){
    FILE * file;
    
    Save save[1] = {0};
    
    file = fopen("SaveDate.bin", "rb");
    if(file == NULL){
        fprintf(stderr, "Erreur d'ouverture de fichier\n");
        return 0;
    }
    
    fread(save, sizeof(Save), 1, file);
    fclose(file);
    
    *sauvegarde = save[0];
    
    return 1;
}