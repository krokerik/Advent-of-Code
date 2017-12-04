#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/04.txt"

long part1(char* seq);
long part2(char* seq);
int** getSpiral(int width);
int isAnagram(char* w1, char* w2);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	int numValid = 0;
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		//if(part1(line) == 1) {
		if(part2(line) == 1) {
			numValid++;
		}
	}
	printf("num valid: %d\n",numValid);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long part1(char* seq) {
	char* word = strtok(seq," ");
	char** sentence = malloc(sizeof(char**));
	int pos = 0, valid = 1;
	do {
		sentence[pos] = malloc(strlen(word) + 1);
		strcpy(sentence[pos],word);
		pos++;
		sentence = realloc(sentence, sizeof(char**)*(pos+1));
		word = strtok(NULL, " ");
	} while(word != NULL);
	for(int i=0; i<pos; i++) {
		for(int j=i+1; j<pos; j++) {
			if(strcmp(sentence[i],sentence[j])==0) {
				valid = 0;
			}
		}
		free(sentence[i]);
	}
	free(sentence);
	return valid;
}

long part2(char* seq) {
		char* word = strtok(seq," ");
	char** sentence = malloc(sizeof(char**));
	int pos = 0, valid = 1;
	do {
		sentence[pos] = malloc(strlen(word) + 1);
		strcpy(sentence[pos],word);
		pos++;
		sentence = realloc(sentence, sizeof(char**)*(pos+1));
		word = strtok(NULL, " ");
	} while(word != NULL);
	for(int i=0; i<pos; i++) {
		for(int j=i+1; j<pos; j++) {
			if(isAnagram(sentence[i],sentence[j])==1) {
				valid = 0;
			}
		}
		free(sentence[i]);
	}
	free(sentence);
	return valid;
}

int isAnagram(char* w1, char* w2) {
	int valid = 1;
	
	if(strlen(w1)!=strlen(w2)) {
		valid = 0;
	} else {
		int len = strlen(w1), alpha1[26] = {0}, alpha2[26] = {0};
		for(int i=0; i<len; i++) {
			alpha1[w1[i]-'a']++;
			alpha2[w2[i]-'a']++;
		}
		for(int i=0; i<26; i++) {
			if(alpha1[i]!=alpha2[i]) {
				valid = 0;
				break;
			}
		}
	}
	return valid;
}