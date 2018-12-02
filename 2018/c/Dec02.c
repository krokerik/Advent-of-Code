#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/02.txt"

int findDup(char * id, int num);
int isPair(char* s1, char* s2);

int main() {
	FILE * fp;
	char * line   = NULL;
	size_t len    = 0;
	int numTwo    = 0;
	int numThree  = 0;
	int numSeen   = 0;
	int foundPair = 0;
	char ** seen  = malloc(sizeof(char*));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		numTwo   += findDup(line,2);
		numThree += findDup(line,3);

		numSeen++;
		seen = realloc(seen,sizeof(char*)*numSeen);
		seen[numSeen-1] = malloc(sizeof(char)*strlen(line)+1);
		strcpy(seen[numSeen-1],line);
	}

	printf("part 1: %d\n",numTwo*numThree);

	for(int i=0; i<numSeen && foundPair==0; i++) {
		for(int j=0; j<numSeen && foundPair==0; j++) {
			if(i!=j) {
				if(isPair(seen[i],seen[j])) {
					foundPair=1;
					int len = strlen(seen[i]);
					printf("part 2: ");
					for(int k=0; k<len; k++) {
						if(seen[i][k]==seen[j][k]) {
							printf("%c",seen[i][k]);
						}
					}
					printf("\n");
				}
			}
		}
	}

	for(int i=0; i<numSeen; i++) {
		free(seen[i]);
	}

	free(seen);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int findDup(char * id, int num) {
	int hasRepeated = 0;
	int len = strlen(id);
	int alphabet[26] = {0};
	for(int i=0; i<len; i++) {
		alphabet[id[i]-'a']++;
	}
	for(int i=0; i<26; i++) {
		if(alphabet[i]==num) {
			hasRepeated=1;
			break;
		}
	}
	return hasRepeated;
}

int isPair(char* s1, char* s2) {
	int inCommon = 0;
	int len = strlen(s1);
	if(len == strlen(s2)) {
		for(int i=0; i<len; i++) {
			if(s1[i] == s2[i]) {
				inCommon++;
			}
		}

	}
	if(len-inCommon == 1) {
		return 1;
	}
	return 0;
}
