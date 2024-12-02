#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

#include "../include/Graphique.h"

Images initwindowMLV(){
	Images ret;
	MLV_create_window("Donjon", "RogueLike",LENGTH*CASE + 200,WIDTH*CASE);

	ret.image_w = MLV_load_image("./Texture/wall3.jpeg");
	ret.image_g = MLV_load_image("./Texture/ground2.jpeg");
	ret.image_t = MLV_load_image("./Texture/treasure.png");

	ret.image_u = MLV_load_image("./Texture/stairs.png");
	ret.image_u_d = MLV_load_image("./Texture/stairsdown.png");

	ret.image_k_s = MLV_load_image("./Texture/Sud.png");
	ret.image_k_n = MLV_load_image("./Texture/Nord.png");
	ret.image_k_e = MLV_load_image("./Texture/Est.png");
	ret.image_k_o = MLV_load_image("./Texture/Ouest.png");

	ret.image_m_s = MLV_load_image("./Texture/SudM.png");
	ret.image_m_n = MLV_load_image("./Texture/NordM.png");
	ret.image_m_e = MLV_load_image("./Texture/EstM.png");
	ret.image_m_o = MLV_load_image("./Texture/OuestM.png");

	ret.image_b_s = MLV_load_image("./Texture/BossDragonSud.png");
	ret.image_b_n = MLV_load_image("./Texture/BossDragonNord.png");
	ret.image_b_e = MLV_load_image("./Texture/BossDragonEst.png");
	ret.image_b_o = MLV_load_image("./Texture/BossDragonOuest.png");

	MLV_resize_image_with_proportions( ret.image_w, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_g, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_t, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_u, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_u_d, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_k_s, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_k_n, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_k_o, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_k_e, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_m_s, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_m_n, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_m_o, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_m_e, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_b_s, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_b_n, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_b_o, CASE, CASE);
	MLV_resize_image_with_proportions( ret.image_b_e, CASE, CASE);

	return ret;
}

int Menu_MLV(){
	int  mouse_x, mouse_y;
	MLV_draw_filled_rectangle( (LENGTH*CASE + 200)/3, (WIDTH*CASE)*3/5, (LENGTH*CASE + 200)/3, (WIDTH*CASE)/5, MLV_COLOR_WHITE );
	MLV_draw_adapted_text_box(
		(LENGTH*CASE + 200)*2/5,(LENGTH*CASE)/5,
		"\n\n                 DONJON!                     \n\n",
		9,
		MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_COLOR_YELLOW,
		MLV_TEXT_CENTER
	);
	MLV_draw_text(((LENGTH*CASE + 200)/2) - CASE, ((WIDTH*CASE)*7/10), "  NOUVELLE PARTIE!", MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle( 0, 0, 100, 100, MLV_COLOR_WHITE );

	MLV_actualise_window();

	MLV_wait_mouse(&mouse_x, &mouse_y );

	while(1){
		if( (mouse_x >= (LENGTH*CASE + 200)/3 && mouse_x <= (LENGTH*CASE + 200)*2/3) && (mouse_y >= (WIDTH*CASE)*3/5 && mouse_y <= (WIDTH*CASE)*4/5) ){			/*Nouvelle partie*/
			return 1;
		}else if( (mouse_x >= 0 && mouse_x <= 100) && (mouse_y >= 0 && mouse_y <= 100) ){																		/*Sauvegarde*/
			return 0;
		}
		MLV_wait_mouse(&mouse_x, &mouse_y );
	}

}

void endwindowMLV(Images *textures){

	MLV_free_image( textures->image_u );
	MLV_free_image( textures->image_u_d );
	MLV_free_image( textures->image_g );
	MLV_free_image( textures->image_t );
	MLV_free_image( textures->image_w );
	MLV_free_image( textures->image_k_s );
	MLV_free_image( textures->image_k_n );
	MLV_free_image( textures->image_k_o );
	MLV_free_image( textures->image_k_e );
	MLV_free_image( textures->image_m_s );
	MLV_free_image( textures->image_m_n );
	MLV_free_image( textures->image_m_o );
	MLV_free_image( textures->image_m_e );
	MLV_free_image( textures->image_b_s );
	MLV_free_image( textures->image_b_n );
	MLV_free_image( textures->image_b_o );
	MLV_free_image( textures->image_b_e );

	textures = NULL;
	MLV_free_window();

}

void affichageterminal(Plateau plateau){
	int i,j;
	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){
			if(plateau.carte[i][j].type == WALL){
				printf("#");
			}else if(plateau.carte[i][j].type == STAIR_UP){
				printf("X");
			}else if(plateau.carte[i][j].type == MONSTER){
				printf("M");
			}else if(plateau.carte[i][j].type == TREASURE){
				printf("T");
			}else if(plateau.carte[i][j].type == ROOM){
				printf(" ");
			}else{
				printf("?");
			}
		}
		printf("\n");
	}
}

void affichageMLVMap(Plateau plateau, int x, int y){
	int i,j;
	MLV_draw_filled_rectangle( 0, 0, NB_COL*CASE_M, NB_LIG*CASE_M, MLV_COLOR_BLACK );
	for(i=0; i<NB_LIG; i++){
		for(j=0; j<NB_COL; j++){
			if(plateau.carte[i][j].type == WALL){
				MLV_draw_filled_rectangle( j*CASE_M, i*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_BLACK );
			}else if(plateau.carte[i][j].type == STAIR_UP){
				MLV_draw_filled_rectangle( j*CASE_M, i*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_BLUE );
			}else if(plateau.carte[i][j].type == TREASURE){
				MLV_draw_filled_rectangle( j*CASE_M, i*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_YELLOW );
			}else if(plateau.carte[i][j].type == STAIR_DOWN){
				MLV_draw_filled_rectangle( j*CASE_M, i*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_PURPLE );
			}else{
				MLV_draw_filled_rectangle( j*CASE_M, i*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_WHITE );
			}
		}
	}
	MLV_draw_filled_rectangle( x*CASE_M, y*CASE_M, CASE_M-1, CASE_M-1, MLV_COLOR_RED );

	MLV_actualise_window();

}

void affichageMLV(Plateau plateau, Images texture, Character perso, int etage, Tour tour){
	int i,j;
	
	MLV_draw_filled_rectangle(0,0,LENGTH*CASE + 200,LENGTH*CASE,MLV_COLOR_BLACK);			

	for(i=perso.pos.y-WIDTH/2; i<(perso.pos.y+WIDTH/2)+1; i++){

		for(j=perso.pos.x-LENGTH/2; j<(perso.pos.x+LENGTH/2)+1; j++){

			if( (0<=j && j<=NB_COL-1) && (0<=i && i<=NB_LIG-1)){

				if(plateau.carte[i][j].type == WALL){
					MLV_draw_image( texture.image_w, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );

				}else if(plateau.carte[i][j].type == ROOM){
					MLV_draw_image( texture.image_g, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );

				}else if(plateau.carte[i][j].type == STAIR_UP){
					MLV_draw_image( texture.image_g, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
					MLV_draw_image( texture.image_u, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );

				}else if(plateau.carte[i][j].type == STAIR_DOWN){
					MLV_draw_image( texture.image_u_d, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );

				}else if(plateau.carte[i][j].type == MONSTER){
					MLV_draw_image( texture.image_g, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
					if(plateau.carte[i][j].entity.monster.dir == SUD && plateau.carte[i][j].entity.monster.Mp > etage ){
						MLV_draw_image( texture.image_b_s,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}else if(plateau.carte[i][j].entity.monster.dir  == NORD && plateau.carte[i][j].entity.monster.Mp > etage ){
						MLV_draw_image( texture.image_b_n,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
					}else if(plateau.carte[i][j].entity.monster.dir  == EST && plateau.carte[i][j].entity.monster.Mp > etage ){
						MLV_draw_image( texture.image_b_e,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}else if(plateau.carte[i][j].entity.monster.dir  == OUEST && plateau.carte[i][j].entity.monster.Mp > etage ){
						MLV_draw_image( texture.image_b_o,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}else if(plateau.carte[i][j].entity.monster.dir == SUD){
						MLV_draw_image( texture.image_m_s,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}else if(plateau.carte[i][j].entity.monster.dir  == NORD){
						MLV_draw_image( texture.image_m_n,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
					}else if(plateau.carte[i][j].entity.monster.dir  == EST){
						MLV_draw_image( texture.image_m_e,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}else if(plateau.carte[i][j].entity.monster.dir  == OUEST){
						MLV_draw_image( texture.image_m_o,(j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE);
					}
					MLV_draw_text((j-(perso.pos.x-LENGTH/2))*CASE+10, (i-(perso.pos.y-WIDTH/2))*CASE+10, "Hp : %d",MLV_COLOR_RED,plateau.carte[i][j].entity.monster.Hp);

				}else if(plateau.carte[i][j].type == TREASURE){
					MLV_draw_image( texture.image_g, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
					MLV_draw_image( texture.image_t, (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE );
				}else{
					MLV_draw_filled_rectangle( (j-(perso.pos.x-LENGTH/2))*CASE, (i-(perso.pos.y-WIDTH/2))*CASE, CASE, CASE, MLV_COLOR_RED );
				}
			}
		}
	}
	/*MLV_draw_filled_rectangle( (perso.pos.x-(perso.pos.x-LENGTH/2))*CASE, (perso.pos.y-(perso.pos.y-WIDTH/2))*CASE, CASE, CASE, MLV_COLOR_WHITE );*/
	if(perso.dir == SUD){
		MLV_draw_image( texture.image_k_s, (perso.pos.x-(perso.pos.x-LENGTH/2))*CASE, (perso.pos.y-(perso.pos.y-WIDTH/2))*CASE );
	}else if(perso.dir == NORD){
		MLV_draw_image( texture.image_k_n, (perso.pos.x-(perso.pos.x-LENGTH/2))*CASE, (perso.pos.y-(perso.pos.y-WIDTH/2))*CASE );
	}else if(perso.dir == EST){
		MLV_draw_image( texture.image_k_e, (perso.pos.x-(perso.pos.x-LENGTH/2))*CASE, (perso.pos.y-(perso.pos.y-WIDTH/2))*CASE );
	}else if(perso.dir == OUEST){
		MLV_draw_image( texture.image_k_o, (perso.pos.x-(perso.pos.x-LENGTH/2))*CASE, (perso.pos.y-(perso.pos.y-WIDTH/2))*CASE );
	}

	MLV_draw_text(LENGTH*CASE + 50, 20, "Player:",MLV_COLOR_WHITE);
	MLV_draw_text(LENGTH*CASE + 10, 40, "Hp : %d",MLV_COLOR_WHITE,perso.Hp);
	MLV_draw_text(LENGTH*CASE + 10, 60, "Mp : %d",MLV_COLOR_WHITE,perso.Mp);
	MLV_draw_text(LENGTH*CASE + 50, 80, "Exp : %d",MLV_COLOR_WHITE,perso.Exp);
	MLV_draw_text(LENGTH*CASE + 50, 100, "Lv : %d",MLV_COLOR_WHITE,perso.Lv);
	i = (100.0*perso.Hp)/(perso.Def*10.0);
	if(i >75){
		MLV_draw_filled_rectangle( LENGTH*CASE + 70, 40, i, 12, MLV_COLOR_GREEN );
	}else if(25 <= i && i <= 75){
		MLV_draw_filled_rectangle( LENGTH*CASE + 70, 40, i, 12, MLV_COLOR_ORANGE );
	}else{
		MLV_draw_filled_rectangle( LENGTH*CASE + 70, 40, i, 12, MLV_COLOR_RED );
	}
	MLV_draw_filled_rectangle( LENGTH*CASE + 70, 60, (100*perso.Mp)/(perso.Int*10-50), 12, MLV_COLOR_BLUE );

	MLV_draw_text(LENGTH*CASE + CASE/3, (WIDTH-4)*CASE+CASE*5/3, "M : Magie   C : Carte",MLV_COLOR_WHITE);
	if(tour.apprentissage != 0){
		MLV_draw_text(LENGTH*CASE + 20, 320, "Bonus apprentissage : %d",MLV_COLOR_GREEN,30-tour.apprentissage);
	}
	if(tour.regeneration != 0){
		MLV_draw_text(LENGTH*CASE + 20, 340, "Bonus regeneration  : %d",MLV_COLOR_GREEN,30-tour.regeneration);

	}
	if(tour.precision != 0){
		MLV_draw_text(LENGTH*CASE + 20, 360, "Bonus precision     : %d",MLV_COLOR_GREEN,30-tour.precision);
	}

	MLV_draw_text(LENGTH*CASE + 55, 220, "Stats:",MLV_COLOR_WHITE);
	MLV_draw_text(LENGTH*CASE + 50, 240, "Atk : %d",MLV_COLOR_WHITE,perso.Atk);
	MLV_draw_text(LENGTH*CASE + 50, 260, "Int : %d",MLV_COLOR_WHITE,perso.Int);
	MLV_draw_text(LENGTH*CASE + 50, 280, "Def : %d",MLV_COLOR_WHITE,perso.Def);
	MLV_draw_text(LENGTH*CASE + 100, 240, " +%d",MLV_COLOR_YELLOW,perso.equipment[1].status);
	MLV_draw_text(LENGTH*CASE + 100, 260, " +%d",MLV_COLOR_YELLOW,perso.equipment[2].status);
	MLV_draw_text(LENGTH*CASE + 100, 280, " +%d",MLV_COLOR_YELLOW,perso.equipment[0].status);

	MLV_draw_filled_rectangle( LENGTH*CASE + CASE/3, (WIDTH-4)*CASE+CASE/3, CASE*2, CASE, MLV_COLOR_RED );
	MLV_draw_text(LENGTH*CASE + CASE*5/6, (WIDTH-4)*CASE+CASE*5/7, "Inventaire",MLV_COLOR_WHITE);

	MLV_draw_filled_rectangle( (LENGTH*CASE + CASE/3)-10, ((WIDTH-2)*CASE+CASE/3)-10, CASE*2+20, CASE+20, MLV_COLOR_WHITE );
	MLV_draw_filled_rectangle( LENGTH*CASE + CASE/3, (WIDTH-2)*CASE+CASE/3, CASE*2, CASE, MLV_COLOR_BLACK );
	MLV_draw_text(LENGTH*CASE + CASE, (WIDTH-2)*CASE+CASE*5/7, "Quitter",MLV_COLOR_WHITE);

	MLV_actualise_window();
}


