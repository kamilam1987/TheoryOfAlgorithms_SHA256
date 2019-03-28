#include<stdio.h>
#include<stdint.h>

uint8_t *givemeints(uint8_t *theints) {



	for(int i = 0; i < 20;i++) {
		theints[i] = i * i;
	}
	return theints;
}

int main(int argc, char *argv[]){
	
	uint8_t theints[20];
	 givemeints(theints);

	for (int i = 0; i < 20; i++){
		printf("Element %2i is %zu.\n", i, theints[i]);
	}
	return 0;
}
