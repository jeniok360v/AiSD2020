#include <stdlib.h>
#include <stdio.h>

int main(){

	for(int i=0;i<1000;i++){
		printf("insert %i %i\n", rand()%1000, rand()%100);
	}

	return 0;
}