#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/07.txt"

typedef struct ssl {
	int type; //1 for ABA, 2 for BAB.
	char str[4];
}ssl;

int hasAbba(char* ipv7);
int hasAba(char* ipv7);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	int numTls  = 0, numSsl = 0;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		numTls += hasAbba(line);
		numSsl += hasAba(line);
	}
	printf("TLS: %d\n", numTls);
	printf("SSL: %d\n", numSsl);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int hasAbba(char* ipv7) {
	int inHypernet = 0, result = 0;
	char abba[] = {' ', ' ', ' ', ' '};

	for(int i=0, len=strlen(ipv7); i<len; i++) {
		for(int j=0; j<3; j++)
			abba[j] = abba[j+1];
		abba[3] = ipv7[i];
		switch(ipv7[i]) {
			case '[':
				inHypernet++;
				break;
			case ']':
				inHypernet--;
				break;
			default:
				if(abba[0]==abba[3] && abba[1]==abba[2] && abba[0]!=abba[1]){
					if(inHypernet == 0) {
						result = 1;
					} else {
						return 0;
					}
				}
		}
	}
	return result;
}

int hasAba(char* ipv7) {
	int inHypernet = 0, num = 0;
	ssl* aba = malloc(sizeof(ssl) * (num));
	char buffer[] = {' ', ' ', ' ', '\0'};

	for(int i=0, len=strlen(ipv7); i<len; i++) {
		buffer[0] = buffer[1];
		buffer[1] = buffer[2];
		buffer[2] = ipv7[i];
		switch(ipv7[i]) {
			case '[':
				inHypernet++;
				break;
			case ']':
				inHypernet--;
				break;
			default:
				if(buffer[0]==buffer[2] && buffer[0]!=buffer[1] &&
				                           buffer[1]!='[' && buffer[1]!=']'){
					aba = realloc(aba, sizeof(ssl) * (num+1));
					for(int j=0; j<4; j++)
						aba[num].str[j] = buffer[j];
					aba[num].type = inHypernet>0?2:1;
					for(int j=0; j<num; j++){
						if(aba[j].type!=aba[num].type &&
						   aba[j].str[0]==aba[num].str[1] &&
						   aba[j].str[1]==aba[num].str[0]) {
							free(aba);
							return 1;
						}
					}
					num++;
				}
		}
	}
	free(aba);
	return 0;
}
