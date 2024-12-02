#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include "Plateau.h"

#define LENGTH 13
#define WIDTH 9
#define CASE 75
#define CASE_M 5

/*
Structure Images
Stockant les textures utiles à l'affichage graphique
*/

typedef struct images
{
	MLV_Image * image_w;
	MLV_Image * image_g;
	MLV_Image * image_t;


	MLV_Image * image_u;
	MLV_Image * image_u_d;

	MLV_Image * image_k_s;
	MLV_Image * image_k_n;
	MLV_Image * image_k_e;
	MLV_Image * image_k_o;

	MLV_Image * image_m_s;
	MLV_Image * image_m_n;
	MLV_Image * image_m_e;
	MLV_Image * image_m_o;

	MLV_Image * image_b_s;
	MLV_Image * image_b_n;
	MLV_Image * image_b_e;
	MLV_Image * image_b_o;
}Images;

Images initwindowMLV();

int Menu_MLV();

void endwindowMLV(Images *textures);

void affichageterminal(Plateau plateau);

void affichageMLVMap(Plateau plateau, int x, int y);

void affichageMLV(Plateau plateau, Images texture, Character perso, int etage, Tour tour);
#endif