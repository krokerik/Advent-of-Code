#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/09.txt"

int uncompress(char* raw);
char* uncompressV2(char* raw);

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
		printf("basic uncompress:    %d\n",uncompress(line));
		char* adv = uncompressV2(line);
		printf("advanced uncompress: %d\n",strlen(adv)-1);
		free(adv);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int uncompress(char* raw){
	int depth = 0, total = 0;
	for(int i=0, len=strlen(raw)-1; i<len; i++){
		switch(raw[i]){
			case '(':
				depth++;
				break;
			case ')':
				depth--;
				break;
			default:
				if(depth==0){
					total++;
				}else if(depth==1){
					int pos = i;
					int amount = atoi(raw+pos);
					int times = 0;
					do {
						if(raw[pos]=='x')
							times = atoi(raw+pos+1);
						pos++;
					}while(raw[pos]!=')');
					total += amount*times;
					i = pos+amount;
					depth--;
				}
		}
	}
	return total;
}
char* uncompressV2(char* raw){
	char* uncompressed = malloc(sizeof(char)*strlen(raw)+2);
	int pos,amount, times, total;
	strcpy(uncompressed, raw);
	for(int i=0; i<strlen(uncompressed); i++){
		printf("\r%6.2f%%",(float)i/strlen(uncompressed)*100);
		fflush(stdout);
		if(uncompressed[i] == '('){
			pos=i+1;
			amount = atoi(uncompressed+pos);
			do {
				if(uncompressed[pos]=='x')
					times = atoi(uncompressed+pos+1);
				pos++;
			}while(uncompressed[pos]!=')');
			char* buffer = malloc((sizeof(char)*amount)+1);
			strncpy(buffer, uncompressed+pos+1, amount);
			buffer[amount] = '\0';
			char* temp = uncompressV2(buffer);
			free(buffer);
			buffer = malloc((strlen(temp)*times)+1);
			strcpy(buffer, temp);
			for(int j=1; j<times; j++){
				strcat(buffer,temp);
			}
			buffer[strlen(temp)*times] = '\0';
			free(temp);
			temp = malloc(sizeof(char)*(strlen(uncompressed)+strlen(buffer)));
			strcpy(temp,uncompressed);
			temp[i] = '\0';
			strcat(temp,buffer);
			strcat(temp,uncompressed+pos+amount+1);
			i += strlen(buffer);
			free(uncompressed);
			free(buffer);
			uncompressed = temp;
		}
	}
	return uncompressed;
}
