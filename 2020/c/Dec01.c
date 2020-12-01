#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"
#define GOAL  2020

int main() {
	FILE * fp;
	char * line    = NULL;
	size_t len     = 0;
	int entriesLen = 1;
	int part1      = 0;
	int part2      = 0;
	int * entries  = malloc(entriesLen * sizeof(int));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}


	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		entries[entriesLen-1] = atoi(line);
		entriesLen++;
		entries = realloc(entries, entriesLen * sizeof(int));
	}

	for(int i=0; i<entriesLen-1; i++) {
		for(int j = 0; j<entriesLen-1; j++) {
			if(i!=j && entries[i]+entries[j] == GOAL) {
				part1 = entries[i]*entries[j];
				break;
			}
		}
		if(part1!=0) {
			break;
		}
	}

	for(int i=0; i<entriesLen-1; i++) {
		for(int j=0; j<entriesLen-1; j++) {
			for(int k=0; entries[i]+entries[j]<GOAL && k<entriesLen-1; k++) {
				if(i!=j && i!=k && j!=k && entries[i]+entries[j]+entries[k] == GOAL) {
					part2 = entries[i]*entries[j]*entries[k];
					break;
				}
			}
			if(part2!=0){
				break;
			}
		}
		if(part2!=0){
			break;
		}
	}

	printf("part 1:%d\n", part1);
	printf("part 2:%d\n", part2);
	fclose(fp);
	free(line);
	free(entries);
	exit(EXIT_SUCCESS);
}
