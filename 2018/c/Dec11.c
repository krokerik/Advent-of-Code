#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/11.txt"
#define GRIDSIZE 300

int getHundred(int integer);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int integral[GRIDSIZE][GRIDSIZE] = {0};
	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		int gridSerial = atoi(line);
		for(int i=0; i<GRIDSIZE; i++) {
			for(int j=0; j<GRIDSIZE; j++) {
				int x          = i+1;
				int y          = j+1;
				int rackID     = x+10;
				int powerLevel = rackID*y;
				powerLevel    += gridSerial;
				powerLevel    *= rackID;
				powerLevel     = getHundred(powerLevel);
				powerLevel    -= 5;
				integral[i][j] = powerLevel;
				if(i>0) {
					integral[i][j] += integral[i-1][j];
				}
				if(j>0) {
					integral[i][j] += integral[i][j-1];
				}
				if(i>0 && j>0) {
					integral[i][j] -= integral[i-1][j-1];
				}
			}
		}

		int biggestPower = INT_MIN;
		int biggestX = -1;
		int biggestY = -1;
		for(int i=0; i<GRIDSIZE-2; i++) {
			for(int j=0; j<GRIDSIZE-2; j++) {
				int squarePower = integral[i+2][j+2];
				if(i>0) {
					squarePower -= integral[i-1][j+2];
				}
				if(j>0) {
					squarePower -= integral[i+2][j-1];
				}
				if(i>0 && j>0) {
					squarePower += integral[i-1][j-1];
				}
				if(squarePower>biggestPower) {
					biggestPower = squarePower;
					biggestX = i+1;
					biggestY = j+1;
				}
			}
		}
		printf("part1: %d,%d\n",biggestX,biggestY);
		biggestPower = INT_MIN;
		biggestX = -1;
		biggestY = -1;
		int biggestBlock = -1;
		for(int blockSize=1; blockSize<GRIDSIZE; blockSize++) {
			int offset = blockSize-1;
			for(int i=0; i<GRIDSIZE-offset; i++) {
				for(int j=0; j<GRIDSIZE-offset; j++) {
					int squarePower = integral[i+offset][j+offset];
					if(i>0) {
						squarePower -= integral[i-1][j+offset];
					}
					if(j>0) {
						squarePower -= integral[i+offset][j-1];
					}
					if(i>0 && j>0) {
						squarePower += integral[i-1][j-1];
					}
					if(squarePower>biggestPower) {
						biggestPower = squarePower;
						biggestX = i+1;
						biggestY = j+1;
						biggestBlock = blockSize;
					}
				}
			}
		}
		printf("part2: %d,%d,%d\n",biggestX,biggestY,biggestBlock);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getHundred(int integer) {
	int hundred = 0;
	if(integer>=100) {
		hundred = (integer/100)%10;
	}
	return hundred;
}
