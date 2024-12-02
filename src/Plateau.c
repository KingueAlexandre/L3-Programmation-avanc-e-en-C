#include <stdio.h>
#include <stdlib.h>

#include "../include/Plateau.h"

Cell initCell(Celltype type){
	Cell ret;
	ret.type = type;
	return ret;
}

void initialisationPlateau(Plateau *plateau){
	int i,j;
	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){
			plateau->carte[i][j] = initCell(0);
		}
	}
}

int distance_case(Plateau plateau, int x1, int y1, int x2, int y2){
	return abs(x1-x2)+abs(y1-y2);
}

void init_nb_mur_addj(Plateau plateau, int tab[][NB_COL]){
	int i,j;
	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){
			tab[i][j] = nb_room_distance_1(plateau,j,i);
		}
	}
}

Case initCase(int x, int y){
	Case ret;
	ret.x = x;
	ret.y = y;
	return ret;
}

int present_in_toexpand(Case * toexpand, int taille_toexpand, int x, int y){
	int i;
	for(i=0; i<taille_toexpand; i++){
		if(toexpand[i].x == x && toexpand[i].y == y){  				/*Case présente dans toexpand*/
			return 1;
		}
	}
	return 0;										  				/*Case non présente dans toexpand*/
}

void addadjacents(Case * toexpand, int *taille_toexpand, int x, int y, Plateau plateau){

	if((0<x+1 && x+1<NB_COL-1) && (0<y && y<NB_LIG-1)){				/*Case dans les bornes*/
		if(plateau.carte[y][x+1].type == WALL && present_in_toexpand(toexpand,*taille_toexpand,x+1,y) == 0){			/*Case de droite ajouté dans toexpand*/
			*taille_toexpand+=1;
			toexpand[*taille_toexpand-1] = initCase(x+1,y);
		}
	}
	if((0<x-1 && x-1<NB_COL-1) && (0<y && y<NB_LIG-1)){				/*Case dans les bornes*/
		if(plateau.carte[y][x-1].type == WALL && present_in_toexpand(toexpand,*taille_toexpand,x-1,y) == 0){			/*Case de gauche ajouté dans toexpand*/
			*taille_toexpand+=1;
			toexpand[*taille_toexpand-1] = initCase(x-1,y);
		}
	}
	if((0<x && x<NB_COL-1) && (0<y+1 && y+1<NB_LIG-1)){				/*Case dans les bornes*/
		if(plateau.carte[y+1][x].type == WALL && present_in_toexpand(toexpand,*taille_toexpand,x,y+1) == 0){			/*Case du bas ajouté dans toexpand*/
			*taille_toexpand+=1;
			toexpand[*taille_toexpand-1] = initCase(x,y+1);
		}
	}
	if((0<x && x<NB_COL-1) && (0<y-1 && y-1<NB_LIG-1)){				/*Case dans les bornes*/
		if(plateau.carte[y-1][x].type == WALL && present_in_toexpand(toexpand,*taille_toexpand,x,y-1) == 0){			/*Case du haut ajouté dans toexpand*/
			*taille_toexpand+=1;
			toexpand[*taille_toexpand-1] = initCase(x,y-1);
		}
	}

}

void deleteCase(Case * toexpand, int *taille_toexpand, int ind){
	int i;
	Case tmp;
	for(i=0;i<*taille_toexpand;i++){
		if(ind<=i){
			tmp = toexpand[i];
			toexpand[i] = toexpand[i+1];
			toexpand[i+1] = tmp;
		}
	}
	*taille_toexpand-=1;
}

int room_or_not(Plateau plateau, int x, int y){
	if( (0<x && x<NB_COL-1) && (0<y && y<NB_LIG-1) && (plateau.carte[y][x].type == ROOM || plateau.carte[y][x].type == STAIR_UP) ){
		return 1;
	}
	return 0;
}

int nb_room_distance_2(Plateau plateau, int x, int y){
	int ret;

	ret = room_or_not(plateau,x+2,y);
	ret += room_or_not(plateau,x+1,y+1);
	ret += room_or_not(plateau,x+1,y-1);
	ret += room_or_not(plateau,x,y+2);
	ret += room_or_not(plateau,x,y-2);
	ret += room_or_not(plateau,x-1,y+1);
	ret += room_or_not(plateau,x-1,y-1);
	ret += room_or_not(plateau,x-2,y);

	return ret;
}

int nb_room_distance_1(Plateau plateau, int x, int y){
	int ret;

	ret = room_or_not(plateau,x+1,y);
	ret += room_or_not(plateau,x,y+1);
	ret += room_or_not(plateau,x,y-1);
	ret += room_or_not(plateau,x-1,y);

	return ret;
}

int addmissible(Plateau plateau, int x, int y){
	return nb_room_distance_1(plateau,x,y) == 1 && nb_room_distance_2(plateau,x,y) <= 2;
}

void generationaleaPlateau(Plateau *plateau){
	int stair_up_x,stair_up_y,i,j;
	int taille_toexpand,ind_rand,tour;
	int nb_mur_addj[NB_LIG][NB_COL];

	Case c;
	Case *toexpand;

	tour = 0;
	taille_toexpand = 0;
	stair_up_x = NB_COL/2;
	stair_up_y = NB_LIG/2;
	toexpand = (Case *)malloc(sizeof(Case)*(NB_LIG*NB_COL));

	plateau->carte[stair_up_y][stair_up_x].type = STAIR_UP;
	addadjacents(toexpand,&taille_toexpand,stair_up_x,stair_up_y,*plateau);					/*Etape 1: Initailisation de la liste toexpand*/

	while(taille_toexpand!=0){																/*On continue tant que toexpand n'est pas vide*/
		ind_rand = rand()%taille_toexpand;													/*Etape 2: On tire une case aléatoire dans toexpand*/
		c = toexpand[ind_rand];
		deleteCase(toexpand,&taille_toexpand,ind_rand);								/*On supprime la case de la liste*/
		if(addmissible(*plateau,c.x,c.y)){													/*Etape 3: Si la case n'est pas admissible on revient à l'étape 2, sinon en la convertie en case salle*/
			plateau->carte[c.y][c.x].type = ROOM;
			addadjacents(toexpand,&taille_toexpand,c.x,c.y,*plateau);						/*Etape 4: On ajoute les cases adjacentes dans toexpand*/
		}
		tour += 1;
	}																						/*Etape 5: Si toexpand n'estb pas vide on reprend à l'étape 2*/
	free(toexpand);

	init_nb_mur_addj(*plateau,nb_mur_addj);

	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){
			if(nb_mur_addj[i][j] == 1){														/*Etape 6: réduit les chemins de 1 qui sont inutiles*/
				plateau->carte[i][j].type = WALL;
			}
		}
	}
	plateau->carte[stair_up_y][stair_up_x].type = STAIR_UP;
}


void generation_tresor(Plateau *plateau, int x, int y, int etage){
    int objet;
    int potion;
    
    objet = rand() % 2;
    potion = 0;
    
    switch(objet){
        case 0:  																										/*On ajoute une potion*/
            potion = rand() % 5;
            switch(potion){
                case 0: plateau -> carte[x][y].entity.treasure.objet = init_object("soin","",0,0); break;
                case 1: plateau -> carte[x][y].entity.treasure.objet = init_object("magie","",0,0); break;
                case 2: plateau -> carte[x][y].entity.treasure.objet = init_object("régénération","",0,0); break;
                case 3: plateau -> carte[x][y].entity.treasure.objet = init_object("précision","",0,0) ; break;
                case 4: plateau -> carte[x][y].entity.treasure.objet = init_object("apprentissage","",0,0); break;
                default : break;
            }
            break;
        case 1: 																										/*On ajoute un équipement*/
            plateau -> carte[x][y].entity.treasure.objet.equipment.quality = rand() % 3;
            switch(plateau -> carte[x][y].entity.treasure.objet.equipment.quality){
                case 0: plateau -> carte[x][y].entity.treasure.objet = init_object("","Epée",1 + rand() % etage,1); break;
                case 1: plateau -> carte[x][y].entity.treasure.objet = init_object("","Bouclier",1 + rand() % etage,0); break;
                case 2: plateau -> carte[x][y].entity.treasure.objet = init_object("","Baguette magique",1 + rand() % etage,2); break;
                default : break;
            }
            break;
        default : break;
    }
    plateau -> carte[x][y].entity.treasure.type = objet;

    objet = rand() % 2;   
    switch(objet){
        case 0: 																										/*On ajoute une potion*/
            potion = rand() % 5;
            switch(potion){
                case 0: plateau -> carte[x][y].entity.treasure.objet2 = init_object("soin","",0,0); break;
                case 1: plateau -> carte[x][y].entity.treasure.objet2 = init_object("magie","",0,0); break;
                case 2: plateau -> carte[x][y].entity.treasure.objet2 = init_object("régénération","",0,0); break;
                case 3: plateau -> carte[x][y].entity.treasure.objet2 = init_object("précision","",0,0) ; break;
                case 4: plateau -> carte[x][y].entity.treasure.objet2 = init_object("apprentissage","",0,0); break;
                default : break;
            }
            break;
        case 1: 																										/*On ajoute un equipement*/
            plateau -> carte[x][y].entity.treasure.objet.equipment.quality = rand() % 3;
            switch(plateau -> carte[x][y].entity.treasure.objet.equipment.quality){
                case 0: plateau -> carte[x][y].entity.treasure.objet2 = init_object("","Epée",1 + rand() % etage,1); break;
                case 1: plateau -> carte[x][y].entity.treasure.objet2 = init_object("","Bouclier",1 + rand() % etage,0); break;
                case 2: plateau -> carte[x][y].entity.treasure.objet2 = init_object("","Baguette magique",1 + rand() % etage,2); break;
                default : break;
            }
            break;
        default : break;
    }
    plateau -> carte[x][y].entity.treasure.type2 = objet;
    plateau -> carte[x][y].entity.treasure.close = 1;
    plateau -> carte[x][y].type = TREASURE;
}

void generation_monstre(Plateau *plateau, int x, int y, int etage){
    plateau -> carte[x][y].entity.monster.Hp = 15 * etage + rand() % etage;
    plateau -> carte[x][y].entity.monster.Mp = etage;
    plateau -> carte[x][y].entity.monster.Atk = plateau -> carte[x][y].entity.monster.Hp / 2;
    plateau -> carte[x][y].entity.monster.Def = 0;
    plateau -> carte[x][y].entity.monster.Int = 0;
    plateau -> carte[x][y].entity.monster.Exp = 75 * etage + rand() % (etage + 5);
    plateau -> carte[x][y].entity.monster.Lv = 1 * etage + (rand() % etage) / 3;
    plateau -> carte[x][y].entity.monster.dir = SUD;

    
    plateau -> carte[x][y].type = MONSTER;
}

int generationentite(Plateau *plateau, int etage){
    int seuil_proba,proba;
    int i, j;
    
    proba = 0;
    seuil_proba = 10;

    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){
            if(plateau -> carte[i][j].type == ROOM && nb_room_distance_1(*plateau,j,i) == 1){				/*On cheche une case vide en bout de chemin pour mettre un trésor*/
                proba = rand() % 100;
                if(proba < 0){
                    return 0;
                }
                else if(proba >=0 && proba < seuil_proba){
                    generation_tresor(plateau, i, j, etage);
                    if(plateau -> carte[i - 1][j].type == ROOM){											/*On génere un monstre à côté du coffre*/
                    	generation_monstre(plateau, i-1, j, etage);
                    }else if(plateau -> carte[i + 1][j].type == ROOM){
                    	generation_monstre(plateau, i+1, j, etage);
                    }else if(plateau -> carte[i][j + 1].type == ROOM){
                    	generation_monstre(plateau, i, j+1, etage);
                    }else if(plateau -> carte[i][j - 1].type == ROOM){
                    	generation_monstre(plateau, i, j-1, etage);
                    }
                }
            }
            if(plateau -> carte[i][j].type == STAIR_UP){													/*On essait d'avoir au moins 1 coffre prêt du l'escalier montant*/
                if(plateau -> carte[i - 1][j].type != TREASURE && plateau -> carte[i + 1][j].type != TREASURE
                   && plateau -> carte[i][j -1].type != TREASURE && plateau -> carte[i][j + 1].type != TREASURE){
                    while(proba != -1){
                        proba = rand() % 4;
                    	if(proba == 0 && plateau -> carte[i - 1][j].type == ROOM){
                    		generation_tresor(plateau,i-1,j,etage);
                    		proba = -1;
                    	}else if(proba == 1 && plateau -> carte[i + 1][j].type == ROOM){
                    		generation_tresor(plateau,i+1,j,etage);
                    		proba = -1;
                    	}else if(proba == 2 && plateau -> carte[i][j -1].type == ROOM){
                    		generation_tresor(plateau,i,j-1,etage);
                    		proba = -1;
                    	}else if(proba == 3 && plateau -> carte[i][j + 1].type == ROOM){
                    		generation_tresor(plateau,i,j+1,etage);
                    		proba = -1;
                    	}
                    }
                }
            }
        }
    }
    
    return 1;
}

void generation_stair_down(Plateau *plateau, int *x, int *y, int etage){
	int rx,ry;
	rx = rand()%NB_COL;
	ry = rand()%NB_LIG;
	while(plateau -> carte[ry][rx].type != ROOM || distance_case(*plateau,rx,ry,NB_COL/2,NB_LIG/2) < 25){  /*On attend que la case trouvée soit une salle et assez loin de l'entrée de l'étage*/
		rx = rand()%NB_COL;
		ry = rand()%NB_LIG;
	}
	plateau -> carte[ry][rx].type = STAIR_DOWN;
	*x = rx;
	*y = ry;
	if(etage%5 == 0){
		if(plateau -> carte[ry - 1][rx].type == ROOM){											/*On génere un monstre à côté du coffre*/
        	generation_monstre(plateau, ry-1, rx, etage*5);
        }
        if(plateau -> carte[ry + 1][rx].type == ROOM){
        	generation_monstre(plateau, ry+1, rx, etage*5);
        }
        if(plateau -> carte[ry][rx + 1].type == ROOM){
        	generation_monstre(plateau, ry, rx+1, etage*5);
        }
        if(plateau -> carte[ry][rx - 1].type == ROOM){
        	generation_monstre(plateau, ry, rx-1, etage*5);
        }
	}
}

void m_a_j_monster_treasure(Plateau *plateau, Character *perso){
    int i, j;
    
    for(i=0; i<NB_LIG; i++){
        for(j=0; j<NB_COL; j++){
            if(plateau -> carte[i][j].type == MONSTER && plateau -> carte[i][j].entity.monster.Hp <= 0){ /*Les monstres morts (Hp <= 0) sont suppprimés*/
            	plateau -> carte[i][j].type = ROOM;
            	perso->Exp += plateau -> carte[i][j].entity.monster.Exp;
            }
            if(plateau -> carte[i][j].type == TREASURE && plateau -> carte[i][j].entity.treasure.close == 0){	/*Les trésors sont supprimés quand ils sont ouverts*/
            	plateau -> carte[i][j].type = ROOM;
            }
		}
	}
}
