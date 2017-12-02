#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/02.txt"

long part1(char* seq);
int part2(char* seq);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	long tot1 = 0;
	int tot2 = 0;
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		tot1+=part1(line);
		tot2+=part2(line);
	}
	printf("part1: %ld\n",tot1);
	printf("part2: %d\n",tot2);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long part1(char* seq) {
	long smallest = LONG_MAX, biggest = LONG_MIN;
	char* end;

	for (long i = strtol(seq, &end, 10); seq != end; i = strtol(seq, &end, 10)){
		if(i<smallest) {
			smallest = i;
		}
		if(i>biggest) {
			biggest = i;
		}
		seq = end;
	}

	return biggest - smallest;
}

int part2(char* seq) {
	return 0;
}