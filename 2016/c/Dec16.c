#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT  "../input/16.txt"
#define PART1  272
#define PART2  35651584
#define LENGTH PART2

char* getDragon(char* data);
char* getChecksum(char* data);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1]='\0';
		char* data = getDragon(line);
		data[LENGTH] = '\0';
		char* checksum = getChecksum(data);
		printf("checksum %s\n",checksum);
		free(checksum);
		free(data);
	}
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

char* getDragon(char* data){
	int len = strlen(data), pos = 0;
	char* dragon = malloc((LENGTH+1)*sizeof(char));
	while(len<LENGTH){
		for(int i=pos; i<len*2+1 && i<LENGTH; i++){
			if(i<len){
				dragon[i] = data[i];
			}else if(i==len){
				dragon[i] = '0';
			}else{
				dragon[i] = data[len+(len-i)]=='0'?'1':'0';
			}
		}
		dragon[(len*2+1)<LENGTH?len*2+1:LENGTH] = '\0';
		data = dragon;
		len = strlen(dragon);
		pos = strlen(dragon);
	}
	return dragon;
}

char* getChecksum(char* data){
	int len = strlen(data);
	if(len%2==1){
		char* checksum = malloc(len+1);
		strcpy(checksum,data);
		return checksum;
	}
	char* checksum = malloc((len/2)+1);
	for(int i=0; i<len; i+=2){
		checksum[i/2] = data[i]==data[i+1]?'1':'0';
	}
	checksum[strlen(data)/2] = '\0';
	char* tmp = getChecksum(checksum);
	free(checksum);
	return tmp;
}
