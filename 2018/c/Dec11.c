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
	int grid[GRIDSIZE][GRIDSIZE] = {0};

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		printf("%s\n",line);
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
				grid[i][j]     = powerLevel;
			}
		}
		int biggestPower = INT_MIN;
		int biggestX = -1;
		int biggestY = -1;
		for(int i=0; i<GRIDSIZE-2; i++) {
			for(int j=0; j<GRIDSIZE-2; j++) {
				int squarePower=0;
				for(int k=i; k<i+3; k++) {
					for(int l=j; l<j+3; l++) {
						squarePower += grid[k][l];
					}
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
			printf("block %dx%d\n",blockSize,blockSize);
			for(int i=0; i<GRIDSIZE-(blockSize-1); i++) {
				for(int j=0; j<GRIDSIZE-(blockSize-1); j++) {
					int blockPower = 0;
					for(int k=i; k<i+blockSize; k++) {
						for(int l=j; l<j+blockSize; l++) {
							blockPower += grid[k][l];
						}
					}
					if(blockPower>biggestPower) {
						biggestPower = blockPower;
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
