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


//Staus for padding the message(tracks how the file is reading).
enum status {READ, PAD0, PAD1, FINISH};

uint32_t t( uint32_t val )
{
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
	return (val << 16) | (val >> 16);
}

uint64_t s( uint64_t val )
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL ) | ((val >> 8) & 0x00FF00FF00FF00FFULL );
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL ) | ((val >> 16) & 0x0000FFFF0000FFFFULL );
	return (val << 32) | (val >> 32);
}

int main(int argc, char *argv[]) {

	//Declare instance of message block.
	union msgblock M;

	// Tracks all read bits
	uint64_t nobits = 0;

	// Current number of bytes(0-64) that file reads.
	uint64_t nobytes;

	// Declares status variable at the start.
	enum status S = READ;

	//Declare a pointer of type file.
	FILE* fptr;

	//Opens a file.
	fptr = fopen(argv[1], "r");

	int i;

	// Test for file nor existing.
	if (fptr == NULL) {
		printf("Error! Could not open file\n");
		exit(-1);
	}
	
	while (S== READ) {
		//Outputs 64 bits integer using llu-unsigned long long int
		nobytes = fread(M.e, 1, 64, fptr);
		printf("Read %2llu bytes\n", nobytes);

		// Previos number of bytes plus current number of bytes multiply by 8.
		nobits = nobits + (nobytes * 8);
		// 64 -(8+1)
		if (nobytes < 56) {
			printf("I've found a block with less then 55 bytes!\n");
			// The first bytes in M that has not been written over.
			// 80 it's the hex value(0ne followed by seven zeros).
			M.e[nobytes] = 0x80;
			while(nobytes < 56) {
				nobytes = nobytes + 1;
				// Sets all bytes to 0.
				M.e[nobytes] = 0x00;
			}
			// Sets last element to nobits(number of bits in orginal message).
			M.s[7] = nobits;
			// Sets status to finish
			S = FINISH;
		}else if (nobytes < 64){
			// Needs another message block that gives all zeros
			S = PAD0;
			M.e[nobytes] = 0x80;
			// If can add some of the padding to current block but not all
			// Pend with one and fill with all zeros
			while (nobytes < 64) {
				nobytes = nobytes + 1;
				M.e[nobytes] = 0x00;
			}
		
		// Checks if it's at the end of the file.
		}else if (feof(fptr)) {
			S = PAD1;
		}

		//printf("%llu\n", nobytes);

	}
	// If has another message block to deliver.
	if (S == PAD0 || S == PAD1) {
		for (i = 0; i < 56; i++)
			// Adds a block of paddings where the first 448 bits are zeros
			M.e[i] = 0x00;
		//Puts the 64 bits big endian int representing the number of bits that were in the oginal message.
		M.s[7] = nobits;
	}
	if (PAD1)
		M.e[0] = 0x80;
	// Reads first character from a  file.
	// printf("%c\n",fread(&c, 1, 1, fptr));

	fclose(fptr);

	for (int i = 0; i < 64; i++)
		// Outputs all elements of M  as 64 indyvidual bytes
		printf("%x ", M.e[i]);
	printf("\n");
	

	return 0;

}
