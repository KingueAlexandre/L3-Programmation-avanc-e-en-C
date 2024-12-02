#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include "Jeu.h"

int FindujeuPlateau(Plateau P){
	int i, j;
	for(i=0; i<NB_LIG ; i++) {
		for(j=0; j<NB_COL; j++) {
			if( (P.bloc[i][j]).lig != i || (P.bloc[i][j]).col != j){	/*Une case ne correspond pas à sa position initial. On renvoit 0 -> le jeu n'est pas finis*/
				return 0;
			}
		}
	}
	return 1;				/*Tout les cases sont à leur position initial. -> le jeu est finis*/
}

void TourPlateau(Plateau *P, int *case_nx, int *case_ny){

	MLV_Keyboard_button touche;
	int new_case_nx,new_case_ny;

	new_case_ny = *case_ny;
	new_case_nx = *case_nx;

	MLV_wait_keyboard( &touche, NULL, NULL );				/*On attend le clic du joueur*/

	while(1){
		/*On agit en focntion de ce clic*/
		if(touche == MLV_KEYBOARD_UP && *case_ny>0){				/*Flèche du haut*/
			new_case_ny=*case_ny-1;
			break;
		}else if(touche == MLV_KEYBOARD_DOWN && *case_ny<NB_LIG-1){		/*Flèche du bas*/
			new_case_ny=*case_ny+1;
			break;
		}else if(touche == MLV_KEYBOARD_RIGHT && *case_nx<NB_COL-1){		/*Flèche de gauche*/
			new_case_nx=*case_nx+1;
			break;
		}else if(touche == MLV_KEYBOARD_LEFT && *case_nx>0){			/*Flèche de droite*/
			new_case_nx=*case_nx-1;
			break;
		}

		MLV_wait_keyboard( &touche, NULL, NULL );
	}
	EchangeCasePlateau(P, *case_nx, *case_ny, new_case_nx,new_case_ny);		/*L'échange est éfectué*/
	*case_ny=new_case_ny;								/*Les coordonnées de la case noire sont changés*/
	*case_nx=new_case_nx;

}
