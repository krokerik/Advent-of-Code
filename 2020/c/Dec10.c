#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/10.txt"

int main() {
	FILE * fp;
	char * line     = NULL;
	size_t len      = 0;
	int part1      = 0;
	int part2      = 0;
	int numAdapters = 0;
	int* adapters   = malloc(sizeof(int));
	int device      = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		int adapter;
		sscanf(line,"%d",&adapter);
		if(adapter>device) {
			device = adapter;
		}
		numAdapters++;
		adapters = realloc(adapters, sizeof(int) * numAdapters);
		adapters[numAdapters-1] = adapter;
	}

	device += 3;
	numAdapters++;
	adapters = realloc(adapters, sizeof(int) * numAdapters);
	adapters[numAdapters-1] = device;

	int curr = 0;
	int jumps[3] = {0};
	while(curr != device) {
		int candidate = INT_MAX;
		for(int i=0; i<numAdapters; i++) {
			if(adapters[i] <= curr+3 && adapters[i]>curr &&
			   adapters[i] < candidate) {
				candidate = adapters[i];
			}
		}
		jumps[candidate-curr-1]++;
		curr = candidate;
	}
	part1 = jumps[0]*jumps[2];
	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}
