#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"

int captcha(char* seq);

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
		printf("%s%d\n\n", line, captcha(line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int captcha(char* seq) {
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