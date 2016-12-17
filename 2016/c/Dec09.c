#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/09.txt"

int uncompress(char* raw);
long long uncompressV2(char* raw);

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
		printf("\radvanced uncompress: %lli\n",uncompressV2(line)-1);
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
long long uncompressV2(char* raw){
	int amount, times;
	long long total=0;
	for(int i=0; i<strlen(raw); i++){
		printf("\r%7.3f%%",(float)i/strlen(raw)*100);
		fflush(stdout);
		if(raw[i] == '('){
			i++;
			amount = atoi(raw+i);
			do {
				if(raw[i]=='x')
					times = atoi(raw+i+1);
				i++;
			}while(raw[i]!=')');
			char* buffer = malloc((sizeof(char)*amount)+1);
			strncpy(buffer, raw+i+1, amount);
			buffer[amount] = '\0';
			total += uncompressV2(buffer)*times;
			free(buffer);
			i += amount;
		}else{
			total++;
		}
	}
	return total;
}
