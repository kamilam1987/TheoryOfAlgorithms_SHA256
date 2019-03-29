/* Author: Kamila Michel
 * The Secure Hash Algorithm, 256 bit version
 * Theory of algorithms project 2019 
 */

// Input and output header file.
#include <stdio.h>
// Uses for fixed-bit length integers.
#include <stdint.h>
#include<stdlib.h>

// References: https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define Ch(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
//Represents a message block.
union msgblock {
	uint8_t e[64];
	uint32_t t[16];
	uint64_t s[8];
};

// A flag for where where are in reading the file.
enum status {READ, PAD0, PAD1, FINISH};

// Secton 4.1.2 Functions.
//uint32_t sig0(uint32_t x);
//uint32_t sig1(uint32_t x);

// Section 3.2 for definitions.
//uint32_t rotr(uint32_t n, uint32_t x);
//uint32_t shr(uint32_t n, uint32_t x);

// Definitions section 4.1.2.
//uint32_t SIG0(uint32_t x);
//uint32_t SIG1(uint32_t x);

//uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
//uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// Calculates the SHA256 hash of a file.
void sha256(FILE *fptr);

// Retrives the next message block.
int nextmsgblock(FILE *fptr, union msgblock *M, enum status *S, uint64_t *nobits);

// Main method.
int main(int argc, char *argv[]){

	//Declare a pointer of type file.
	FILE* fptr;
	
	//Opens a file.
	fptr = fopen("test.txt", "r");

	// Test for file nor existing.
	if (fptr == NULL) {
		printf("Error! Could not open file\n");
		exit(1);
	}

	// Runs the secure hash algorithm on the file.
	sha256(fptr);

	// Close the file.
	fclose(fptr);

	return 0;
}

void sha256(FILE *fptr){
	
	//Declare instance of message block.
	union msgblock M;
	
	// Tracks all read bits
	uint64_t nobits = 0;
	
	// Declares status variable at the start.
	enum status S = READ;

	/* The K constatnts. Section 4.2.2 
	 * Sixty-four constatnts 32-bit words. Those words represent the first thirty-two bits of the fractional
	 * parts of the cube roots of the first sixty-four primes numbers. 
	 */
	uint32_t K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	// Message schedule sixty-four 23-bt words.
	uint32_t W[64];
	// Working variables (Section 6.2).
	uint32_t a, b, c, d, e, f, g, h;
	// Two temporary variables.
	uint32_t T1, T2;
	// The Hash value.
	uint32_t H[8] = {
		//The values from section 5.3.3 in hex.
		 0x6a09e667,
		 0xbb67ae85,
		 0x3c6ef372,
		 0xa54ff53a,
		 0x510e527f,
		 0x9b05688c,
		 0x1f83d9ab,
		 0x5be0cd19
	};

	// The current message block.
	//uint32_t M[16] = {0,0,0,0,0,0,0,0};
	// From page 22, W[t]=m[t] for 0<=t <=15.
	int i, t;

	while (nextmsgblock(fptr, &M, &S, &nobits)) {

		// Loops through first 16 elements of W.
		for(t = 0; t < 16; t++)
			//W[t] = M.t[t];
			W[t] = SWAP_UINT32(M.t[t]);

		// From page 22, W[t] = ...
		for(t = 16; t < 64; t++)
			W[t] = SIG1(W[t-2]) + W[t-7] + SIG0(W[t-15]) + W[t-16];
		// Initialise a, b, c, d, e, f, g, h as er Step 2 from section 6.2.
		a = H[0]; b = H[1]; c = H[2]; d = H[3];
       	e = H[4]; f = H[5]; g = H[6]; h = H[7];	

		// Step 3 from secion 6.2.
		for (t = 0; t < 64; t++){
			T1 = h + EP1(e) + Ch(e, f, g) + K[t] + W[t];
			T2 = EP0(a) + Maj(a, b, c);
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		// Step 4.
		H[0] = a + H[0];
		H[1] = b + H[1];
		H[2] = c + H[2];
		H[3] = d + H[3];
		H[4] = e + H[4];
		H[5] = f + H[5];
		H[6] = g + H[6];
		H[7] = h + H[7];
	}
	
	printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7]);

}

int nextmsgblock(FILE *fptr, union msgblock *M, enum status *S, uint64_t *nobits) {

	// Current number of bytes(0-64) that file reads.
	uint64_t nobytes;

	int i;

	// If we have finished all message blocks, then S should be FINISH.
	if(*S == FINISH)
		return 0;

	// Oterwise, check if we need another block full of padding.
	if (*S == PAD0 || *S == PAD1) {
		// Set the first 56 bytes to all zeros bits.
		for (i = 0; i < 56; i++)
			// Adds a block of paddings where the first 448 bits are zeros
			M->e[i] = 0x00;
		//Puts the 64 bits big endian int representing the number of bits that were in the oginal message.
		M->s[7] = *nobits;
		// Finish
		*S = FINISH;		
		
		// If S was PAD1, then set the first bit of M to one.
		if (*S == PAD1)
			M->e[0] = 0x80;
		// Keep the loop in sha256 going for one more iteration.
		return 1;
	}

	//Not finished reading the file
	//Outputs 64 bits integer using llu-unsigned long long int
	nobytes = fread(M->e, 1, 64, fptr);
		
	// Previos number of bytes plus current number of bytes multiply by 8.
	*nobits = *nobits + (nobytes * 8);
	// 64 -(8+1)
	// If less then 56 nytes then put padding in this message block.
	if (nobytes < 56) {
		// The first bytes in M that has not been written over.
		// 80 it's the hex value(0ne followed by seven zeros).
		M->e[nobytes] = 0x80;
		// Add zero bits until the last 64 bits.
		while(nobytes < 56) {
			nobytes = nobytes + 1;
			// Sets all bytes to 0.
			M->e[nobytes] = 0x00;
		}
		// Append the file size in bits as unsigned 64 bits int.
		// Sets last element to nobits(number of bits in orginal message).
		M->s[7] = *nobits;
		// Sets status to finish	
		*S = FINISH;
	//Check if we can put some padding into this message block.
	}else if (nobytes < 64){
		// Needs another message block that gives all zeros
		*S = PAD0;
		//Put the one bit into the current block.
		M->e[nobytes] = 0x80;
		// If can add some of the padding to current block but not all
		// Pend with one and fill with all zeros
		while (nobytes < 64) {
			nobytes = nobytes + 1;
			M->e[nobytes] = 0x00;
		}
	// Checks if it's at the end of the file.
	}else if (feof(fptr)) {
		//Need message block with all padding.
		*S = PAD1;
		//printf("%llu\n", nobytes);
	}

	//Return 1 so this function is called again.	
	return 1;
}


