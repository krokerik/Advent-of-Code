#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

int getNumBlocks(char* instructions);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1) {
		printf("num blocks: %d\n", getNumBlocks(line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getNumBlocks(char* instructions) {
	const char delim[3] = ", ";
	char *instruction;
	char direction;
	int distance, facing;
	int total[4];
	
	facing = NORTH;
	instruction = strtok(instructions, delim);
	total[NORTH] = 0;
	total[EAST] = 0;
	total[SOUTH] = 0;
	total[WEST] = 0;
	
	while(instruction != NULL) {
		distance = atoi(instruction+1);
		direction = instruction[0];
		
		switch(direction) {
			case 'L':
				facing--;
				break;
			case 'R':
				facing++;
				break;
			default:
				fprintf(stderr, "Invalid direction '%c'\n", direction);
				exit(EXIT_FAILURE);
		}
		if(facing<NORTH) {
			facing = WEST;
		} else if(facing>WEST) {
			facing = NORTH;
		}
		
		total[facing] += distance;
		
		instruction = strtok(NULL, delim);
	}
	
	return abs(total[NORTH]-total[SOUTH])+abs(total[EAST]-total[WEST]);
}