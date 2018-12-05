#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/05.txt"

char* react(char* polymer);
char changePolarity(char unit);
void removeUnit(char* str, char unit);

int main() {
	FILE * fp;
	char * line      = NULL;
	size_t len       = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char * input = malloc(sizeof(char)*len);
		strcpy(input, line);
		printf("part1: %zu\n",strlen(react(input)));

		strcpy(input, line);
		int shortest = len;
		for(char c = 'a'; c<='z'; c++) {
			removeUnit(input,c);
			int length = strlen(react(input));
			if(length < shortest) {
				shortest = length;
			}
			strcpy(input, line);
		}
		printf("part2: %d\n",shortest);
		free(input);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

char* react(char* polymer) {
	int len = strlen(polymer);
	int removedUnits = 0;
	for(int i=0; i<len-1; i++) {
		if(changePolarity(polymer[i]) == polymer[i+1]) {
			memmove(polymer+i,polymer+i+2,len-i-2);
			polymer[len-2] = '\0';
			removedUnits = 1;
			i+=2;
		}
	}
	if(removedUnits) {
		polymer = react(polymer);
	}
	return polymer;
}

char changePolarity(char unit) {
	if(unit<'a') {
		unit += 32;
	} else {
		unit -= 32;
	}
	return unit;
}

void removeUnit(char* str, char unit) {
	char polar = changePolarity(unit);
	char *dst;
	for(dst = str; *str != '\0'; str++) {
		*dst = *str;
		if(*dst != unit && *dst != polar) {
			dst++;
		}
	}
	*dst = '\0';
}
