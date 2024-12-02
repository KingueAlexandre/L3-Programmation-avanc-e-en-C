#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include "../include/Jeu.h"

int tour_joueur_MLV(Plateau *plateau, Character *perso, int  preci, int  appr, int *etage, Inventaire *inv){
    int var_x,var_y;
	int mouse_x, mouse_y;
	MLV_Keyboard_button touche;
    MLV_Event event_type=MLV_NONE;

    if((*perso).dir == NORD){           			/*On initialise les variables avec le dernier clic*/   
        var_x = 0;
        var_y = -1;
    }else if((*perso).dir == SUD){      
        var_x = 0;
        var_y = +1;
    }else if((*perso).dir == EST){     
        var_x = 1;
        var_y = 0;
    }else if((*perso).dir == OUEST){      
        var_x = -1;
        var_y = 0;
    }
	event_type = MLV_wait_keyboard_or_mouse( &touche, NULL, NULL, &mouse_x, &mouse_y );				/*On attend le clic du joueur*/
	while(1){
		/*On agit en focntion de ce clic*/
        if(touche == MLV_KEYBOARD_UP){              /*Flèche du haut*/
            (*perso).dir = NORD;
            var_x = 0;
            var_y = -1;
        }else if(touche == MLV_KEYBOARD_DOWN){      /*Flèche du bas*/
            (*perso).dir = SUD;
            var_x = 0;
            var_y = +1;
        }else if(touche == MLV_KEYBOARD_RIGHT){     /*Flèche de droite*/
            (*perso).dir = EST;
            var_x = 1;
            var_y = 0;
        }else if(touche == MLV_KEYBOARD_LEFT){      /*Flèche de gauche*/
            (*perso).dir = OUEST;
            var_x = -1;
            var_y = 0;
        }
        if(event_type == MLV_KEY){
            if(touche == 'm'){          /*Touhe m : Attaque de magie*/
                if((*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == MONSTER){
                    magic_pl(perso, &(plateau->carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].entity.monster), preci);
                    break;
                }
            }else if(touche == 'c'){
            	affichageMLVMap(*plateau,(*perso).pos.x ,(*perso).pos.y);
            }else if(touche == MLV_KEYBOARD_UP || touche == MLV_KEYBOARD_DOWN || touche == MLV_KEYBOARD_RIGHT || touche == MLV_KEYBOARD_LEFT ){    				/*Déplacement du joueur*/
                if( (*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == ROOM){									/*Avancement sur une Case salle*/
                (*perso).pos.y += var_y;
                (*perso).pos.x += var_x;
                break;

                }else if((*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == MONSTER){							/*Attaque du perso sur un monstre*/
                    attack_pl(perso, &(plateau->carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].entity.monster), preci);
                    break;

                }else if((*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == TREASURE){						/*Tentative d'ouverture d'un coffre*/
                    if(2 + (*inv).nb_object < MAX_INV){
                        new_treasure(inv,perso,(*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].entity.treasure);
                        (*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].entity.treasure.close = 0;
                    }
                    break;

                }else if( (*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == STAIR_UP){						/*On descend d'un étage*/
                    (*perso).pos.y += var_y;
                    (*perso).pos.x += var_x;
                    if(*etage > 1){																				/*L'escalier montant du 1er étage ne mène nul part (on ne sort pas du donjon)*/
                        *etage-=1;
                        return 1;
                    }
                    return 0;

                }else if( (*plateau).carte[(*perso).pos.y + var_y][(*perso).pos.x + var_x].type == STAIR_DOWN){						/*On monte d'un étage*/
                    (*perso).pos.y += var_y;
                    (*perso).pos.x += var_x;
                    *etage+=1;
                    return 1;
                }
            }else{
                printf("touche présée : %c\n",touche);
            }
        }else if(event_type == MLV_MOUSE_BUTTON){																							  				/*Clic du joueur*/
            if( (LENGTH*CASE + CASE/3 <= mouse_x && mouse_x <= LENGTH*CASE + CASE/3 + CASE*2) && ((WIDTH-4)*CASE+CASE/3 <= mouse_y && mouse_y <= (WIDTH-4)*CASE+CASE/3 + CASE)){ /*Inventaire*/
                return 2;
            }else if( (LENGTH*CASE + CASE/3 <= mouse_x && mouse_x <= LENGTH*CASE + CASE/3 + CASE*2) && ((WIDTH-2)*CASE+CASE/3 <= mouse_y && mouse_y <= (WIDTH-2)*CASE+CASE/3 + CASE)){ /*Quitter*/
                return 3;
            }
        }
		event_type = MLV_wait_keyboard_or_mouse( &touche, NULL, NULL, &mouse_x, &mouse_y );				/*On attend le clic du joueur*/
	}
    return 0;
}

void tour_monster(Plateau *plateau, Character *perso){
    if((*plateau).carte[(*perso).pos.y][(*perso).pos.x - 1].type == MONSTER){							/*Le monstre est à 1 case du joueur*/

        plateau -> carte[(*perso).pos.y][(*perso).pos.x - 1].entity.monster.dir = EST;					/*Le monstre se tourne vers le joueur*/
        attack_ms(perso, &(plateau->carte[(*perso).pos.y][(*perso).pos.x - 1].entity.monster));			/*Le monstre attaque le joueur*/
    }

    if((*plateau).carte[(*perso).pos.y][(*perso).pos.x + 1].type == MONSTER){

        plateau -> carte[(*perso).pos.y][(*perso).pos.x + 1].entity.monster.dir = OUEST;
        attack_ms(perso, &(plateau->carte[(*perso).pos.y][(*perso).pos.x + 1].entity.monster));
    }

    if((*plateau).carte[(*perso).pos.y - 1][(*perso).pos.x].type == MONSTER){

        plateau -> carte[(*perso).pos.y - 1][(*perso).pos.x].entity.monster.dir = SUD;
        attack_ms(perso, &(plateau->carte[(*perso).pos.y - 1][(*perso).pos.x].entity.monster));
    }

    if((*plateau).carte[(*perso).pos.y + 1][(*perso).pos.x].type == MONSTER){

        plateau -> carte[(*perso).pos.y +1][(*perso).pos.x].entity.monster.dir = NORD;
        attack_ms(perso, &(plateau->carte[(*perso).pos.y + 1][(*perso).pos.x].entity.monster));
    }
}

void attack_pl(Character * player, Monster * monster, int preci){
    int triple;
    int attack;
    
    triple = rand() % 100;
    attack = 0;
    
    attack = (player-> Atk + (*player).equipment[1].status) * (80 + rand() % 41) / 100;
    if(triple < preci){
        attack *= 3;
    } 
    (monster -> Hp) -= attack;
}

void magic_pl(Character * player, Monster * monster, int preci){
    int triple;
    int attack;
    
    triple = rand() % 100;
    attack = 0;
    
    if((player -> Mp) >= 20){
        attack = 2 * (player -> Int + (*player).equipment[2].status) * (80 + rand() % 41) / 100;
        if(triple < preci){
            attack *= 3;
        }
        (monster -> Hp) -= attack;
        (player -> Mp) -= 20;
    }
}

void attack_ms(Character * player, Monster * monster){
    int triple;
    int attack;
    
    triple = rand() % 100;
    attack = 0;
    
    attack = (monster -> Atk) * (80 + rand() % 41) / 100;
    if(triple < 5){
        attack *= 3;
    } 
    (player -> Hp) -= attack;
}

Tour initTour(){
    Tour ret;
    ret.precision = 0;
    ret.regeneration = 0;
    ret.apprentissage = 0;
    return ret;
}

int verif_tour(Character * player, Tour * tour, int * preci, int * appr){
    if((tour -> regeneration) == 31){															/*Fin de l'effet de la potion de regénaration*/
        (tour -> regeneration) = 0;
    }
    else if((tour -> regeneration) > 0 && (tour -> regeneration) <= 30){						/*Début de l'effet de la potion de regénartion*/				
    	if((tour -> regeneration)%3 == 0){
	        (player -> Hp) += 20;
	        if(player->Hp >= player->Def*10){
	        	player->Hp = player->Def*10;
	        }
	        (player -> Mp) += 10;
	        if(player -> Mp >= player->Int*10 - 50){
	        	(player -> Mp) = player->Int*10 - 50;
	        }
	    }
        ++(tour -> regeneration);
    }
    
    if((tour -> precision) == 31){																/*Fin de l'effet de la potion de précision*/
        (tour -> precision) = 0;
        *preci = 5;
    }
    else if((tour -> precision) > 0 && (tour -> precision) <= 30){								/*Début de l'effet de la potion de précision*/
        ++(tour -> precision);
    }
    
    if((tour -> apprentissage) == 31){															/*Fin de l'effet de la potion d'apprentissage*/
        (tour -> apprentissage) = 0;
        *appr = 0;
    }
    else if((tour -> apprentissage) > 0 && (tour -> apprentissage) <= 30){						/*Début de l'effet de la potion d'apprentissage*/
        ++(tour -> apprentissage);
    }
    return 1;
}

void utilise_potion(Character * player, char * potion, Tour * tour, int * preci, int * appr){
    if(strcmp(potion, "soin") == 0){														/*Potion de soin*/
        (player -> Hp) += (player -> Def);
    }
    else if(strcmp(potion, "magie") == 0){													/*Potion de magie*/
        (player -> Mp) += (player -> Def) - 5;
    }
    else if(strcmp(potion, "régénération") == 0 && (tour -> regeneration) == 0){			/*Potion de régénération*/
        (player -> Hp) += 20;
        (player -> Mp) += 10;
        ++(tour -> regeneration);
    }
    else if(strcmp(potion, "précision") == 0 && (tour -> precision) == 0){					/*Potion de précision*/
        *preci = 15;
        ++(tour -> precision);
    }
    else if(strcmp(potion, "apprentissage") == 0 && (tour -> apprentissage) == 0){			/*Potion d'apprentissage*/
        *appr = 30;
        ++(tour -> apprentissage);
    }
}


void nouvelles_stats(Character * player){
	int stats,atk,def,int_, mouse_x,mouse_y;
	stats = 3;																						/*Le nombre d'augmentayion de stats restantes*/
	atk = 0;
	def = 0;
	int_ = 0;
	if(player->Exp >= 350+50*player->Lv){															/*Le joueur Lv up*/
		player->Exp -= 350+50*player->Lv;
		player->Lv+=1;
		MLV_draw_filled_rectangle( 4*CASE, 2*CASE, 6*CASE, 3*CASE, MLV_COLOR_BLACK );
		MLV_draw_filled_rectangle( 4*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_RED);
		MLV_draw_filled_rectangle( 6*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_GREEN);
		MLV_draw_filled_rectangle( 8*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_BLUE);

		MLV_draw_text(7*CASE, 2*CASE+CASE/2, "STATS!", MLV_COLOR_WHITE);
		MLV_draw_text(4*CASE+CASE/2, 3*CASE+CASE*2/3, "ATK! +%d", MLV_COLOR_WHITE,atk);
		MLV_draw_text(6*CASE+CASE/2, 3*CASE+CASE*2/3, "DEF! +%d", MLV_COLOR_WHITE,def);
		MLV_draw_text(8*CASE+CASE/2, 3*CASE+CASE*2/3, "INT! +%d", MLV_COLOR_WHITE,int_);

		MLV_actualise_window();

		while(stats>0){
			MLV_wait_mouse(&mouse_x, &mouse_y);
			if((4*CASE <= mouse_x && mouse_x <= 6*CASE) && (3*CASE <= mouse_y && mouse_y <= 5*CASE) ){					/*Atk+ choisi*/
				atk+=1;
				stats--;
			}else if((6*CASE <= mouse_x && mouse_x <= 8*CASE) && (3*CASE <= mouse_y && mouse_y <= 5*CASE) ){			/*Def+ choisi*/
				def+=1;
				stats--;
			}else if((8*CASE <= mouse_x && mouse_x <= 10*CASE) && (3*CASE <= mouse_y && mouse_y <= 5*CASE) ){			/*Int+ choisi*/
				int_+=1;
				stats--;
			}
			MLV_draw_filled_rectangle( 4*CASE, 2*CASE, 6*CASE, 3*CASE, MLV_COLOR_BLACK );
			MLV_draw_filled_rectangle( 4*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_RED);
			MLV_draw_filled_rectangle( 6*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_GREEN);
			MLV_draw_filled_rectangle( 8*CASE, 3*CASE, 2*CASE, 2*CASE, MLV_COLOR_BLUE);

			MLV_draw_text(7*CASE, 2*CASE+CASE/2, "STATS!", MLV_COLOR_WHITE);
			MLV_draw_text(4*CASE+CASE/2, 3*CASE+CASE*2/3, "ATK! +%d", MLV_COLOR_WHITE,atk);
			MLV_draw_text(6*CASE+CASE/2, 3*CASE+CASE*2/3, "DEF! +%d", MLV_COLOR_WHITE,def);
			MLV_draw_text(8*CASE+CASE/2, 3*CASE+CASE*2/3, "INT! +%d", MLV_COLOR_WHITE,int_);

			MLV_actualise_window();
		}
        player->Atk+=atk;																								/*On met à jour les stats*/
        player->Def+=def;
        player->Int+=int_;

        player->Hp += def*10;																							/*Les Hp et Mp sont légérement augmentés grâce aux nouvelles stats*/
       	player->Mp += (int_*10)/2;

	}
}


void InventaireMLV(Inventaire *inv, Character *perso, Tour *tour, int *preci, int *appr){
    int i,ind,fonct,end;
    int mouse_x, mouse_y;

    MLV_draw_filled_rectangle((LENGTH-4)*CASE,4*CASE,4*CASE,5*CASE,MLV_COLOR_WHITE);
    MLV_draw_filled_rectangle((LENGTH-4)*CASE+10,4*CASE+10,4*CASE-20,5*CASE-20,MLV_COLOR_BLACK);
    MLV_draw_text((LENGTH-4)*CASE + CASE*3/2, 4*CASE+10+CASE/2, "Potions",MLV_COLOR_WHITE);
            

    for (i = 0; i < (*inv).nb_object; ++i){
        MLV_draw_text((LENGTH-4)*CASE + 10 + CASE/2, 4*CASE+10+CASE/2 + (CASE*(i+1))/3, "%s",MLV_COLOR_WHITE,(*inv).inventaire[i].potion);

        MLV_draw_filled_rectangle((LENGTH)*CASE -30, 4*CASE+10+CASE/2  + (CASE*(i+1))/3,15,15,MLV_COLOR_RED);
        MLV_draw_filled_rectangle((LENGTH)*CASE -50, 4*CASE+10+CASE/2  + (CASE*(i+1))/3,15,15,MLV_COLOR_GREEN);
    }
    MLV_actualise_window();
    end = 1;
    
    while(end){
        MLV_wait_mouse(&mouse_x, &mouse_y );  /*On attend le clic du joueur*/
        if( ( mouse_x <= (LENGTH-4)*CASE || (LENGTH-4)*CASE + 4*CASE <= mouse_x) || (mouse_y <= 4*CASE  || 9*CASE <= mouse_y) ){					/*Un clic en dehors de l'inventaire on quitte l'inventaire*/
            ind  = -1;
            fonct = -1;
            end = 0;
            continue;
        }
        for (i = 0; i < (*inv).nb_object; ++i){
            if( ((LENGTH)*CASE - 30 <= mouse_x && mouse_x <= ((LENGTH)*CASE - 15)) && (4*CASE+10+CASE/2  + (CASE*(i+1))/3 <= mouse_y && mouse_y <= 4*CASE+10+CASE/2  + (CASE*(i+1))/3 +15) ){		/*Un clic dans un bouton rouge on supprime une potion de l'inventaire*/
                ind  = i;
                fonct = 1;
                end = 0;
                break;
            }
            if( ((LENGTH)*CASE - 50 <= mouse_x && mouse_x <= ((LENGTH)*CASE - 25)) && (4*CASE+10+CASE/2  + (CASE*(i+1))/3 <= mouse_y && mouse_y <= 4*CASE+10+CASE/2  + (CASE*(i+1))/3 +15) ){		/*Un clic dans un bouton rouge on boit une potion de l'inventaire*/
                ind  = i;
                fonct = 2;
                end = 0;
                break;
            }
        }
    }
    if(fonct != -1){
        if(fonct == 2){
            utilise_potion(perso,(*inv).inventaire[ind].potion,tour,preci,appr);																	/*La potion est bu*/
        }
        delete_element(inv, ind);																													/*La potion est supprimé*/
    }
    printf("potion n°%d et fonct %d\n",ind,fonct);
}