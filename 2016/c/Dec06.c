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
	char* part1 = malloc(wordlen+1);
	char* part2 = malloc(wordlen+1);
	for(int i=0; i<wordlen; i++) {
		int most  = 0;
		int least = 0;
		for(int j=0; j<26; j++) {
			if(freq[i][j]!=0) {
				most = freq[i][most]>freq[i][j]?most:j;
				least = freq[i][least]<freq[i][j]?least:j;
			}
		}
		part1[i] = most+'a';
		part2[i] = least+'a';
		free(freq[i]);
	}
	part1[wordlen] = '\0';
	part2[wordlen] = '\0';
	printf("part1 %s\n", part1);
	printf("part2 %s\n", part2);

	free(part1);
	free(part2);
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
