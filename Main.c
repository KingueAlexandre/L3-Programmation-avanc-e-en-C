#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>

#include "Jeu.h"

int main(int argc, char const * argv[]){

	srand(time(NULL));
	int i,case_noir_x,case_noir_y,ech,temps1,temps2;
	MLV_Image *Image;
	Plateau plateau;

	InitialisationPlateau(&plateau);			/*INITIALISATION DU PLATEAU*/
	case_noir_y = 3;					/*On établit la position de la case au noir*/
	case_noir_x = 3;
	ech = 3;						/*Le nombre d'échange*/

	MLV_create_window("Taquin","Taquin",TAILLE_FENETRE,TAILLE_FENETRE);		/*CREATION DE LA FENETRE*/
	
	Image = Menu_MLV();					/*Le joueur a choisit son image*/
	while(Image != NULL){					/*Taquin continue tant que le joueur a choisit une image*/
		MLV_draw_filled_rectangle(0,0,TAILLE_FENETRE,TAILLE_FENETRE,MLV_COLOR_BLACK);
		Affichage_Taquin_MLV(plateau,Image);			/*On affiche l'image intacte avant de commencer*/
		MLV_actualise_window();

		MLV_wait_keyboard( NULL, NULL, NULL );			/*L'utilisateur décide de lancer le jeu*/

		MLV_draw_filled_rectangle(0,0,TAILLE_FENETRE,TAILLE_FENETRE,MLV_COLOR_BLACK);
		DebutdeJeuPlateau(&plateau, &case_noir_x, &case_noir_y, ech);			/*Le plateau est mélangé "ech" fois*/
		Affichage_Taquin_MLV(plateau,Image);
		MLV_actualise_window();
		
		temps1 = MLV_get_time();
		/*PARTIE CONCERNANT LE JEU*/
		while(FindujeuPlateau(plateau) == 0){			/*Tant que le plateau n'as pas retrouvé sa position initial, le jeu continue*/
			TourPlateau(&plateau, &case_noir_x, &case_noir_y);			/*Le joueur a choisi un déplacement*/
			MLV_draw_filled_rectangle(0,0,TAILLE_FENETRE,TAILLE_FENETRE,MLV_COLOR_BLACK);			
			Affichage_Taquin_MLV(plateau,Image);		/*On reaffiche le plateau*/
			MLV_actualise_window();
		}
		temps2 = MLV_get_time();				/*On récupère le temps mis par le joueur*/
		Affichage_gagnant(temps2-temps1);
		MLV_actualise_window();

		MLV_wait_keyboard( NULL, NULL, NULL );			/*On attend un clique pour sortir*/
	
		MLV_draw_filled_rectangle(0,0,TAILLE_FENETRE,TAILLE_FENETRE,MLV_COLOR_BLACK);			
		Image = Menu_MLV();					/*Le joueur choisit encore son image*/
	}


	MLV_free_window();					/*LA FENETRE EST DETRUITE*/

	return 0;
}
