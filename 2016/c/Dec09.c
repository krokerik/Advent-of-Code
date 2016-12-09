#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/09.txt"

int uncompress(char* raw);

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
		printf("%d\n",uncompress(line));
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
