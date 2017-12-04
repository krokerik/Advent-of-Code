#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INPUT "../input/03.txt"

long part1(char* seq);
long part2(char* seq);
int** getSpiral(int width);

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
		printf("%s: %ld\n",line,part1(line));
		printf("%s: %ld\n",line,part2(line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long part1(char* seq) {
	char* end;
	long input = strtol(seq,&end,10),
	     total = 0,
	     width = 0;
	
	int i=1, lvl;
	do {
		lvl = 4*pow(i,2) - 4*i + 1;
		i++;
	} while(lvl < input);
	i-=2;
	width = (i*2)+1;
	int** spiral = getSpiral(width);

	for(i=0; i<width; i++){
		for(int j=0; j<width; j++) {
			if(spiral[i][j] == input) {
				int dx = abs((width/2)-i);
				int dy = abs((width/2)-j);
				total = dx+dy;
			}
		}
		free(spiral[i]);
	}
	free(spiral);
	return total;
}

long part2(char* seq) {
	char* end;
	long input = strtol(seq,&end,10),
	     total = 0,
	     width = 0;
	
	int i=1, lvl;
	do {
		lvl = 4*pow(i,2) - 4*i + 1;
		i++;
	} while(lvl < input);
	i-=2;
	width = (i*2)+1;
	int** spiral = (int **)malloc(width * sizeof(int *));
	int x = floor(width/2), y = floor(width/2);
	int dx = 1, dy = 0;
	int level = 0;
	
	for(int i=0; i<width; i++) {
		spiral[i] = malloc(width * sizeof(int));
		for(int j=0; j<width; j++) {
			spiral[i][j] = -1;
		}
	}
	for(int i=1; i<=width*width; i++) {
		if(i==1) {
			spiral[y][x] = 1;
		} else {
			long sum = 0;
			for(int j = y-1; j <= y+1; j++) {
				if(j>=0 && j<width) {
					for(int k = x-1; k <= x+1; k++) {
						if(k>=0 && k<width && spiral[j][k]!=-1) {
							sum += spiral[j][k];
						}
					}
				}
			}
			spiral[y][x] = sum;
			if(sum > input) {
				total = sum;
				break;
			}
		}
		x += dx;
		y += dy;
		if(sqrt(i) == floor(sqrt(i)) && ((int)floor(sqrt(i)))%2==1) {
			//bottom right corner.
			level++;
			dx = 0;
			dy = -1;
		} else if(i == 4*pow(level,2) - 2*level) {
			//top right corner.
			dx = -1;
			dy = 0;
		} else if(i == 4*pow(level,2)) {
			//top left corner.
			dx = 0;
			dy = 1;
		} else if(i == 4*pow(level,2) + 2*level) {
			//bottom left corner.
			dx = 1;
			dy = 0;
		}
	}
	return total;
}

int** getSpiral(int width) {
	int** spiral = (int **)malloc(width * sizeof(int *));
	int x = floor(width/2), y = floor(width/2);
	int dx = 1, dy = 0;
	int level = 0;
	for(int i=0; i<width; i++) {
		spiral[i] = malloc(width * sizeof(int));
	}
	for(int i=1; i<=width*width; i++) {
		spiral[y][x] = i;
		x += dx;
		y += dy;
		if(sqrt(i) == floor(sqrt(i)) && ((int)floor(sqrt(i)))%2==1) {
			//bottom right corner.
			level++;
			dx = 0;
			dy = -1;
		} else if(i == 4*pow(level,2) - 2*level) {
			//top right corner.
			dx = -1;
			dy = 0;
		} else if(i == 4*pow(level,2)) {
			//top left corner.
			dx = 0;
			dy = 1;
		} else if(i == 4*pow(level,2) + 2*level) {
			//bottom left corner.
			dx = 1;
			dy = 0;
		}
	}
	return spiral;
}