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
		printf("%s%d %d\n\n", line, part1(line), part2(line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int part1(char* seq) {
	int res = 0, search = 0;
	for(int i=0; i<strlen(seq); i++) {
		int cur = seq[i] - '0';
		if(cur < 1 || cur > 9) continue; //ignore non-digits
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

// breaks if input doesn't end with a line feed
int part2(char* seq) {
	int res = 0, search = 0, len = strlen(seq)-2 , jump = len/2;
	for(int i=0; i<len; i++) {
		int pos = (i+jump)%len;
		if(seq[i] == seq[pos]) {
			res += seq[i]-'0';
		}
	}

	return res;
}