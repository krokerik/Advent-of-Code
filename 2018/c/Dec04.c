#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/04.txt"

int stringsrt(const void *a, const void *b);

int main() {
	FILE * fp;
	char * line      = NULL;
	size_t len       = 0;
	char ** input    = malloc(sizeof(char*));
	int inputLen     = 0;
	int biggestGuard = -1;
	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		if(line[19] == 'G') {
			int id = atoi(line+26);
			if(id>biggestGuard) {
				biggestGuard = id;
			}
		}

		inputLen++;
		input = realloc(input, sizeof(char*) * inputLen);
		input[inputLen-1] = malloc(sizeof(char) * (strlen(line)+1));
		strcpy(input[inputLen-1],line);
	}

	qsort(input, inputLen, sizeof(char*), stringsrt);

	int guards[biggestGuard+1][60]; //make one bigger because the  id's are used as indexes.
	memset(guards,0,sizeof(int) * (biggestGuard+1) * 60);
	int lastGuard = -1;
	int sleepStart = 0;
	for(int i=0; i<inputLen; i++) {
		if(input[i][19] == 'G') {
			lastGuard = atoi(input[i]+26);
		} else if(input[i][19] == 'f') {
			sleepStart = atoi(input[i]+15);
		} else if(input[i][19] == 'w') {
			int sleepStop = atoi(input[i]+15);
			for(int j=sleepStart; j<sleepStop; j++) {
				guards[lastGuard][j]++;
			}
		}
		free(input[i]);
	}

	int sleepiestGuard = -1;
	int minutes = -1;
	int sleepiestMinute = -1;
	int consistentMinute = 0;
	int consistentGuard = 0;
	for(int i=0; i<biggestGuard; i++) {
		int tot = 0;
		int sleepiest = 0;
		for(int j=0; j<60; j++) {
			tot += guards[i][j];
			if(guards[i][j]>guards[consistentGuard][consistentMinute]) {
				consistentMinute = j;
				consistentGuard  = i;
			}
			if(guards[i][j]>guards[i][sleepiest]) {
				sleepiest = j;
			}
		}
		if(tot>minutes) {
			minutes = tot;
			sleepiestGuard = i;
			sleepiestMinute = sleepiest;
		}
	}
	printf("part1: %d\n",sleepiestGuard*sleepiestMinute);
	printf("part2: %d\n",consistentGuard*consistentMinute);
	free(input);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int stringsrt(const void *a, const void *b) {
	return strcmp(*(const char **)a,*(const char**)b);
}
