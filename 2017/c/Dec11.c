#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT "../input/11.txt"

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
		int dx  = 0,
		    dy  = 0,
		    dz  = 0,
		    max = 0;
		char *token;
		
		token = strtok(line, ",");
		while(token!=NULL) {
			if(strcmp(token,"n") == 0){
				dy++;
				dz--;
			} else if(strcmp(token,"ne") == 0){
				dx++;
				dz--;
			} else if(strcmp(token,"se") == 0){
				dx++;
				dy--;
			} else if(strcmp(token,"s") == 0){
				dz++;
				dy--;
			} else if(strcmp(token,"sw") == 0){
				dz++;
				dx--;
			} else if(strcmp(token,"nw") == 0){
				dy++;
				dx--;
			}
			int tmp = (abs(dx)+abs(dy)+abs(dz))/2;
			max = tmp>max?tmp:max;
			token = strtok(NULL, ",");
		}
		printf("part1: %d\n",(abs(dx)+abs(dy)+abs(dz))/2);
		printf("part2: %d\n",max);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}
