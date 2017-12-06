#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/06.txt"
#define SIZE 16

int part1(long* memory);
int part2(long* memory);
int inSet(long* memory, long** history, int len);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	char* end;
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char* token = strtok(line,"\t");
		long memory[SIZE];
		int pos = 0;
		while(token != NULL && pos<SIZE) {
			memory[pos++] = strtol(token,&end,10);
			token = strtok(NULL, "\t");
		}
		printf("part 1: %d\n",part1(memory));
		printf("part 2: %d\n",part2(memory));
	}
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int part1(long* memory) {
	int cycles = 0;
	long** history = malloc(sizeof(long*)*2);
	history[0] = malloc(sizeof(long) * SIZE);

	for(int i=0; i<SIZE; i++) {
		history[0][i] = memory[i];
	}

	while(inSet(memory,history,cycles) == 0) {
		int pos = 0;

		for(int i=0; i<SIZE; i++) {
			if(memory[i] > memory[pos]) {
				pos = i;
			}
		}
		int hand = memory[pos];
		memory[pos] = 0;
		while(hand > 0) {
			pos++;
			pos = pos==SIZE ? 0 : pos ;
			memory[pos]++;
			hand--;
		}
		cycles++;
		history = realloc(history, sizeof(long) * (cycles+1));
		history[cycles] = malloc(sizeof(long) * SIZE);

		for(int i=0; i<SIZE; i++) {
			history[cycles][i] = memory[i];
		}
	}

	for(int i=0; i<=cycles; i++) {
		free(history[i]);
	}
	free(history);

	return cycles;
}

int part2(long* memory) {
	int cycles = 0;
	long** history = malloc(sizeof(long*)*2);
	history[0] = malloc(sizeof(long) * SIZE);

	history[0] = memcpy(history[0],memory,sizeof(long)*SIZE);

	while(inSet(memory,history,cycles) == 0) {
		int pos = 0;

		for(int i=0; i<SIZE; i++) {
			if(memory[i] > memory[pos]) {
				pos = i;
			}
		}
		int hand = memory[pos];
		memory[pos] = 0;
		while(hand > 0) {
			pos++;
			pos = pos==SIZE ? 0 : pos ;
			memory[pos]++;
			hand--;
		}
		cycles++;
		history = realloc(history, sizeof(long) * (cycles+1));
		history[cycles] = malloc(sizeof(long) * SIZE);

		for(int i=0; i<SIZE; i++) {
			history[cycles][i] = memory[i];
		}
	}

	int len = 0;
	for(int i=0; i<cycles; i++) {
		int num = 0;
		for(int j=0; j<SIZE; j++) {
			if(history[i][j] == memory[j]) {
				num++;
			}
		}
		if(num == SIZE) {
			len = cycles-i;
		}
		free(history[i]);
	}

	free(history);

	return len;
}

int inSet(long* memory, long** history, int len) {
	int res = 0;
	for(int i=0; i<len && res == 0; i++) {
		int num = 0;
		for(int j=0; j<SIZE; j++) {
			if(res == 0 && history[i][j] == memory[j]) {
				num++;
			}
		}
		if(num == SIZE) {
			res = 1;
			break;
		}
	}
	return res;
}