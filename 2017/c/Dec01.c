#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"

int part1(char* seq);
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

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		printf("%s: %d %d\n\n", line, part1(line), part2(line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int part1(char* seq) {
	int res = 0, search = 0;
	for(int i=0; i<strlen(seq); i++) {
		int cur = seq[i] - '0';
		if(cur < 1 || cur > 9) {
			search = 0;
			continue; //ignore non-digits
		}
		if(cur==search) {
			res+=cur;
		}
		search = cur;
	}
	if(seq[0]-'0'==search) { //check circular loop.
		res+=search;
	}
	return res;
}

int part2(char* seq) {
	int res = 0, len = strlen(seq) , jump = len/2;
	for(int i=0; i<len; i++) {
		int cur = seq[i] - '0';
		int pos = (i+jump)%len;
		if(cur < 1 || cur > 9) continue; //ignore non-digits
		if(seq[i] == seq[pos]) {
			res += cur;
		}
	}

	return res;
}