#ifndef __JEU__
#define __JEU__

#include "Graphique.h"

/*FONCTION DETECTANT LA FIN DU JEU.
Renvoie 0 quand le jeu n'est pas terminé et 1 sinon*/
int FindujeuPlateau(Plateau P);

/*FONCTION DE DEPLACEMENT DE LA CASE NOIR (TOUR) DU JEU.
Effectue les déplacements de la case noir en focntion des choix du joueur*/
void TourPlateau(Plateau *P, int *case_nx, int *case_ny);

#endif
