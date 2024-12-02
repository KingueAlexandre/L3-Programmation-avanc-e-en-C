#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <ftw.h>
#define MAX 1000
#define TAILLE 10

typedef struct Fichier{
	char name[MAX];
	long long int size_oc;
}Fichier;

struct Fichier grosfichier[TAILLE];
int nbajout = 0;
int nbfichier = 0;

Fichier creationFichier(const char name[MAX], unsigned long size){
	Fichier ret;
	ret.size_oc = size;
	strcpy(ret.name,name);
	return ret;
}

void initGrosFichier(){
	int i;
	for(i=0; i<TAILLE; i++){
		grosfichier[i] = creationFichier("",0);
	}
}

void trieGrosFichier(Fichier nouv){
	int i;
	Fichier tmp;
	for(i=0; i<TAILLE; i++){
		if(grosfichier[i].size_oc <= nouv.size_oc){
			tmp = grosfichier[i];
			grosfichier[i] = nouv;
			nouv = tmp;
		}
	}
}

void afficheGrosFichier(){
	int i;
	printf("Début affichage\n");
	for(i=0; i<TAILLE; i++){
		printf("%s : %d octets\n", grosfichier[i].name, grosfichier[i].size_oc);
	}
	printf("Fin affichage\n");
}

int aux(const char* fpath, const struct stat *sb, int typeflag){
	Fichier tmp;
	nbfichier++;
	if(typeflag == FTW_F && sb->st_size >= grosfichier[TAILLE-1].size_oc){
		tmp = creationFichier(fpath,sb->st_size);
		trieGrosFichier(tmp);
		nbajout++;
	}else{
	}
	return 0;
}

int main(int argc, char const * argv[]){
	initGrosFichier();
	if(argc < 2){
		printf("Pas assez d'argument.\n");
		exit(EXIT_FAILURE);
	}else if(argc > 2){
		printf("Argument(s) inutile(s).");
	}

	printf("%s\n",argv[1] );
	
	if( ftw(argv[1],aux,40) != -1){
		printf("			Execution correcte\n");
	}else{
		printf("			Execution ratée\n");
	}
	afficheGrosFichier();

	return 0;
}