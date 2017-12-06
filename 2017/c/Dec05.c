#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/05.txt"

int part1(long* maze, int len);
int part2(long* maze, int len);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	
	long* maze = malloc(sizeof(long));
	char* end;
	int num = 0;
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		maze[num++] = strtol(line,&end,10);
		maze = realloc(maze,sizeof(long) * (num+1));
	}
	long* maze2 = malloc(sizeof(long)*num);
	maze2 = memcpy(maze2,maze,sizeof(long)*num);
	printf("number of jumps: %d\n",part1(maze2, num));
	printf("number of jumps: %d\n",part2(maze, num));
	fclose(fp);
	free(line);
	free(maze);
	free(maze2);
	exit(EXIT_SUCCESS);
}

int part1(long* maze, int len) {
	int pos = 0, jumps = 0;
	while(pos>=0 && pos<len) {
		pos += maze[pos]++;
		jumps++;
	}
	return jumps;
}

int part2(long* maze, int len) {
	int pos = 0, jumps = 0;
	while(pos>=0 && pos<len) {
		pos += maze[pos]>=3 ? maze[pos]-- : maze[pos]++;
		jumps++;
	}
	return jumps;
}