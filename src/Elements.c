#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Elements.h"

void initInventaire(Inventaire *Inv){
	int i;
	for (i = 0; i < MAX_INV; ++i)	{
		(*Inv).inventaire[i].potion = (char *) malloc( 20*sizeof(char) );
	}
	(*Inv).nb_object = 0;
}

Equipement init_equip(char *s, int status, Quality quality){
	Equipement ret;
	ret.name = (char *) malloc( 20*sizeof(char) );
	strcpy(ret.name,s);
	ret.quality = quality;
	ret.status = status;
	return ret;
}

Object init_object(char *potion, char *name, int status, Quality quality){
	Object ret;
	ret.potion = malloc(20*sizeof(char));
	ret.potion[0] = '\0';
	if( strlen(potion) != 0){											/*C'est une potion*/
		strcpy(ret.potion,potion);
	}else{																/*C'est de l'équipement*/
		ret.equipment = init_equip(name,status,quality);
	}
	printf("\n");
	return ret;
}

Character initPerso(){
	int i;
	char *s;
	Character ret;
	s = (char *) malloc( 20*sizeof(char) );
	ret.Atk = 10;
	ret.Def = 10;
	ret.Int = 10;
	ret.Lv = 1;
	ret.Exp = 0;
	ret.Hp = 100;
	ret.Mp = 50;
	ret.pos.x =NB_COL/2;
	ret.pos.y =NB_LIG/2;
	ret.dir = SUD;
	for (i = 0; i < 3; ++i){
		printf("%d\n",i );
		s[0] = '\0';
		if(i==0){
			strcpy(s,"Bouclier");
		}else if(i == 1){
			strcpy(s,"Epée");
		}else{
			strcpy(s,"Baguette magique");
		}
		printf("		%d%d\n",i ,i);
		ret.equipment[i] = init_equip(s, 0, i);
	}
	return ret;
}

void new_equipement(Character *perso, Equipement equipment){
	if( (*perso).equipment[equipment.quality].status < equipment.status){						/*On garde que s'il y a un intérêt*/
		(*perso).equipment[equipment.quality].status = equipment.status;
	}
}

void new_treasure(Inventaire *stock, Character *perso, Treasure treasure){
	if(treasure.type == 0){																		/*1er object: C'est une potion*/
		strcpy((*stock).inventaire[(*stock).nb_object].potion,treasure.objet.potion);
		(*stock).nb_object++;
		printf("%s => p\n",treasure.objet.potion);
	}else{																						/*1er object: C'est de l'équipement*/
		new_equipement(perso, treasure.objet.equipment);
		printf("%s => e\n",treasure.objet.equipment.name);
	}
	if(treasure.type2 == 0){																	/*2eme object: C'est une potion*/
		strcpy((*stock).inventaire[(*stock).nb_object].potion,treasure.objet2.potion);
		(*stock).nb_object++;
		printf("%s => p\n",treasure.objet2.potion);
	}else{																						/*2eme object: C'est de l'équipement*/
        new_equipement(perso, treasure.objet2.equipment);
		printf("%s => e\n",treasure.objet2.equipment.name);
	}
}

void delete_element(Inventaire *stock, int ind){
	int i;
	Object tmp;
	for (i = 0; i < (*stock).nb_object-1; ++i){
		if(i>=ind){
			tmp = (*stock).inventaire[i];
			(*stock).inventaire[i] = (*stock).inventaire[i+1];
			(*stock).inventaire[i+1] = tmp;
		}
	}
	(*stock).nb_object-=1;
}