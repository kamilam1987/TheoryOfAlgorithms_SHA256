#ifndef SHA_256_h

// MACROS
// References: https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c
#define SHA_256_h
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define Ch(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))
#define IS_BIGE (*(uint16_t *)"\0\xff" < 0x100)

#include <stdio.h>
#include <stdint.h>

//Represents a message block.
typedef union test {
  uint8_t e[64];
  uint32_t t[16];
  uint64_t s[8];
}Msgblock;

// A flag for where where are in reading the file.
typedef enum status{
  READ,
  PAD0,
  PAD1,
  FINISH  
} Estatus ;

// References: https://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func?rq=1
uint32_t SWAPE32( uint32_t x );
uint64_t SWAPE64( uint64_t x );
// Calculates the SHA256 hash of a file.
void sha256(FILE *fptr);
// Retrieves the next message block.
int nextmsgblock(FILE *fptr, Msgblock *M, Estatus *S, uint64_t *nobits);

#endif /* SHA_256_h */
