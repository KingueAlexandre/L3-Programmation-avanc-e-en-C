#include <stdio.h>




int main(int argc, char const * argv[]){

	char caractere;
	FILE *fichier = NULL;

	if(argc>1){
		fichier = fopen(argv[1],"w");
	}else{
		fichier = fopen("ERROR.log","w");
	}

	while( ( caractere = fgetc(stdin) ) != EOF){
		if(fichier != NULL){
			fputc(caractere,fichier);
		}
		printf("%c",caractere);

	};
	printf("\n");

	if(fichier != NULL){
		fclose(fichier);
	}

	return 0;
}
