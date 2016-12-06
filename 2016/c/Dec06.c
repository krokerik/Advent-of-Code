#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/06.txt"

int** getFrequency(char* word);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	int** freq  = NULL;
	int wordlen = 0;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		int** tmp = getFrequency(line);
		if(i == 0) {
			wordlen = strlen(line)-1;
			freq = tmp;
		} else {
			for(int j=0; j<wordlen; j++) {
				for(int k=0; k<26; k++) {
					freq[j][k] += tmp[j][k];
				}
				free(tmp[j]);
			}
			free(tmp);
		}
	}

	for(int i=0; i<wordlen; i++) {
		int pop = 0;
		for(int j=0; j<26; j++) {
			pop = freq[i][pop]>freq[i][j]?pop:j;
		}
		printf("%c",pop+'a');
		free(freq[i]);
	}
	printf("\n");

	fclose(fp);
	free(line);
	free(freq);
	exit(EXIT_SUCCESS);
}

int** getFrequency(char* word) {
	int** freq;
	int len;

	len = strlen(word)-1;
	freq = malloc(sizeof(int*) * len);
	for(int i=0; i<len; i++) {
		freq[i] = malloc(sizeof(int) * 26);
		for(int j=0; j<26; j++) {
			freq[i][j] = 0;
		}
		freq[i][word[i]-'a']++;
	}

	return freq;
}
