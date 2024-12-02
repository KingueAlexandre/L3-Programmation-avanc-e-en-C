#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Plateau.h"

void InitialisationPlateau(Plateau *P){
	int i, j;
	for(i=0; i<NB_LIG ; i++) {
		for(j=0; j<NB_COL; j++) {
			((P->bloc)[i][j]).lig = i;
			((P->bloc)[i][j]).col = j;
		}
	}
}

void EchangeCasePlateau(Plateau *P, int x, int y, int x2, int y2){
	int tmp;
	tmp = ((P->bloc)[y][x]).lig;
	((P->bloc)[y][x]).lig = ((P->bloc)[y2][x2]).lig;
	((P->bloc)[y2][x2]).lig = tmp;

	tmp = ((P->bloc)[y][x]).col;
	((P->bloc)[y][x]).col = ((P->bloc)[y2][x2]).col;
	((P->bloc)[y2][x2]).col = tmp;
}

void DebutdeJeuPlateau(Plateau *P, int *xn, int *yn, int nb){
	int i,choix,xe,ye;

	for(i=0; i<nb; i++){
		/*printf("%d et (%d,%d)\n",i,*xn,*yn);*/
		choix = rand()%2;

		if(choix == 0){ 			/*ECHANGE HORIZONTAL*/

			choix = rand()%2;

			if(choix == 0 && *xn < NB_COL-1){			/*CASE NOIR ECHANGER AVEC CELLE DU BAS*/
				EchangeCasePlateau(P, *xn, *yn, *xn+1, *yn);
				*xn+=1;
			}else if(choix == 0){										/*CASE NOIR ECHANGER AVEC CELLE DU HAUT*/
				EchangeCasePlateau(P, *xn, *yn, *xn-1, *yn);
				*xn-=1;
			}else if(choix == 1 && *xn > 0){					/*CASE NOIR ECHANGER AVEC CELLE DU HAUT*/
				EchangeCasePlateau(P, *xn, *yn, *xn-1, *yn);
				*xn-=1;
			}else if (choix == 1){										/*CASE NOIR ECHANGER AVEC CELLE DU BAS*/
				EchangeCasePlateau(P, *xn, *yn, *xn+1, *yn);
				*xn+=1;
			}

		}else{						/*ECHANGE VERTICAL*/

			choix = rand()%2;

			if(choix == 0 && *yn < NB_LIG-1){			/*CASE NOIR ECHANGER AVEC CELLE DU BAS*/
				EchangeCasePlateau(P, *xn, *yn, *xn, *yn+1);
				*yn+=1;
			}else if(choix == 0){										/*CASE NOIR ECHANGER AVEC CELLE DU HAUT*/
				EchangeCasePlateau(P, *xn, *yn, *xn, *yn-1);
				*yn-=1;
			}else if(choix == 1 && *yn > 0){					/*CASE NOIR ECHANGER AVEC CELLE DU HAUT*/
				EchangeCasePlateau(P, *xn, *yn, *xn, *yn-1);
				*yn-=1;
			}else if(choix == 1){										/*CASE NOIR ECHANGER AVEC CELLE DU BAS*/
				EchangeCasePlateau(P, *xn, *yn, *xn, *yn+1);
				*yn+=1;
			}



		}
	}

}
