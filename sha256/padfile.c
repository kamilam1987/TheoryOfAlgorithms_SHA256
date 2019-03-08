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

	// Tracks all read bits
	uint64_t nobits = 0;

	// Current number of bytes(0-64)
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
		nobits = nobits + (nobytes * 8);
		// 64 -(8+1)
		if (nobytes < 56) {
			printf("I've found a block with less then 55 bytes!\n");
			M.e[nobytes] = 0x80;
			while(nobytes < 56) {
				nobytes = nobytes + 1;
				// Sets all bytes to 0.
				M.e[nobytes] = 0x00;
			}
			// Sets last element to nobits
			M.s[7] = nobits;
			// Set last 8 bytes as 64 int
		}
		//printf("%llu\n", nobytes);

	}
	// Reads first character from a  file.
	// printf("%c\n",fread(&c, 1, 1, fptr));

	fclose(fptr);

	for (int i = 0; i < 64; i++)
		// Outputs all elements of M  as 64 indyvidual bytes
		printf("%x ", M.e[i]);
	printf("\n");
	

	return 0;

}
