#ifndef __ELEMENTS__
#define __ELEMENTS__

#define NB_COL 63
#define NB_LIG 43

#define MAX_INV 12

/*
Structure Case
Simulant une case.
*/
typedef struct Case{
    int x;
    int y;
}Case;

/*
Enum Direction
Représentant une direction.
*/
typedef enum{
    NORD,
    SUD,
    EST,
    OUEST
}Direction;

/*
Enum Celltype
Représnetant un type de case.
*/
typedef enum {
    WALL, 
    ROOM, 
    MONSTER, 
    TREASURE,
    STAIR_UP, 
    STAIR_DOWN
}Celltype;

/*
Enum Quamilty
Représantant un type de boost de stats.
*/
typedef enum{
    DEF,
    ATK,
    INT
}Quality;

/*
Structure Equipement
Simulant les tours restant des différent effets des potions.
*/
typedef struct{
    char * name;
    Quality quality;
    int status;
}Equipement;

/*
Union Object
Union pouvant être une potion ou un équipement.
*/
typedef union objet{
    char * potion;
    Equipement equipment;
}Object;

/*
Structure Treasure
Représantant un trésor.
*/
typedef struct{
    Object objet;
    int type;
    Object objet2;
    int type2;
    int close;
}Treasure;

/*
Structure Character
Simaulant un joueur au cours du jeu.
*/
typedef struct{
    int Hp;
    int Mp;
    int Atk;
    int Int;
    int Def;
    int Exp;
    int Lv;
    Case pos;
    Direction dir;
    Equipement equipment[3];
}Character, Monster;

/*
Union Entity
Union pouvant être soit un monstre soit un trésor.
Stocké dans les cellules du tableau de la structure Plateau.
*/
typedef union entity{
    Monster monster;
    Treasure treasure;
}Entity;

/*
Structure Inventaire
Simulant l'inventaire ou sont stockés les potions.
*/
typedef struct inventaire{
    Object inventaire[MAX_INV];
    int nb_object;
}Inventaire;

/*Fonction Initilisant l'inventaire*/
void initInventaire(Inventaire *Inv);

/*Fonction initialisant un Equipement*/
Equipement init_equip(char *s, int status, Quality quality);

/*Fonction initialisant un Object*/
Object init_object(char *potion, char *name, int status, Quality quality);

/*Fonction initialisant un Character*/
Character initPerso();

/*Fonction ajoutant un nouvelle équipement (ou pas) pour le Character perso*/
void new_equipement(Character *perso, Equipement equipment);

/*Fonction ajoutant le contenu d'un trésor d'un l'inventaire ou dans l'équipement du Character perso*/
void new_treasure(Inventaire *stock, Character *perso, Treasure treasure);

/*Fonction supprimant un élément de l'inventaire à l'indice ind*/
void delete_element(Inventaire *stock, int ind);

#endif
