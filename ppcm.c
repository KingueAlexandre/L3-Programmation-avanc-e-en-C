#include <stdio.h>
#include <stdlib.h>

int ppcm_trouve(int *tab, int taille){
	int i;
	for(i=0;i<taille;i++){
		if(tab[i] != 1){
			return 0;
		}
	}
	return 1;
}

void affiche_tab(int n, int *tab){
	int i;
	printf("%d		:",n);
	for(i=0; i<n; i++){
		printf("%d ",tab[i]);
	}
	printf("FIN\n");
	return ;
}

int main(int argc, char const * argv[]){
	
	int i,nb,ppcm;
	int m_ppcm,cmpt_ppcm;
	int *tab;

	nb = argc-1;
	tab=(int *)malloc(sizeof(int)*nb);
	ppcm = 1;
	m_ppcm = 1;
	cmpt_ppcm = 0;
	
	for(i=0;i<nb;i++){
		tab[i]=atoi(argv[i+1]);		
	}
	affiche_tab(nb,tab);

	if(nb == 1){
		printf("%d\n",tab[0]);		
		
	}else if(nb == 0){
		printf("1\n");
	}else{
		while(ppcm_trouve(tab,nb) == 0){
			affiche_tab(nb,tab);
			for(i=0;i<nb;i++){
				if(tab[i]%m_ppcm == 0 && m_ppcm != 1){
					tab[i]/=m_ppcm;
					cmpt_ppcm = 1;
				}
			}
			if(cmpt_ppcm == 1){
				ppcm*=m_ppcm;
			}else{
				m_ppcm+=1;
			}
			cmpt_ppcm = 0;
			
		}
		printf("%d\n",ppcm);
	}

	return 0;
}
