#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/11.txt"

int tick(char*** state, int height);
int tock(char*** state, int height);
int numAdjacent(char** map, int height, int width, int y, int x);
int numVisible(char** map, int height, int width, int y, int x);

int main() {
	FILE * fp;
	char * line     = NULL;
	size_t len      = 0;
	int part1       = 0;
	int part2       = 0;
	int mapLen = 0;
	char** map1 = malloc(sizeof(char*));
	char** map2 = malloc(sizeof(char*));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char* row1 = malloc(strlen(line)+1);
		char* row2 = malloc(strlen(line)+1);
		strcpy(row1,line);
		strcpy(row2,line);
		mapLen++;
		map1 = realloc(map1,mapLen*sizeof(char*));
		map2 = realloc(map2,mapLen*sizeof(char*));
		map1[mapLen-1] = row1;
		map2[mapLen-1] = row2;
	}

	while(tick(&map1,mapLen));

	for(int i=0; i<mapLen; i++) {
		int width = strlen(map1[i]);
		for(int j=0; j<width; j++) {
			part1 += map1[i][j]=='#';
		}
		free(map1[i]);
	}
	printf("part 1: %d\n", part1);
	while(tock(&map2,mapLen));
	for(int i=0; i<mapLen; i++) {
		int width = strlen(map2[i]);
		for(int j=0; j<width; j++) {
			part2 += map2[i][j]=='#';
		}
		free(map2[i]);
	}
	printf("part 2: %d\n", part2);

	fclose(fp);
	free(line);
	free(map1);
	free(map2);
	exit(EXIT_SUCCESS);
}

int tick(char*** state, int height) {
	int changed = 0;
	char** tmp = malloc(sizeof(char*)*height);
	for(int i=0; i<height; i++) {
		int len = strlen((*state)[i]);
		tmp[i] = malloc(sizeof(char)*(len+1));
		strcpy(tmp[i],(*state)[i]);
		for(int j=0; j<len; j++) {
			if((*state)[i][j] == 'L' && numAdjacent(*state,height,len,i,j)==0) {
				changed++;
				tmp[i][j] = '#';
			} else if((*state)[i][j] == '#' && numAdjacent(*state,height,len,i,j)>=4) {
				changed++;
				tmp[i][j] = 'L';

			}
		}
	}
	for(int i=0; i<height; i++) {
		free((*state)[i]);
	}
	free(*state);
	*state = tmp;
	return changed;
}
int tock(char*** state, int height) {
	int changed = 0;
	char** tmp = malloc(sizeof(char*)*height);
	for(int i=0; i<height; i++) {
		int len = strlen((*state)[i]);
		tmp[i] = malloc(sizeof(char)*(len+1));
		strcpy(tmp[i],(*state)[i]);
		for(int j=0; j<len; j++) {
			if((*state)[i][j] == 'L' && numVisible(*state,height,len,i,j)==0) {
				changed++;
				tmp[i][j] = '#';
			} else if((*state)[i][j] == '#' && numVisible(*state,height,len,i,j)>=5) {
				changed++;
				tmp[i][j] = 'L';

			}
		}
	}
	for(int i=0; i<height; i++) {
		free((*state)[i]);
	}
	free(*state);
	*state = tmp;
	return changed;
}

int numAdjacent(char** map, int height, int width, int y, int x) {
	int count = 0;
	for(int i=y-1; i<=y+1; i++) {
		for(int j=x-1; j<=x+1; j++) {
			if(!(i==y && j==x) && i>=0 && i<height && j>=0 && j<width) {
				count += map[i][j]=='#';
			}
		}
	}
	return count;
}

int numVisible(char** map, int height, int width, int y, int x) {
	int dir[8][2] ={{-1,-1},
	                {-1,0},
	                {-1,1},
	                {0, -1},
	                {0, 1},
	                {1, -1},
	                {1, 0},
	                {1, 1},};
	int count = 0;
	for(int i=0; i<8; i++) {
		int tmpx = x+dir[i][0];
		int tmpy = y+dir[i][1];
		while(tmpx>=0 && tmpy>=0 && tmpx<width && tmpy<height && map[tmpy][tmpx]=='.') {
			tmpx += dir[i][0];
			tmpy += dir[i][1];
		}
		if(tmpx>=0 && tmpx<width && tmpy>=0 && tmpy<height) {
			count += map[tmpy][tmpx]=='#';
		}
	}
	return count;
}
