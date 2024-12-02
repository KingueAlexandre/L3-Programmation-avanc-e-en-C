#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const * argv[]){
	/*La suite finit par stationner à 15.403683 avec un float et un int*/
	/*La suite est bien plus précise avec un double pour la Série et un 
	long long int pour le n. On va bien au dela du résultat précédent.*/
	long long int i;
	double harm;

	i = 1;
	harm = 0.0;
	while(1){
		harm+= 1.0/i;
		if(i%1000000 == 0){
			printf("%lld : %lf\n",i,harm );
		}
		i++;
	}

	return 0;
}