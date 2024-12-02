#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 30

void dessin_string(char * text, int taille, int ligne){

	int i,i2,taille_dernier_mot;

	for(i = 0; i < ligne+4; i++){
		printf("-");
	}
	printf("\n");
	taille_dernier_mot = 0;
	for(i = 0; i < taille; ++i){
		if(i == 0){
			printf("| ");
		}
		if(text[i] == '\n'){
			for(i2 = 0; i2 < ligne-taille_dernier_mot; i2++){
				printf(" ");
			}
			printf(" |");
			printf("%c",text[i]);
			printf("| ");
			taille_dernier_mot = 0;
		}else{
			taille_dernier_mot += 1;
			printf("%c",text[i]);
		}
	}
	for(i2 = 0; i2 < ligne-taille_dernier_mot; i2++){
		printf(" ");
	}
	printf(" |\n");
	for(i = 0; i < ligne+4; i++){
		printf("-");
	}
	printf("\n");

	printf("    \\ \n");
	printf("     \\  °  _____\n");
	printf("      \\  0/ .   \\  /|\n");
	printf("       \\O \\      |/ |\n");
	printf("          /      |\\ |\n");
	printf("          \\_____/  \\|    \n");

	

	printf("\n");


}



int main(int argc, char const * argv[]){
	
	int taille,taille_pre,max_ligne,ligne,i;
	char *stri;
	taille = 0;
	taille_pre = 0;
	max_ligne = 0;
	ligne = 0;
	printf("%d\n",taille );

	for(i=1; i<argc; i++){
		taille += strlen(argv[i])+1;
		ligne += strlen(argv[i])+1;
		if(taille_pre%TAILLE_MAX > taille%TAILLE_MAX){
			taille+=1;
			if(ligne>max_ligne){
				max_ligne = ligne;
			}
			ligne = 0;
		}
		taille_pre = taille;
	}
	stri = (char *)malloc(sizeof(char)*taille);

	taille = 0;
	taille_pre = 0;

	for(i=1; i<argc; i++){
		taille += strlen(argv[i])+1;
		strcat(&(stri[taille_pre]),argv[i]);
		strcat(&stri[taille]," ");
		if(taille_pre%TAILLE_MAX > taille%TAILLE_MAX){
			taille+=1;
			strcat(&stri[taille],"\n");
		}
		printf("%d%s\n",taille,stri);
		taille_pre = taille;
	}
	dessin_string(stri,taille,max_ligne);
	free(stri);

	return 0;
}