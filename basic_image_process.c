/* Basic image process */

#include <stdio.h>
#include <stdlib.h>

#define IMAGE_SIZE 512
#define IMAGE_SIZE_X IMAGE_SIZE
#define IMAGE_SIZE_Y IMAGE_SIZE
#define PIXEL_SIZEOF 4

/* 600 fois plus rapide que sa version en python... */
void invert_color(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
  int i, j;

  for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
    for (j=0 ; j<IMAGE_SIZE_X ; ++j){
      bitmap[i][j][0] = 255 - bitmap[i][j][0]; /* red */
      bitmap[i][j][1] = 255 - bitmap[i][j][1]; /* green */
      bitmap[i][j][2] = 255 - bitmap[i][j][2]; /* blue */
    }
  }
}

void niveaux_de_gris_moy(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	 int i, j, value;

	for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	    	value = (bitmap[i][j][0] + bitmap[i][j][1] + bitmap[i][j][2])/3;
	      	bitmap[i][j][0] = value;
	      	bitmap[i][j][1] = value;
	      	bitmap[i][j][2] = value;
	    }
	}
}

int mini_max(unsigned char * tab){
	if(tab[0]>=tab[1] && tab[0]>tab[2]){
		return tab[0];
	}else if(tab[1]>=tab[0] && tab[1]>tab[2]){
		return tab[1];
	}
	return tab[2];
}

float mini_mini(unsigned char * tab){
	if(tab[0]<=tab[1] && tab[0]<tab[2]){
		return tab[0];
	}else if(tab[1]<=tab[0] && tab[1]<tab[2]){
		return tab[1];
	}
	return tab[2];
}

void niveaux_de_gris_clarte(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	 int i, j, value;

	for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	    	value = (mini_max(bitmap[i][j]) + mini_mini(bitmap[i][j]) )/2;
	      	bitmap[i][j][0] = value;
	      	bitmap[i][j][1] = value;
	      	bitmap[i][j][2] = value;
	    }
	}
}

void niveaux_de_gris_luminance(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
 	int i, j, value;

	for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	    	value = bitmap[i][j][0]*0.2126 + bitmap[i][j][1]*0.7152 + bitmap[i][j][2]*0.0722;
	      	bitmap[i][j][0] = value;
	      	bitmap[i][j][1] = value;
	      	bitmap[i][j][2] = value;
	    }
	}
}


void seuillage_noir_blanc(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	int i,j;

    niveaux_de_gris_luminance(bitmap);

    for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
            if (bitmap[i][j][0]*1.0 > 127.5){
                bitmap[i][j][0] = 255;
               	bitmap[i][j][1] = 255;
                bitmap[i][j][2] = 255;
            }else{
                bitmap[i][j][0] = 0;
                bitmap[i][j][1] = 0;
                bitmap[i][j][2] = 0;
            }
        }
    }

}
 

void plus_rouge(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	int i, j;

	for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	      	bitmap[i][j][0] = (bitmap[i][j][0]+255)/2;
	    }
	}
}

void tres_vert(unsigned char bitmap[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	int i, j;

	for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	      	bitmap[i][j][1] = (255*3+bitmap[i][j][1])/4;
	    }
	}
}


unsigned char*** degrade(){
	int i, j;

	unsigned char*** img;

  img = (unsigned char ***) malloc(sizeof(unsigned char**)*IMAGE_SIZE_Y);
  for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
  	img[i] = (unsigned char **) malloc(sizeof(unsigned char*)*IMAGE_SIZE_X);
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	      	img[i][j] = (unsigned char *) malloc(sizeof(unsigned char)*PIXEL_SIZEOF);
	        img[i][j][0] = 1-(i+j)/1024;
	      	img[i][j][1] = (i+j)/1024;
	      	img[i][j][2] = 0;
	      	img[i][j][3] = 255;
	    }
	}
	return img;
}

unsigned char*** moyenne(unsigned char img1[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF], unsigned char img2[IMAGE_SIZE_Y][IMAGE_SIZE_X][PIXEL_SIZEOF]){
	int i, j, k;
  unsigned char*** img;

  img = (unsigned char ***) malloc(sizeof(unsigned char**)*IMAGE_SIZE_Y);
  for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
  	img[i] = (unsigned char **) malloc(sizeof(unsigned char*)*IMAGE_SIZE_X);
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
	      	img[i][j] = (unsigned char *) malloc(sizeof(unsigned char)*PIXEL_SIZEOF);
	        img[i][j][0] = 0;
          img[i][j][1] = 0;
          img[i][j][2] = 0;
	      	img[i][j][3] = 255;
	    }
	}

  for (i=0 ; i<IMAGE_SIZE_Y ; ++i){
		for (j=0 ; j<IMAGE_SIZE_X ; ++j){
			for (k=0 ; k<3 ; ++k){
                img[i][j][k] = (img1[i][j][k] + img2[i][j][k])/2;
            }
        }
    }
  return img;
}