#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/10.txt"

typedef struct point {
	int x;
	int y;
	int dx;
	int dy;
} point;

int isMessage(point* points, int numPoints);
void printPoints(point* points, int numPoints);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	point* points = malloc(sizeof(point));
	int numPoints = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char* temp = strstr(line,", ");

		int x  = atoi(line+10);
		int y  = atoi(temp+2);
		temp   = strstr(temp,"=<");
		int dx = atoi(temp+2);
		temp   = strstr(temp,", ");
		int dy = atoi(temp+2);

		point point = {x,y,dx,dy};
		numPoints++;
		points = realloc(points, sizeof(point)*numPoints);
		points[numPoints-1] = point;
	}

	int seconds = 0;
	while(!isMessage(points, numPoints)) {
		for(int i=0; i<numPoints; i++) {
			points[i].x += points[i].dx;
			points[i].y += points[i].dy;
		}
		seconds++;
	}
	printf("part1:\n");
	printPoints(points, numPoints);
	printf("part2: %d\n",seconds);

	free(points);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int isMessage(point* points, int numPoints) {
	int message = 0;

	int maxX = INT_MIN;
	int minX = INT_MAX;

	int maxY = INT_MIN;
	int minY = INT_MAX;

	int nexMaxX = INT_MIN;
	int nexMinX = INT_MAX;

	int nexMaxY = INT_MIN;
	int nexMinY = INT_MAX;


	for(int i=0; i<numPoints; i++) {
		int nexX = points[i].x + points[i].dx;
		int nexY = points[i].y + points[i].dy;
		if(points[i].x>maxX) {
			maxX = points[i].x;
		}
		if(points[i].x<minX) {
			minX = points[i].x;
		}
		if(points[i].y>maxY) {
			maxY = points[i].y;
		}
		if(points[i].y<minY) {
			minY = points[i].y;
		}

		if(nexX>nexMaxX) {
			nexMaxX = nexX;
		}
		if(nexX<nexMinX) {
			nexMinX = nexX;
		}
		if(nexY>nexMaxY) {
			nexMaxY = nexY;
		}
		if(nexY<nexMinY) {
			nexMinY = nexY;
		}

	}
	int height = maxX-minX;
	int width  = maxY-minY;
	int nextHeight = nexMaxX-nexMinX;
	int nextWidth  = nexMaxY-nexMinY;
	if(height<nextHeight && width<nextWidth) {
		message = 1;
	}
	return message;
}

void printPoints(point* points, int numPoints) {
	int maxX = INT_MIN;
	int maxY = INT_MIN;
	int minX = INT_MAX;
	int minY = INT_MAX;

	for(int i=0; i<numPoints; i++) {
		if(points[i].x>maxX) {
			maxX = points[i].x;
		}
		if(points[i].x<minX) {
			minX = points[i].x;
		}
		if(points[i].y>maxY) {
			maxY = points[i].y;
		}
		if(points[i].y<minY) {
			minY = points[i].y;
		}
	}
	int height = (maxY-minY)+1;
	int width  = (maxX-minX)+1;

	char message[height][width];
	memset(message, '.', sizeof(char)*height*width);

	for(int i=0; i<numPoints; i++) {
		message[points[i].y-minY][points[i].x-minX] = '#';
	}

	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
			printf("%c",message[i][j]);
		}
		printf("\n");
	}
}
