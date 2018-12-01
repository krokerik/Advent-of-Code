#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT "../input/09.txt"

#define PART1 0
#define PART2 1

int getScore(char* data, int* pos, int scoreBase);
int getGarbage(char* data, int* pos);

int part;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		int pos = 0;
		part = PART1;
		printf("part1: %d\n", getScore(line,&pos,0));
		part = PART2;
		pos = 0;
		printf("part2: %d\n", getScore(line,&pos,0));
		
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getScore(char* data, int* pos, int scoreBase) {
	int score   = scoreBase+1,
	    numGarb = 0;
	
	(*pos)++;
	while(data[*pos]!='}') {
		switch(data[*pos]) {
			case '!':
				(*pos)++;
				break;
			case '{':
				if(part == PART1) {
					score   += getScore(data, pos, scoreBase+1);;
				} else {
					numGarb += getScore(data, pos, scoreBase+1);;
				}
				break;
			case '<':
				numGarb += getGarbage(data, pos);
				break;
		}
		(*pos)++;
	}
	
	return part == PART1 ? score : numGarb;
}

int getGarbage(char* data, int* pos) {
	int score = 0;
	(*pos)++;
	while(data[*pos]!='>') {
		switch(data[*pos]) {
			case '!':
				(*pos)++;
				break;
			default:
				score++;
		}
		(*pos)++;
	}
	return score;
}
