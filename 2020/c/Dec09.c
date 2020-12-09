#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/09.txt"
#define PREAMBLE 25

int canSum(long* arr,long target);
long getContiguous(long* arr, int len, long target);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	long part1  = 0;
	long part2  = 0;
	int row     = 0;
	long* codes = malloc(sizeof(long));
	long preamble[PREAMBLE];

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		if(row<PREAMBLE) {
			sscanf(line,"%ld",&preamble[row]);
		} else {
			long target;
			sscanf(line,"%ld",&target);
			if(!part1 && !canSum(preamble,target)) {
				part1 = target;
			} else {
				preamble[row%PREAMBLE] = target;
			}
		}
		row++;
		codes = realloc(codes,sizeof(long)*row);
		codes[row-1] = preamble[(row-1)%PREAMBLE];
	}

	for(int i=0; i<row && !part2; i++) {
		part2 = getContiguous(codes+i,row-i,part1);
	}

	printf("part 1: %ld\n", part1);
	printf("part 2: %ld\n", part2);

	fclose(fp);
	free(line);
	free(codes);
	exit(EXIT_SUCCESS);
}

int canSum(long* arr,long target) {
	int found = 0;
	for(int i=0; i<PREAMBLE && !found; i++) {
		for(int j=i+1; j<PREAMBLE && !found; j++) {
			if(arr[i]+arr[j]==target) {
				found = 1;
			}
		}
	}
	return found;
}

long getContiguous(long* arr, int len, long target) {
	long max = arr[0];
	long min = arr[0];
	long tot = arr[0];

	for(int i=1; i<len && tot<target; i++) {
		tot += arr[i];
		if(arr[i] > max) {
			max = arr[i];
		}
		if(arr[i] < min) {
			min = arr[i];
		}
	}

	return tot==target ? min+max : 0;
}
