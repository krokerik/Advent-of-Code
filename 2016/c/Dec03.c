#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/03.txt"

int* toTriangle(char* sides);
int  isTriangle(int* triangle);
int numColTriangles(int** triangles);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	int numTriangles = 0, colTriangles = 0;
	int* triangle;
	int* columns[3];

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for (int i=0;getline(&line, &len, fp) != -1; i++) {
		triangle = toTriangle(line);
		columns[i%3] = triangle;
		numTriangles += isTriangle(triangle);
		if(i%3 == 2) {
			colTriangles += numColTriangles(columns);
			for(int j=0; j<3; j++)
				free(columns[j]);
		}
	}
	printf("num triangles:    %d\n",numTriangles);
	printf("num col triangle: %d\n",colTriangles);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}


int* toTriangle(char* sides) {
	int *triangle = malloc(sizeof(int)*3);
	char* tmpSide = strtok(sides, " ");

	for(int i=0; i<3 ; i++, tmpSide = strtok(NULL, " ")) {
		if(tmpSide != NULL) {
			triangle[i] = atoi(tmpSide);
		} else {
			fprintf(stderr,"Row %s does not have enough sides.\n",sides);
			triangle[i] = 0;
		}
	}

	return triangle;
}
int isTriangle(int* triangle) {
	int triangular = 0;
	triangular = triangle[0]+triangle[1]>triangle[2]?1:0;
	if(!triangular) return triangular;
	triangular = triangle[2]+triangle[0]>triangle[1]?1:0;
	if(!triangular) return triangular;
	triangular = triangle[1]+triangle[2]>triangle[0]?1:0;
	return triangular;
}

int numColTriangles(int** triangles) {
	int numTriangles = 0;
	int tmpTriangle[3];

	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			tmpTriangle[j] = triangles[j][i];
		}
		numTriangles += isTriangle(tmpTriangle);
	}

	return numTriangles;
}
