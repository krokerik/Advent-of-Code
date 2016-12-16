#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT  "../input/16.txt"
#define LENGTH 272

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
		char* data = malloc(strlen(line)+1);
		strcpy(data,line);
		data[strlen(line)] = '\0';
		while(strlen(data)<LENGTH){
			printf("\r%7.3f%%",(float)strlen(data)/LENGTH*100);
			fflush(stdout);
			char* tmp = getDragon(data);
			free(data);
			data = tmp;
		}
		data[LENGTH] = '\0';
		char* checksum = getChecksum(data);
		printf("\rchecksum %s\n",checksum);
		free(checksum);
		free(data);
	}
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

char* getDragon(char* data){
	char* checksum = malloc((strlen(data)*2)+2);
	for(int i=0; i < (strlen(data)*2)+1; i++){
		if(i<strlen(data)){
			checksum[i] = data[i];
		}else if(i == strlen(data)){
			checksum[i] = '0';
		}else{
			if(data[strlen(data)+(strlen(data)-i)] == '0')
				checksum[i] = '1';
			else
				checksum[i] = '0';
		}
	}
	checksum[(strlen(data)*2)+1] = '\0';
	return checksum;
}

char* getChecksum(char* data){
	if(strlen(data)%2==1){
		char* checksum = malloc(strlen(data)+1);
		strcpy(checksum,data);
		return checksum;
	}
	char* checksum = malloc((strlen(data)/2)+1);
	for(int i=0; i<strlen(data); i+=2){
		checksum[i/2] = data[i]==data[i+1]?'1':'0';
	}
	checksum[strlen(data)/2] = '\0';
	char* tmp = getChecksum(checksum);
	free(checksum);
	return tmp;
}
