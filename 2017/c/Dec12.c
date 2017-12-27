#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define INPUT "../input/12.txt"

void parseLine(char* line);
void addPipe(int origin, int* dest);
int* getConnected(int* visited, int origin);
int inArray(int val, int* arr, int len);

int** pipes, biggest;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	biggest     = 0;
	pipes       = malloc(sizeof(int*));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		parseLine(line);
	}
	
	int* visited = malloc(sizeof(int));
	visited[0] = 1;
	visited = getConnected(visited,0);
	printf("part 1: %d\n",visited[0]-1);

	int numGroups = 1;
	for(int i=0; i<biggest; i++) {
		if(!inArray(i,visited+1,visited[0]-1)) {
			visited = getConnected(visited,i);
			numGroups++;
		}
	}
	printf("part 2: %d\n",numGroups);

	for(int i=0; i<biggest+1; i++) {
		free(pipes[i]);
	}
	fclose(fp);
	free(visited);
	free(line);
	free(pipes);
	exit(EXIT_SUCCESS);
}

void parseLine(char* line) {
	int origin,
	    *dest = malloc(sizeof(int)),
	    tmp,
	    len = 0;
	origin = strtol(line, &line, 10);
	tmp = strtol(line, &line, 10);
	while (*line) {
		if (isdigit(*line)) {
		    tmp = strtol(line, &line, 10);
			dest = realloc(dest,sizeof(int)*(len+2));
			dest[0] = ++len; // storing length in first element of array.
			dest[len] = tmp;
		} else {
		    line++;
		}
    }

	addPipe(origin, dest);
}

void addPipe(int origin, int* dest) {
	if(origin > biggest) {
		pipes = realloc(pipes, sizeof(int*)*(origin+1));
		biggest = origin;
	}
	pipes[origin] = dest;
}

int* getConnected(int* visited, int origin) {
	visited = realloc(visited,sizeof(int)*(visited[0]+1));
	visited[visited[0]++] = origin; // storing length in first element.
	for(int i=1; i<=pipes[origin][0]; i++) {
		if(!inArray(pipes[origin][i],visited+1,visited[0]-1))
			visited = getConnected(visited,pipes[origin][i]);
	}
	return visited;
}

int inArray(int val, int* arr, int len) {
	int in = 0;
	for(int i=0; i<len; i++){
		if(arr[i] == val) {
			in = 1;
			break;
		}
	}
	return in;
}
