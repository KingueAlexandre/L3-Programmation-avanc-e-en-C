#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <MLV/MLV_all.h>

#include "../include/Jeu.h"
#include "../include/Graphique.h"
#include "../include/Donjon.h"

int main(int argc, char *argv[]){   
	int etage,preci,appr,ret,w_stair;
	Images textures;
	Donjon etage_courant;
	Inventaire inv;
	Tour tours;
    Save sauvegarde;
    srand(time(NULL));

	etage = 1;
	preci = 5;
	appr = 0;
	initInventaire(&inv);					
	tours = initTour();

	textures = initwindowMLV();											/*On télécharge les tetxures pour l'affichage*/

	if(Menu_MLV()){														/*Une nouvelle partie a était choisi*/
		sauvegarde.player = initPerso();
		if(insererC(&(sauvegarde.donjon), etage ) == -1){
			exit(0);
		}
		sauvegarde.etage_max = 0;

	}else{																/*On charge la dernière sauvegarde*/
		printf("save\n");
		lecture_partie(&sauvegarde);
		printf("done\n");
		etage_courant = etage_donjon(sauvegarde.donjon,etage);
		sauvegarde.player.pos.x = NB_COL/2;
		sauvegarde.player.pos.y = NB_LIG/2;
		if(sauvegarde.donjon == NULL){
			printf("???????????????????????????????????\n");
		}
		if(etage_courant == NULL){
			printf("???????????????????????????????????\n");
		}
	}
	etage_courant = etage_donjon(sauvegarde.donjon,etage);

	affichageMLV(etage_courant->plateau,textures,sauvegarde.player,etage,tours);			/*On affiche le Jeu*/

	while(sauvegarde.player.Hp >= 0){
		ret = tour_joueur_MLV(&(etage_courant->plateau), &(sauvegarde.player),preci,appr,&etage, &inv);
		if(ret == 0){																													/*Déplacement ou attaque du joueur (1 tour)*/
			m_a_j_monster_treasure(&(etage_courant->plateau),&(sauvegarde.player));								/*Disparition des montres morts et coffres ouverts*/
			nouvelles_stats(&(sauvegarde.player));																/*Possible mis a jour du niveau et des stats*/
			tour_monster(&(etage_courant->plateau), &(sauvegarde.player));										/*les monstres proches attaquent*/
			verif_tour(&(sauvegarde.player), &tours, &preci, &appr);											/*Les tours des potions actives sont comptés*/

		}else if(ret == 1){																												/*Changement d'étage*/

			if(etage_courant->plateau.carte[sauvegarde.player.pos.y][sauvegarde.player.pos.x].type == STAIR_UP){
				w_stair = 1;
			}else{
				w_stair = 0;
			}
			if(etage>sauvegarde.etage_max){																		/*Si l'étage n'a jamais était visité on l'ajoute*/
				if(insererC(&((sauvegarde.donjon)), etage) == -1){
					exit(0);
				}
				sauvegarde.etage_max = etage;
			}
			etage_courant = etage_donjon((sauvegarde.donjon),etage);
			if(etage_courant == NULL){
				break;
			}
			if(w_stair){																						/*En fonction du type de l'escalier on attributs une nouvelle position pour le prochain étage*/
				sauvegarde.player.pos.x = etage_courant->pos_stair_down.x;
				sauvegarde.player.pos.y = etage_courant->pos_stair_down.y;
			}else{
				sauvegarde.player.pos.x = NB_COL/2;
				sauvegarde.player.pos.y = NB_LIG/2;
			}
			verif_tour(&(sauvegarde.player), &tours, &preci, &appr);											/*Les tours des potions actives sont comptés*/

		}else if(ret == 2){																												/*Visite de l'inventaire*/
			InventaireMLV(&inv,&(sauvegarde.player),&tours,&preci,&appr);
		}else if(ret == 3){																												/*On quitte le jeu en cours*/
			break;
		}
		affichageMLV(etage_courant->plateau,textures,sauvegarde.player,etage,tours);		/*On affiche le Jeu*/
	}
	
    MLV_wait_seconds( 1 );

    if(sauvegarde.player.Hp >= 0){												/*Si le jeu n'est pas finis on le sauvegarde*/
    	sauvegarde_partie(sauvegarde);
    	printf("save done\n");
    }

	endwindowMLV(&textures);

	freePile(&(sauvegarde.donjon));

	return 0;
}
