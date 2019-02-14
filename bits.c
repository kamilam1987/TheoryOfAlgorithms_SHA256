#include <stdio.h>
#include<stdint.h>

/* Prints 32 bits int  in binary */
void binprint(uint32_t x) {
	int i;
	uint32_t one = 1;

	for(i = 0; i< 32; i++)
		/* Takes 1 and shifted up 31 times to the left */
		if((one << (31 - i)) & x)
			printf("1");
		else
			printf("0");
			
}
/*
 * Rotate left (circular left shift) operation, where x is a w-bit word and n
 * is an integer with 0<=n < w, is defined by ROTL n(x)=(x << n)v(x >> w - n)
 */
uint32_t rotl(uint32_t x, int n) {
	return ((x<< n) | (x >> (32 - n)));
}
/*
 * The rotate right (circular right shift) operation, where x is a w-bit word
 * and n is an integer with 0 <= n < w, is defined by ROTR n(x)=(x >> n)v (x << w - n).
 */
uint32_t rotr(uint32_t x, int n) {
	return ((x << (32 - n)) | (x >> n));
}

int main(int arcg, char *argv[]) {
	uint32_t a = 0x428a2f98;
	uint32_t b = 0x71374491;

	printf("hex a: %08x\n", a);
	printf("hex b: %08x\n", b);

	printf("a: "); binprint(a); printf("\n");
	printf("b: "); binprint(b); printf("\n");
	
	 /* 
	  * Bitwise Operators
	  * References: https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm
	  */
	//printf("&: %08x\n", (a&b));
	printf("   a&b: "); binprint(a&b); printf("\n");
	//printf("|: %08x\n", (a|b));
	printf("   a|b: "); binprint(a|b); printf("\n");
	//printf("^: %08x\n", (a^b));
	printf("   a^b "); binprint(a^b); printf("\n");
	//printf("~: %08x\n", (~a));
	printf("   ~a: "); binprint(~a); printf("\n");
	//printf("<<: %08x\n", (a<<1));	
	printf("   a<<1 "); binprint(a<<1); printf("\n");
        //printf(">>: %08x\n", (a>>1));	
	printf("   a>>1 "); binprint(a>>1); printf("\n");

	printf("rotl(a,3): "); binprint(rotl(a,3)); printf("\n");
	printf("rotr(a,3): "); binprint(rotr(a,3)); printf("\n");


	return 0;

}
