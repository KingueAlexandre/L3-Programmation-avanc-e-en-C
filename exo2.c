#include <stdio.h>
#include <stdlib.h>

int nombres_binomiaux(int n, int p){
	if(n < 0 || p < 0 || p > n){
		return -1;
	}
	if(p == 0 || n == p){
		return 1;
	}
	return nombres_binomiaux(n-1,p) + nombres_binomiaux(n-1,p-1);
}

int ** alloue_tab(int n, int p){
	int **tab;
	int i,j;

	tab=(int **)malloc(sizeof(int *) * (n+1));
	for(i=0; i<n+1; i++){
		tab[i]=(int *)malloc(sizeof(int) * (i+1));
		for(j=0; j<p; j++){
			tab[i][j]=0;
		}
	}

	return tab;
}


int nombres_binomiaux2(int n, int p, int **tab){

	if(n < 0 || p < 0 || p > n){
		return -1;
	}
	if(tab[n][p] != 0){
		return tab[n][p];
	}
	if(p == 0 || n == p){
		tab[n][p] = 1;
		return 1;
	}
	tab[n][p] = nombres_binomiaux2(n-1,p,tab) + nombres_binomiaux2(n-1,p-1,tab);
	return tab[n][p];
}

void free_tab(int n, int **tab){
	int i;

	for(i=0; i<n; i++){
		free(tab[i]);
	}
	free(tab);
	return ;
}

void affiche_tab(int n, int p, int **tab){
	int i,j;

	for(i=0; i<n+1; i++){
		printf("%d		",i);
		for(j=0;j<i+1; j++){
			printf("%d ",tab[i][j]);
		}
		printf("\n");
	}
	printf("FIN\n");
	return ;
}

int main(int argc, char const * argv[]){

	int n = 24, p = 2;
	int **tab;
	
	if(argc<2){
		n = atoi(argv[1]);
	}
	if(argv<3){
		p = atoi(argv[2]);
	}
	printf("b(%d,%d) = %d\n",n,p,nombres_binomiaux(n,p));

	tab=alloue_tab(n,p);
	printf("Initialisation\n");
	affiche_tab(n,p,tab);
	printf("Calcul binomiaux\n");
	nombres_binomiaux2(n, p, tab);
	affiche_tab(n,p,tab);
	printf("b(%d,%d) = %d\n",n,p,tab[n][p]);
	free_tab(n,tab);
	return 0;
}
