#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/05.txt"
#define LENGTH 10

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int *seats  = malloc(sizeof(int));
	int part1   = 1;
	int part2   = 0;
	seats[0]    = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		int row[2]  = {0,127};
		int seat[2] = {0,7};
		for(int i=0; i<LENGTH; i++) {
			int range;
			switch(line[i]){
				case 'F':
					range   = row[1]-row[0]+1;
					row[1] -= range/2;
					break;
				case 'B':
					range   = row[1]-row[0]+1;
					row[0] += range/2;
					break;
				case 'L':
					range    = seat[1]-seat[0]+1;
					seat[1] -= range/2;
					break;
				case 'R':
					range    = seat[1]-seat[0]+1;
					seat[0] += range/2;
					break;
				default:
					printf("unknown char '%c'\n",line[i]);
					break;
			}
		}
		int id = row[0] * 8 + seat[0];
		if(id>part1) {
			seats = realloc(seats,(id+1)*sizeof(int));
			memset(seats+part1,0,sizeof(int) * (id-part1));
			part1 = id;
		}
		seats[id] = 1;
	}
	for(int i=1; i<part1; i++) {
		if(seats[i-1] && !seats[i] && seats[i+1]){
			part2 = i;
			break;
		}
	}
	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);
	fclose(fp);
	free(line);
	free(seats);
	exit(EXIT_SUCCESS);
}
