#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT "../input/11.txt"

int getDistance(int dx, int dy, int dz);

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
			dz++;
			} else if(strcmp(token,"ne") == 0){
			dx++;
			} else if(strcmp(token,"se") == 0){
			dy++;
			} else if(strcmp(token,"s") == 0){
			dz--;
			} else if(strcmp(token,"sw") == 0){
			dx--;
			} else if(strcmp(token,"nw") == 0){
			dy--;
			}

			int tmp = getDistance(dx,dy,dz);
			max = tmp>max?tmp:max;

			token = strtok(NULL, ",");
		}
		printf("part1: %d\n",getDistance(dx,dy,dz));
		printf("part2: %d\n",max);
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getDistance(int dx, int dy, int dz) {
/* x = ne-sw
 * y = se-nw
 * z =  n-s
 * 
 * n       = +dz
 * ne      = +dx
 * se      = +dy
 * s       = -dz
 * sw      = -dx
 * nw      = -dy
 * 
 * n  + sw = nw => dz>0, dx<0, dy--
 * s  + ne = se => dz<0, dx>0, dy++
 * s  + nw = sw => dz<0, dy<0, dx--
 * n  + se = ne => dz>0, dy>0, dx++
 * se + sw = s  => dy>0, dx<0, dz--
 * ne + nw = n  => dx>0, dy<0, dz++
 */

	if(dz>0 && dx<0) {
		int tmp = abs(dz)<abs(dx)?abs(dz):abs(dx);
		dz -= tmp;
		dx += tmp;
		dy -= tmp;
	}
	if(dz>0 && dy>0) {
		int tmp = abs(dz)<abs(dy)?abs(dz):abs(dy);
		dz -= tmp;
		dy -= tmp;
		dx += tmp;
	}
	if(dz<0 && dy<0) {
		int tmp = abs(dz)<abs(dy)?abs(dz):abs(dy);
		dz += tmp;
		dy += tmp;
		dx -= tmp;
	}
	if(dz<0 && dx>0) {
		int tmp = abs(dz)<abs(dx)?abs(dz):abs(dx);
		dz += tmp;
		dx -= tmp;
		dy += tmp;
	}
	if(dy>0 && dx<0) {
		int tmp = abs(dy)<abs(dx)?abs(dy):abs(dx);
		dy -= tmp;
		dx += tmp;
		dz -= tmp;
	}
	if(dx>0 && dy<0) {
		int tmp = abs(dx)<abs(dy)?abs(dx):abs(dy);
		dx -= tmp;
		dy += tmp;
		dz += tmp;
	}

	return abs(dx) + abs(dy) + abs(dz);
}
