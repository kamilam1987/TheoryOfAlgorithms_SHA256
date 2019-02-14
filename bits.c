#include <stdio.h>
#include<stdint.h>

int main(int arcg, char *argv[]) {
	uint32_t a = 1;
	uint32_t b = 2;

	printf("a: %08x\n", a);
	printf("b: %08x\n", b);

	 /* 
	  * Bitwise Operators
	  * References: https://www.tutorialspoint.com/cprogramming/c_bitwise_operators.htm
	  */
	printf("&: %08x\n", (a&b));
	printf("|: %08x\n", (a|b));
	printf("^: %08x\n", (a^b));
	printf("~: %08x\n", (~a));	
	printf("<<: %08x\n", (a<<1));	
	printf(">>: %08x\n", (a>>1));	

	return 0;

}
