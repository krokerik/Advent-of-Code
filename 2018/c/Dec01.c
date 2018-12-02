#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"

int main() {
	FILE * fp;
	char * line   = NULL;
	size_t len    = 0;
	int freq      = 0;
	int freqsLen  = 1;
	int changeLen = 1;
	int loop      = 0;
	int * frequencies  = malloc(freqsLen * sizeof(int));
	int * changes      = malloc(changeLen * sizeof(int));
	int foundDuplicate = 0;

	frequencies[freqsLen-1] = freq;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}


	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		changes[changeLen-1] = atoi(line);
		changeLen++;
		changes = realloc(changes, changeLen * sizeof(int));
	}
	while(foundDuplicate == 0) {
		for(int i=0; i<changeLen-1; i++) {
			freq += changes[i];
			for(int j=0; foundDuplicate == 0 && j<freqsLen; j++) {
				if(frequencies[j] == freq) {
					foundDuplicate = 1;
					printf("Duplicate: %d\n",freq);
				}
			}
			if(foundDuplicate==1 && loop>0) {
				break;
			}
			freqsLen++;
			frequencies = realloc(frequencies, freqsLen * sizeof(int));
			frequencies[freqsLen-1] = freq;
		}
		loop++;
		if(loop==1) {
			printf("Final frequency: %d\n",freq);
		}
	}

	fclose(fp);
	free(frequencies);
	free(changes);
	free(line);
	exit(EXIT_SUCCESS);
}
