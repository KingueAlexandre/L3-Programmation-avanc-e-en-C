#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echange_char(char *a, char *b){
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(int argc, char const * argv[]){
	
	int taille,i;
	char * stri;
	if(argc >= 2){
		taille = strlen(argv[1]);
		stri = (char *) malloc(sizeof(char)*(taille));
		strcpy(stri,argv[1]);
		printf("%s\n",stri );
		for(i=0; i<taille/2; i++){
			echange_char( &(stri[i]), &(stri[taille-i-1]) ) ;
		}
		printf("%s\n",stri );
	}
	return 0;
}