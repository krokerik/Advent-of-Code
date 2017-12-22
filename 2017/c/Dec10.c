#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/10.txt"

int* genCircle(int len);
void reverse(int* circle, int start, int end, int len, int iter);

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
		int circleSize = 256,
		    *circle   = genCircle(circleSize),
		    pos      = 0,
		    skipSize = 0;
		const char s[3] = ", ";
		char *token = strtok(line,s),
		     *end;

		while(token != NULL) {
			int len = strtol(token,&end,10);
			if(len>1)
				reverse(circle,pos,(pos+len-1)%circleSize,circleSize,0);
			pos += len + (skipSize++);
			pos = pos%circleSize;
			token = strtok(NULL, s);
		}

		printf("part1: %d\n",(circle[0]*circle[1]));
		free(circle);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int* genCircle(int len) {
	int* circle = malloc(sizeof(int) * len);
	for(int i = 0; i<len; i++) {
		circle[i] = i;
	}
	return circle;
}

void reverse(int* circle, int start, int end, int len, int iter) {
	if(iter > 0 && (start == end || start == (end+1)%len)) return;
	int tmp       = circle[start];
	circle[start] = circle[end];
	circle[end]   = tmp;
	if(end == 0) end = len;
	reverse(circle, (start+1)%len,end-1,len,iter+1);
}
