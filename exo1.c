#include <stdio.h>
#include <stdlib.h>

int puissance(int a, int b){
	if(b == 0){
		return 1;
	}else if(b < 0){
		return -1;
	}
	return a*puissance(a,b-1);
}

int main(int argc, char const * argv[]){

	int i,x,y,z;

	for(i=0; i<500; i++){
		if(i<10){
			x = puissance(i,3);
			if(i == x){
				printf("%d = %d³ = %d\n",i,i,x );
			}
		}else if(i<100){
			x = puissance(i/10,3);
			y = puissance(i%10,3);
			if(i == x + y){
				printf("%d = %d³ + %d³ = %d + %d\n",i,i/10,i%10,x,y );
			}
		}else{
			x = puissance(i/100,3);
			y = puissance((i/10)%10,3);
			z = puissance(i%10,3);
			if(i == x + y + z){
				printf("%d = %d³ + %d³ + %d³ = %d + %d + %d\n",i,i/100,(i/10)%10,i%10,x,y,z );
			}
		}


	}

	return 0;
}