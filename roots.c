#include <stdio.h>
#include <math.h>
#include<stdint.h>
/* Array of primes */
uint32_t primes[] = {
	      2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
	 31, 37, 41,  43, 47, 53, 59, 61, 67, 71, 
     73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
283, 293, 307, 311,
};
int main(int argc, char *argv[]){
       	long double cubeRoot;
       	long double fraction;
       	long double multiply;
       	for (int i = 0; i < 64; i++){
	       	/* Cube root of a prime number */
		cubeRoot = cbrtl((long double) primes[i]);
		/* Getting the fractional part of a cube roor(part after the decilam place) */
	       	fraction = cubeRoot - floor(cubeRoot);
	       	/* Multiply 2 to the power of 32 which shifts number up 32 bits */
	       	multiply = fraction * 0x100000000;
	       	multiply = floorl(multiply);
		 printf("%3d -> %3.6Lf -> %03.6Lf -> %08x\n", primes[i], cubeRoot, fraction,(uint32_t) multiply );
       	}
       	return 0;
}
