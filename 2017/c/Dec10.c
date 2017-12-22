#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/10.txt"

int* genCircle(int len);
void reverse(int* circle, int start, int end, int len, int iter);
int* densify(int* sparse, int len);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}
	int circleSize    = 256,
	    *circle       = genCircle(circleSize),
	    *instructions = NULL,
	    numInstr      = 0;
		
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		while(line[numInstr]!='\0') {
			if(instructions == NULL) {
				instructions = malloc(sizeof(int));
			} else {
				instructions = realloc(instructions,sizeof(int)*(numInstr+1));
			}
			instructions[numInstr] = line[numInstr];
			numInstr++;
		}
	}
	instructions = realloc(instructions,sizeof(int)*(numInstr+5));
	instructions[numInstr++] = 17;
	instructions[numInstr++] = 31;
	instructions[numInstr++] = 73;
	instructions[numInstr++] = 47;
	instructions[numInstr++] = 23;

	int skipSize = 0,
	    pos      = 0;
	for(int i=0; i<64; i++) {
		for(int j=0; j<numInstr; j++) {
			int len = instructions[j];
			if(len>1)
				reverse(circle,pos,(pos+len-1)%circleSize,circleSize,0);
			pos += len + (skipSize++);
			pos = pos%circleSize;
		}
	}

	int* denseHash = densify(circle, circleSize);
	for(int i=0; i<circleSize/16; i++) {
		printf("%02x",denseHash[i]);
	}
	printf("\n");

	free(circle);
	free(instructions);
	free(denseHash);
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

int* densify(int* sparse, int len) {
	int* denseArray = malloc(sizeof(int) * len/16);
	for(int i=0; i<len/16; i++) {
		denseArray[i] = 0;
	}
	for(int i=0; i<len; i++) {
		denseArray[i/16] ^= sparse[i];
	}

	return denseArray;
}
