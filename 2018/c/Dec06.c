#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/06.txt"
#define PART2LIMIT 10000

typedef struct point {
	int id;
	int x;
	int y;
	int distance;
} point;

int getDistance(int x1, int y1, int x2, int y2);

int main() {
	FILE * fp;
	char * line      = NULL;
	size_t len       = 0;
	int max_x        = 0;
	int max_y        = 0;
	point* points    = malloc(sizeof(point));
	int numPoints    = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		int x      = atoi(line);
		char* temp = strstr(line,", ");
		int y      = atoi(temp+2);

		if(x > max_x) {
			max_x = x;
		}
		if(y > max_y) {
			max_y = y;
		}
		point point = {numPoints, x, y, 0};
		numPoints++;
		points = realloc(points,numPoints * sizeof(point));
		points[numPoints-1] = point;
	}
	max_x ++;
	max_y ++;

	int biggestArea = 0;
	int part2Area = 0;
	for(int x=0; x<max_x; x++) {
		for(int y=0; y<max_y; y++) {
			int closest     = INT_MAX,
			    closestID   = -1,
			    total       = 0;
			for(int i=0; i<numPoints; i++) {
				int dist = getDistance(x,y,points[i].x,points[i].y);
				if(dist==closest) {
					closestID = -1;
				} else if (dist<closest) {
					closest = dist;
					closestID = points[i].id;
				}
				total += dist;
			}
			if(closestID!=-1 && points[closestID].distance !=-1) {
				points[closestID].distance++;
			}
			if(closestID!=-1 && (x==0 || y==0 || x==max_x-1 || y==max_y-1)) {
				points[closestID].distance = -1;
			}
			if(total<PART2LIMIT) {
				part2Area++;
			}
		}
	}

	for(int i=0; i<numPoints; i++) {
		if(points[i].distance>biggestArea) {
			biggestArea = points[i].distance;
		}
	}

	printf("part1: %d\n",biggestArea);
	printf("part2: %d\n",part2Area);

	free(points);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getDistance(int x1, int y1, int x2, int y2) {
	return abs(x1-x2) + abs(y1-y2);
}
