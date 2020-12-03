#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/03.txt"

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int mapLen  = 1;
	long part2   = 1;
	char ** map = malloc(mapLen * sizeof(char*));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}


	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char* row = malloc(strlen(line)+1);
		strcpy(row,line);
		map[mapLen-1] = row;
		mapLen++;
		map = realloc(map,mapLen*sizeof(char*));
	}

	int routes[5][2] = {{1,1},{1,3},{1,5},{1,7},{2,1}};
	int results[5];
	for(int i=0; i<5; i++) {
		int pos[2] = {0,0};
		int trees = 0;
		while(pos[0]<mapLen-1) {
			trees  += map[pos[0]][pos[1]%strlen(map[pos[0]])] == '#';
			pos[0] += routes[i][0];
			pos[1] += routes[i][1];
		}
		results[i] = trees;
		part2 *= trees;
	}
	for(int i=0; i<mapLen-1; i++) {
		free(map[i]);
	}

	printf("part 1: %d\n", results[1]);
	printf("part 2: %ld\n", part2);
	fclose(fp);
	free(line);
	free(map);
	exit(EXIT_SUCCESS);
}
