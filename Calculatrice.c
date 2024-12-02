#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct  cell{
	int valeur;
	struct cell *suivant;

}Cellule,*Pile;

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
	while(index != NULL){
		printf("%d\n",index->valeur);
		index=index->suivant;
	}
	printf("FIN\n");
}

int insererC(Pile *pile, int entier){
	Pile index = *pile;
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
	while(index->suivant != NULL){
		index = index->suivant;
	}
	index->suivant = cel;
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
	Pile *index = pile;
	*pile = (*index)->suivant;
	(*index)->suivant = NULL;
	freePile(index);
}

int additionPile(Pile *pile){	
	int val;
	if((*pile) == NULL || (*pile)->suivant == NULL){
		return -1;
	}
	val = (*pile)->valeur + (*pile)->suivant->valeur;
	supprimetetePile(pile);
	supprimetetePile(pile);
	if(insererC(pile,val) == 1){
		return -1;
	}	
	return 1;
}

int main(int argc, char const * argv[]){
	int i,taille,taille_courante;
	char *line,*nombre_courant;
	Pile pile;
	pile = NULL;
	line = readline("");
	add_history(line);
	while(strcmp(line,"q") != 0){

		if(strcmp(line,"+") == 0){
			additionPile(&pile);
		}else if(strcmp(line,"-") == 0){

		}else if(strcmp(line,"*") == 0){

		}else if(strcmp(line,"/") == 0){

		}else if(strcmp(line,"%%") == 0){

		}else if(strcmp(line,"!") == 0){

		}else if(strcmp(line,"^") == 0){

		}else if(strcmp(line,"p") == 0){
			if(pile != NULL){
				printf("%d\n",pile->valeur);
			}else{
				printf("NULL\n");
			}
		}else if(strcmp(line,"c") == 0){
			freePile(&pile);
		}else if(strcmp(line,"a") == 0){
			affichePile(pile);
		}else if(strcmp(line,"r") == 0){

		}else{
			taille = strlen(line);
			nombre_courant = (char *)malloc(sizeof(char)*(taille+1));
			taille_courante = 0;
			for(i=0;i<taille;i++){
				if('0'<=line[i] && line[i]<='9'){
					printf("		%d chiffre détecter : %c\n",i,line[i]);	
					nombre_courant[taille_courante]=line[i];
					taille_courante+=1;
				}else{
					if(taille_courante != 0){
						nombre_courant[taille_courante]='\0';
						printf("		insertion : %s\n",nombre_courant );
						insererC(&pile,atoi(nombre_courant));
					}else{
						printf("		pas d'insertion\n");
					}
					nombre_courant[0] = '\0';
					taille_courante = 0;
				}
			}
			if('0'<=line[i] && line[i]<='9'){
				printf("		%d chiffre détecter : %c\n",i,line[i]);	
				nombre_courant[taille_courante]=line[i];
				taille_courante++;
			}else{
				if(taille_courante != 0){
					nombre_courant[taille_courante]='\0';
					printf("		insertion : %s\n",nombre_courant );
					insererC(&pile,atoi(nombre_courant));
				}else{
					printf("		pas d'insertion\n");
				}
				nombre_courant[0] = '\0';
				taille_courante = 0;
			}
			nombre_courant = "";
			printf("?\n");
		}
		line = readline("");
		add_history(line);
		/*
		if(insererC(&pile,rand()%50) == -1){
			printf("Arret du programme.\n");
		}
		*/
	}
	affichePile(pile);
	freePile(&pile);
	affichePile(pile);

	return 0;
}