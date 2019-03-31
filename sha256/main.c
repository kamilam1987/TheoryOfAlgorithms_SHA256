/* Author: Kamila Michel
 * The Secure Hash Algorithm, 256 bit version
 * Theory of algorithms project 2019
 */

// Headers and libraries
#include "SHA_256.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	//Declare a pointer of type file and file name.
	FILE* fptr;
	char* fName;
	fName = argv[1];
	char c;
	
	// Opens file contents
	FILE *fc = fopen(argv[1], "r");
	//Opens a file.
	fptr = fopen(fName, "r");

	printf("\t\t*** SHA256 HASH ALGORITHM ***\n");
	
	// Test for file not existing.
	if (fptr == NULL) {
		/* Unable to open file hence exit */
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        exit(EXIT_FAILURE);
	}
	else {
		printf("File opened successfully. Reading file contents character by character... \n");
		printf("\n\t\t\t FILE CONTENT\n");
		printf("\t\t\t**************\n ");
		// Runs the file content.
		c = fgetc(fc); 
    	while (c != EOF) 
    	{   // Reads characters from file.
			printf ("%c", c); 
			c = fgetc(fc); 
    	} 
		// Runs the secure hash algorithm on the file.
		sha256(fptr);
	}
	// Close the file.
	fclose(fptr);
	return 0;
}
