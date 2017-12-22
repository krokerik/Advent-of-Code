#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>


#define INPUT  "../input/17.txt"

char* getHash(unsigned char* in);

int main() {
	FILE* fp;
	char* code  = NULL;
	size_t len  = 0;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	if(getline(&code, &len, fp) == -1){
		fprintf(stderr,"%s is empty.\n",INPUT);
		exit(EXIT_FAILURE);
	}
	if(code[strlen(code)-1]=='\n')
		code[strlen(code)-1]='\0';
	char *hash = getHash((unsigned char*)code);
	printf("%s\n",hash);
	
	// hash current
	// see solutions
	// pick
	
	
	fclose(fp);
	free(code);
	free(hash);
	exit(EXIT_SUCCESS);
}

char* getHash(unsigned char* in){
    unsigned char digest[MD5_DIGEST_LENGTH];
    char *hash = malloc(sizeof(char)*33);
	MD5(in, strlen((char*)in), (unsigned char*)&digest);
	for(int i = 0; i < 16; i++)
		sprintf(&hash[i*2], "%02x", (unsigned int)digest[i]);
	return hash;
}
