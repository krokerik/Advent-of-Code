#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/01.txt"

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

	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}
