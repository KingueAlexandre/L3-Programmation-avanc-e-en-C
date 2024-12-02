#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include "Graphique.h"

MLV_Image * Menu_MLV(){
	int x=0,y=0;
	MLV_Image * Image;
	MLV_draw_filled_rectangle(0,0,TAILLE_FENETRE,TAILLE_FENETRE,MLV_COLOR_BLACK);

	MLV_draw_text(TAILLE_FENETRE/2-40, TAILLE_FENETRE/12, "TAQUIN !!!", MLV_COLOR_WHITE);

	/*Montre les différentes images disponibles*/
	MLV_draw_partial_image(MLV_load_image("pikachu.jpg"), 10, TAILLE_FENETRE/5, TAILLE_FENETRE-20, 100, 10, TAILLE_FENETRE/5);
	MLV_draw_partial_image(MLV_load_image("paysage.png"), 10, TAILLE_FENETRE*2/5, TAILLE_FENETRE-20, 100, 10, TAILLE_FENETRE*2/5);
	MLV_draw_partial_image(MLV_load_image("panda.png"), 10, TAILLE_FENETRE*2/5, TAILLE_FENETRE-20, 100, 10, TAILLE_FENETRE*3/5);
	MLV_draw_partial_image(MLV_load_image("galaxy.png"), 10, TAILLE_FENETRE*2/5, TAILLE_FENETRE-20, 100, 10, TAILLE_FENETRE*4/5);
	
	/*Affiche le bouton quitter*/
	MLV_draw_filled_rectangle(TAILLE_FENETRE-50,0,50,50,MLV_COLOR_WHITE);
	MLV_draw_text(TAILLE_FENETRE-48, 20, "quitter",MLV_COLOR_BLACK);

	MLV_actualise_window();
	
	while(1){
		MLV_wait_mouse(&x, &y);							/*On récupère le choix du joueur*/
		if( (10<=x && x<=TAILLE_FENETRE-10) && (TAILLE_FENETRE/5<=y && y<=TAILLE_FENETRE/5+100) ){		/*Choisis pikachu*/
			Image = MLV_load_image("pikachu.jpg");
			break;
		}else if( (10<=x && x<=TAILLE_FENETRE-10) && (TAILLE_FENETRE*2/5<=y && y<=TAILLE_FENETRE*2/5+100) ){	/*Choisis paysage*/
			Image = MLV_load_image("paysage.png");
			break;
		}else if( (10<=x && x<=TAILLE_FENETRE-10) && (TAILLE_FENETRE*3/5<=y && y<=TAILLE_FENETRE*3/5+100) ){	/*Choisis panda*/
			Image = MLV_load_image("panda.png");
			break;
		}else if( (10<=x && x<=TAILLE_FENETRE-10) && (TAILLE_FENETRE*4/5<=y && y<=TAILLE_FENETRE*4/5+100) ){	/*Choisis galaxy*/
			Image = MLV_load_image("galaxy.png");
			break;
		}else if( x>=TAILLE_FENETRE-50 && y<=50 ){				/*Le joueur veut arréter on renvoit NULL*/
			Image = NULL;
			break;
		}
		MLV_actualise_window();
	}
	return Image;
}

void Affichage_Taquin_MLV(Plateau plateau, MLV_Image *image){
	int taille_case,pas_x,pas_y;
	int i,j;
	taille_case = 512/4;
	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){

			pas_y = i*10;
			pas_x = j*10;
			if(plateau.bloc[i][j].col != 3 || plateau.bloc[i][j].lig != 3){
				/*Affiche la case sauvegardé en plateau.bloc[i][j] de l'image dans sa position courante (i,j)*/
				MLV_draw_partial_image(image, taille_case*plateau.bloc[i][j].col, taille_case*plateau.bloc[i][j].lig, taille_case, taille_case, taille_case*j + pas_x, taille_case*i + pas_y);
			}
		}
	}
}

void Affichage_Taquin_terminal(Plateau plateau){
	int taille_case,pas_x,pas_y;
	int i,j;
	taille_case = (TAILLE_FENETRE-10)/4;
	for(i=0; i<NB_LIG; i++){			/*Parcours vertical*/
		for(j=0; j<NB_COL; j++){		/*Parcours horizontal*/

			pas_y = i*10;
			pas_x = j*10;
			if(plateau.bloc[i][j].col != 3 || plateau.bloc[i][j].lig != 3){			/*Affiche la vériatble position de la case se situant en (i,j)*/
				printf("[%d,%d]",plateau.bloc[i][j].col,plateau.bloc[i][j].lig);
			}else{
				printf("[N,N]");							/*Affcihe la case noire*/
			}
		}
		printf("\n");
	}
	printf("\n");
}

void Affichage_gagnant(int temps){

	MLV_draw_text(TAILLE_FENETRE-115, TAILLE_FENETRE-115, "YOU WIN !!!", MLV_COLOR_WHITE);
	MLV_draw_text(TAILLE_FENETRE-115, TAILLE_FENETRE-102, "%d:%d:%d", MLV_COLOR_WHITE,temps/3600000,temps/60000,temps/1000);

}
