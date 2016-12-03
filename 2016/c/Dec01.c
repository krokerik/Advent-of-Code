#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"
#define DELIM ", "
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef struct pos {
	int north, east;
}pos;

void traverse(char* instructions);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1) traverse(line);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void traverse(char* instructions) {
	char* instruction;
	char direction;
	int distance, facing, total[2], histLen, looped;
	pos* history;
	
	facing = NORTH;
	
	instruction = strtok(instructions, DELIM);
	
	total[NORTH] = 0;
	total[EAST]  = 0;
	
	histLen = 1;
	
	looped = 0;
	
	history = malloc(sizeof(pos*) * histLen);
	history[0].east  = 0;
	history[0].north = 0;
	
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
				fprintf(stderr, "Invalid direction '%c' in instruction '%s'\n",
				        direction, instruction);
				exit(EXIT_FAILURE);
		}
		if(facing<NORTH) {
			facing = WEST;
		} else if(facing>WEST) {
			facing = NORTH;
		}

		pos position;
		
		for(int i=0; i<distance; i++) {
			switch(facing) {
				case NORTH:
					total[NORTH] += 1;
					break;
				case EAST:
					total[EAST]  += 1;
					break;
				case SOUTH:
					total[NORTH] -= 1;
					break;
				case WEST:
					total[EAST]  -= 1;
					break;
				default:
					fprintf(stderr,"Invalid direction '%d'\n", facing);
					exit(EXIT_FAILURE);
			}
			position.north = total[NORTH];
			position.east  = total[EAST];

			for(int i=0; i<histLen && looped == 0; i++) {
				if(history[i].north==position.north && 
				   history[i].east==position.east) {
					printf("loop at (%d;%d), distance: %d\n",position.north,
					       position.east,
					       abs(position.north)+abs(position.east));
					looped = 1;
				}
			}
			history = realloc(history, sizeof(pos) * ++histLen);
			history[histLen-1] = position;
		}
		
		instruction = strtok(NULL, DELIM);
	}
	free(history);
	
	if(looped == 0) printf("no loop found\n");
	printf("num blocks total distance: %d\n",
	       abs(total[NORTH])+abs(total[EAST]));
}