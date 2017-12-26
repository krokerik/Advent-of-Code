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
		int dx = 0,
		    dy = 0,
		    dz = 0;
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
			token = strtok(NULL, ",");
		}
		printf("part1: %d\n",getDistance(dx,dy,dz));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getDistance(int dx, int dy, int dz) {
	/*
	part1: n/s:  0, ne/sw:  3, se/nw: 0     3
	part1: n/s:  0, ne/sw:  0, se/nw: 0     0
	part1: n/s: -2, ne/sw:  2, se/nw: 0     2
	part1: n/s:  0, ne/sw: -3, se/nw: 2     3

	x = ne-sw
	y = se-nw
	z =  n-s

	n       = +dz
	ne      = +dx
	se      = +dy
	s       = -dz
	sw      = -dx
	nw      = -dy

	n  + sw = nw => dz>0, dx>0, dy--
	s  + ne = se => dz<0, dx>0, dy++
	s  + nw = sw => dz<0, dy<0, dx--
	n  + se = ne => dz>0, dy>0, dx++
	se + sw = s  => dy>0, dx<0, dz--
	ne + nw = n  => dx>0, dy<0, dz++
	
	*/
	int changed = 1;
	while(changed == 1) {
		changed = 0;
		if(dz>0 && dx>0) {
			dz--;
			dx--;
			dy--;
			changed = 1;
		}
		if(dz>0 && dy>0) {
			dz--;
			dy--;
			dx++;
			changed = 1;
		}
		if(dz<0 && dy<0) {
			dz++;
			dy++;
			dx--;
			changed = 1;
		}
		if(dz<0 && dx>0) {
			dz++;
			dx--;
			dy++;
			changed = 1;
		}
		if(dy>0 && dx<0) {
			dy--;
			dx++;
			dz--;
			changed = 1;
		}
		if(dx>0 && dy<0) {
			dx--;
			dy++;
			dz++;
			changed = 1;
		}
	}
	return abs(dx) + abs(dy) + abs(dz);
}
