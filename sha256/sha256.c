/* Author: Kamila Michel
 * The Secure Hash Algorithm, 256 bit version
 * Theory of algorithms project 2019 
 */

// Input and output header file.
#include <stdio.h>
// Uses for fixed-bit length integers.
#include <stdin.h>

void sha256();

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
}
