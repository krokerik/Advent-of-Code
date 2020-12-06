#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/06.txt"

int main() {
	FILE * fp;
	char * line     = NULL;
	size_t len      = 0;
	int part1       = 0;
	int part2       = 0;
	int answers[26] = {0};
	int people      = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		if(line[0] == '\0') {
			for(int i=0; i<26; i++) {
				part1 += answers[i]>0;
				part2 += answers[i]==people;
				answers[i] = 0;
			}
			people = 0;
		} else {
			people++;
			int length = strlen(line);
			for(int i=0; i<length; i++) {
				answers[line[i]-'a']++;
			}
		}
	}
	for(int i=0; i<26; i++) {
		part1 += answers[i]>0;
		part2 += answers[i]==people;
	}
	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}
