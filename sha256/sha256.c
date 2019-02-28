/* Author: Kamila Michel
 * The Secure Hash Algorithm, 256 bit version
 * Theory of algorithms project 2019 
 */

// Input and output header file.
#include <stdio.h>
// Uses for fixed-bit length integers.
#include <stdin.h>

void sha256();

// Secton 4.1.2 Functions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// Section 3.2 for definitions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);
// Main method
int main(int argc, char *argv[]){
	sha256();
	return 0;
}

void sha256(){
	// Message schedule sixty-four 23-bt words
	uint32_t W[64];
	// Working variables (Section 6.2)
	uint32_t a, b, c, d, e, f, g, h;
	// The hash value
	uint32_t H[8];
	// Two temporary variables
	uint32_t T1, T2;
	// The Hash value 
	uint32_t H[8] = {
		//The values from section 5.3.3 in hex
		  0x6a09e667
		, 0xbb67ae85
		, 0x3c6ef372
		, 0xa54ff53a
		, 0x510e527f
		, 0x9b05688c
		, 0x1f83d9ab
		, 0x5be0cd19
	};

	// The current message block.
	uint32_t M[16];
	// From page 22, W[t]=m[t] for 0<=t <=15
	int t;

	// Loops through first 16 elements of W
	for(t = 0; t < 16; t++)
		W[t] = M[t];

	// From page 22, W[t] = ...
	for(t = 16; t < 64; t++)
		sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
	// Initialise a, b, c, d, e, f, g, h as er Step 2 from section 6.2
	a = H[0]; b = H[1]; c = H[2]; d = H[3];
       	e = H[4]; f = H[5]; g = H[6]; h = H[7];	

	// Step 3 from secion 6.2
	for (t = 0; t < 64; t++){
		T1 = h + SIG_1(e) + Ch(e, f, g) + K[t] + W[t];
		T2 = SIG_0(a) + Maj(a, b, c);
		h = g;
		g = f;
		f = e;
		e = d + T!;
		d = c;
		c = b;
		b = a;
		a = T1 + T2;
	}

	// Step 4
	H[0] = a + H[0];
	H[1] = b + H[1];
	H[2] = c + H[2]
	H[3] = d + H[3]
	H[4] = e + H[4]
	H[5] = f + H[5]
	H[6] = g + H[6]
	H[7] = h + H[7]

}

uint32_t rotr(uint32_t n, uint32_t x){
	return (x >> n) | (x << (32 - n));
}
uint32_t shr(uint32_t n, uint32_t x){
	return (x >> n);
}
uint32_t sig0(uint32_t x){
	return (rotr(7, x) ^ rotr(18, x) ^ shr(3, x));
}

uint32_t sig1(uint32_t x){
	return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x)); 
}
