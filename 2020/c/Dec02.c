#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/02.txt"

// struct not really needed, built it thinking part2 might need it.
typedef struct Entry {
	int least;
	int most;
	char target;
	char* password;
} Entry;

int part1isValid(Entry entry);
int part2isValid(Entry entry);

int main() {
	FILE * fp;
	char * line    = NULL;
	size_t len     = 0;
	int entriesLen = 1;
	int part1      = 0;
	int part2      = 0;
	Entry * entries  = malloc(entriesLen * sizeof(Entry));

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}


	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char * pos;
		int least = (int)strtol(line, &pos, 10);
		int most  = (int)strtol(pos+1, &pos, 10);
		char target = pos[1];
		Entry entry = {least,
		               most,
		               target,
		               pos+4};
		part1 += part1isValid(entry);
		part2 += part2isValid(entry);
	}

	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);
	fclose(fp);
	free(line);
	free(entries);
	exit(EXIT_SUCCESS);
}

int part1isValid(Entry entry) {
	int num = 0;
	int len = strlen(entry.password);
	for(int i=0; i<len; i++){
		if(entry.password[i] == entry.target) {
			num++;
		}
	}
	return num>=entry.least && num<=entry.most;
}

int part2isValid(Entry entry) {
	return !(entry.password[entry.least-1] == entry.target) != !(entry.password[entry.most-1] == entry.target);
}
