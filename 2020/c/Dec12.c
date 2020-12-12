#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/12.txt"

typedef enum {
	north,
	east,
	south,
	west,
	left,
	right,
	forward
} Direction;

typedef struct instruction {
	Direction dir;
	int dist;
} instruction;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int part1   = 0;
	int part2   = 0;
	int numInstructions        = 0;
	instruction* instructions  = malloc(sizeof(instruction));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}


	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		instruction tmp;
		char c;
		sscanf(line,"%c%d",&c,&tmp.dist);
		switch(c) {
			case 'N':
				tmp.dir = north;
				break;
			case 'S':
				tmp.dir = south;
				break;
			case 'E':
				tmp.dir = east;
				break;
			case 'W':
				tmp.dir = west;
				break;
			case 'L':
				tmp.dir = left;
				break;
			case 'R':
				tmp.dir = right;
				break;
			case 'F':
				tmp.dir = forward;
				break;
			default:
				fprintf(stderr,"unknown instruction \"%c\"\n",c);
		}
		numInstructions++;
		instructions = realloc(instructions, numInstructions * sizeof(instruction));
		instructions[numInstructions-1] = tmp;
	}

	int posx=0, posy=0;
	Direction facing = east;
	int multi[6][2] = {{0,-1},{1,0},{0,1},{-1,0}, //cardinals
	                   {-1,-1},{1,1}};            //turning
	for(int i=0; i<numInstructions; i++) {
		switch(instructions[i].dir) {
			case north:
			case south:
			case west:
			case east:
				posx += instructions[i].dist * multi[instructions[i].dir][0];
				posy += instructions[i].dist * multi[instructions[i].dir][1];
				break;
			case left:
			case right:
				facing = (facing+((instructions[i].dist * multi[instructions[i].dir][0])/90))%4;
				break;
			case forward:
				posx += instructions[i].dist * multi[facing][0];
				posy += instructions[i].dist * multi[facing][1];
				break;
		}
	}
	part1 = abs(posx) + abs(posy);
	printf("part 1:%d\n", part1);
	printf("part 2:%d\n", part2);
	fclose(fp);
	free(line);
	free(instructions);
	exit(EXIT_SUCCESS);
}
