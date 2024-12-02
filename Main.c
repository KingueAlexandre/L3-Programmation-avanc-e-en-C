#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "code.h"

void tri_tab(Bitkey *tab){
	int i,j,tmpi;
	Bitkey tmp;
	for(i=0;i<8;i++){
		tmpi = fitness_key(&(tab[i]));
		for(j=i+1;j<8;j++){
			if(tmpi < fitness_key(&(tab[j])) ){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}
}

Bitkey accouplement_bkeys(Bitkey b1, Bitkey b2, Bitkey b3){
	int i;
	Bitkey key_ret;
	for(i=0;i<NB_OCT;i++){
		key_ret.values[i] = (b1.values[i] & b2.values[i]) | (b3.values[i] & b1.values[i]) | (b3.values[i] & b2.values[i]);
	}
	return key_ret;
}


Bitkey generation_alea(){
	int i;
	Bitkey bkey;
	for(i=0;i<NB_OCT;i++){
		bkey.values[i] = rand()%256;
	}
	return bkey;
}

int comparaison(const void * key1, const void * key2){
	Bitkey b1 = *(const Bitkey*)key1;
	Bitkey b2 = *(const Bitkey*)key2;
	return fitness_key(&b2) - fitness_key(&b1);
}

void generate_cle_generation(Bitkey* B, int d){
	int i;
	Bitkey * keys;

	if(d == 0){
		*B = generation_alea();	/*une clé aléatoire dans B*/
		return;
	}

	keys = (Bitkey *)malloc(sizeof(Bitkey)*8);	/*allocation d’un tableau de 8 clés*/
	for(i=0;i<8;i++){
		generate_cle_generation(&keys[i],d-1);	/*génération de 8 clé de génération d-1 ( 10 appels récursifs )*/
	}

	/*tri du tableau*/
	/*tri_tab(keys);*/
	qsort(keys,8,sizeof(Bitkey),comparaison);

	*B = accouplement_bkeys(keys[0],keys[1],keys[2]);/*accouplement des 3 meilleurs clés et fabrication de l’enfant dans B*/

	printf("%f\n",fitness_key(B));
	free(keys);				/*libération mémoire du tableau*/
}

void affiche_Bitkey(Bitkey *B){
	int i;
	for(i=0; i<NB_OCT; i++){
	}
}

int main(int argc, char const * argv[]){
	Bitkey keys;

	srand(time(NULL));
	
	keys = generation_alea();
	
	generate_cle_generation(&keys,7);

	printf("\n\n\n%f\n",fitness_key(&keys));


	enter_the_matrix(&keys);
	return 0;
}
