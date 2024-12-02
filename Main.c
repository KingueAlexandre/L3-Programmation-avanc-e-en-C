#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "Option.h"

int main(int argc, char const * argv[]){
	int i,taille,taille_courante;
	char *line,*nombre_courant;
	Pile pile;
	pile = NULL;
	line = readline("");
	add_history(line);
	while(strcmp(line,"q") != 0){
		taille = strlen(line)+1;
		nombre_courant = (char *)malloc(sizeof(char)*(taille));
		taille_courante = 0;
		for(i=0;i<taille;i++){
			if('0'<=line[i] && line[i]<='9'){
				/*chiffre détecter */
				nombre_courant[taille_courante]=line[i];
				taille_courante+=1;
			}else{
				if(taille_courante != 0){
					nombre_courant[taille_courante]='\0';
					/*insertion*/
					if(insererC(&pile,atoi(nombre_courant)) == -1){
						return 0;
					}
				}else{
					nombre_courant[taille_courante]=line[i];
					nombre_courant[taille_courante+1]='\0';
					if(strcmp(nombre_courant,"+") == 0){
						if(additionPile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"-") == 0){
						if(soustractionPile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"*") == 0){
						if(multiplicationPile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"/") == 0){
						if(divisionPile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"%%") == 0){
						if(moduloPile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"!") == 0){
						if(factoriellePile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"^") == 0){
						if(puissancePile(&pile) == -1){
							exit(EXIT_FAILURE);
						}
					}else if(strcmp(nombre_courant,"p") == 0){
						if(pile != NULL){
							printf("%d\n",pile->valeur);
						}else{
							printf("NULL\n");
						}
					}else if(strcmp(nombre_courant,"c") == 0){
						freePile(&pile);
					}else if(strcmp(nombre_courant,"a") == 0){
						affichePile(pile);
					}else if(strcmp(nombre_courant,"r") == 0){
						reversePile(&pile);

					}
				}
				nombre_courant[0] = '\0';
				taille_courante = 0;
			}
		}

		line = readline("");
		add_history(line);
	}

	affichePile(pile);
	freePile(&pile);
	affichePile(pile);

	return 0;
}