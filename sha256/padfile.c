#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

/* Union allows to store different data types in the same memory location.
 * References: https://www.tutorialspoint.com/cprogramming/c_unions.htm
 */
union msgblock {
	uint8_t e[64];
	uint32_t t[16];
	uint64_t s[8];
};

int main(int argc, char *argv[]) {

	//Declare instance of message block.
	union msgblock M;

	uint64_t nobytes;

	//Declare a pointer of type file.
	FILE* fptr;

	//Opens a file.
	fptr = fopen(argv[1], "r");

	// Test for file nor existing.
	if (fptr == NULL) {
		printf("Error! Could not open file\n");
		exit(-1);
	}
	
	while (!feof(fptr)) {
		//Outputs 64 bits integer using llu-unsigned long long int
		nobytes = fread(M.e, 1, 64, fptr);
		printf("%llu\n", nobytes);

	}
	// Reads first character from a  file.
	// printf("%c\n",fread(&c, 1, 1, fptr));

	fclose(fptr);

	return 0;

}
