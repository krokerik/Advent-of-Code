#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/13.txt"

typedef struct train {
	int x;
	int y;
	int dx;
	int dy;
	int turnCycle;
	int moved;
} train;

int isCollision(train* trains, int numTrains);
int getTrain(train* trains, int numTrains);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;

	char** map = malloc(sizeof(char*));
	train* trains = malloc(sizeof(train));

	int mapHeight = 0;
	int numTrains = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		int length = strlen(line);

		mapHeight++;
		map = realloc(map, sizeof(char*)*mapHeight);
		map[mapHeight-1] = malloc(sizeof(char)*length);
		for(int i=0; i<length; i++) {
			if(line[i] == '|' ||
			   line[i] == '\\' ||
			   line[i] == '/' ||
			   line[i] == '-' ||
			   line[i] == '+') {
				map[mapHeight-1][i] = line[i];
			} else if(line[i] == 'v' ||
			          line[i] == '^' ||
			          line[i] == '>' ||
			          line[i] == '<') {
				numTrains++;
				trains = realloc(trains,sizeof(train)*numTrains);
				int x         = i;
				int y         = mapHeight-1;
				int dx        = 0;
				int dy        = 0;
				int turnCycle = 0;
				int moved     = 0;
				if(line[i] == 'v') {
					dx = 0;
					dy = 1;
				} else if(line[i] == '^') {
					dx = 0;
					dy = -1;
				} else if(line[i] == '>') {
					dx = 1;
					dy = 0;
				} else if(line[i] == '<') {
					dx = -1;
					dy = 0;
				}
				if(dy != 0) {
					map[mapHeight-1][i] = '|';
				} else {
					map[mapHeight-1][i] = '-';
				}
				train train = {
					x,
					y,
					dx,
					dy,
					turnCycle,
					moved
				};
				trains[numTrains-1] = train;
			}
		}
	}

	int tick=0;
	int turn=0;
	int firstCrash = 0;
	while(numTrains>1) {
		tick++;
		int cur = getTrain(trains, numTrains);

		trains[cur].x    += trains[cur].dx;
		trains[cur].y    += trains[cur].dy;
		trains[cur].moved = 1;

		char pos = map[trains[cur].y][trains[cur].x];

		if(pos == '/') {
			if(trains[cur].dx == 1) {
				trains[cur].dx = 0;
				trains[cur].dy = -1;
			} else if(trains[cur].dx == -1) {
				trains[cur].dx = 0;
				trains[cur].dy = 1;
			} else if(trains[cur].dy == 1) {
				trains[cur].dx = -1;
				trains[cur].dy = 0;
			} else if(trains[cur].dy == -1) {
				trains[cur].dx = 1;
				trains[cur].dy = 0;
			}
		} else if(pos == '\\') {
			if(trains[cur].dx == 1) {//right
				trains[cur].dx = 0;
				trains[cur].dy = 1;//turn down
			} else if(trains[cur].dx == -1) {//left
				trains[cur].dx = 0;
				trains[cur].dy = -1;//turn up
			} else if(trains[cur].dy == 1) {//down
				trains[cur].dx = 1;//turn right
				trains[cur].dy = 0;
			} else if(trains[cur].dy == -1) {//up
				trains[cur].dx = -1;//turn left
				trains[cur].dy = 0;
			}
		} else if(pos == '+') {
			if(trains[cur].dx == 1) {//right
				switch(trains[cur].turnCycle) {
					case 0:
						//turn up
						trains[cur].dx = 0;
						trains[cur].dy = -1;
						break;
					case 1:
						//go straight
						break;
					case 2:
						//turn down
						trains[cur].dx = 0;
						trains[cur].dy = 1;
						break;
					default:
						perror("invalid turn cycle!\n");
						exit(EXIT_FAILURE);
				}
			} else if(trains[cur].dx == -1) {//left
				switch(trains[cur].turnCycle) {
					case 0:
						//turn down
						trains[cur].dx = 0;
						trains[cur].dy = 1;
						break;
					case 1:
						//go straight
						break;
					case 2:
						//turn up
						trains[cur].dx = 0;
						trains[cur].dy = -1;
						break;
					default:
						perror("invalid turn cycle!\n");
						exit(EXIT_FAILURE);
				}
			} else if(trains[cur].dy == 1) {//down
				switch(trains[cur].turnCycle) {
					case 0:
						//turn right
						trains[cur].dx = 1;
						trains[cur].dy = 0;
						break;
					case 1:
						//go straight
						break;
					case 2:
						//turn left
						trains[cur].dx = -1;
						trains[cur].dy = 0;
						break;
					default:
						perror("invalid turn cycle!\n");
						exit(EXIT_FAILURE);
				}
			} else if(trains[cur].dy == -1) {//up
				switch(trains[cur].turnCycle) {
					case 0:
						//turn left
						trains[cur].dx = -1;
						trains[cur].dy = 0;
						break;
					case 1:
						//go straight
						break;
					case 2:
						//turn right
						trains[cur].dx = 1;
						trains[cur].dy = 0;
						break;
					default:
						fprintf(stderr,"invalid turn cycle %d!\n",trains[cur].turnCycle);
						exit(EXIT_FAILURE);
				}
			}
			trains[cur].turnCycle++;
			if(trains[cur].turnCycle > 2) {
				trains[cur].turnCycle = 0;
			}
		}

		if(tick >= numTrains) {
			tick = 0;
			turn++;
			for(int i=0; i<numTrains; i++) {
				trains[i].moved = 0;
			}
		}
		for(int i=0; i<numTrains; i++) {
			for(int j=i+1; j<numTrains; j++) {
				if(trains[i].x == trains[j].x &&
				   trains[i].y == trains[j].y) {
					if(firstCrash == 0) {
						firstCrash = 1;
						printf("part1: %d,%d\n",trains[i].x,trains[i].y);
					}
					//remove i and j
					numTrains -= 2;
					tick -= trains[i].moved + trains[j].moved;
					train* tmp = malloc(sizeof(train)*numTrains);
					int offset=0;
					for(int k=0; k<numTrains+2; k++) {
						if(k!=i && k!=j) {
							tmp[k-offset] = trains[k];
						}else if(k==i || k==j) {
							offset++;
						}
					}
					free(trains);
					trains = tmp;
				}
			}
		}
	}

	printf("part2: %d,%d\n",trains[0].x,trains[0].y);

	for(int i=0; i<mapHeight; i++) {
		free(map[i]);
	}
	free(map);
	free(trains);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int isCollision(train* trains, int numTrains) {
	int collision = 0;
	for(int i=0; i<numTrains; i++) {
		for(int j=i+1; j<numTrains; j++) {
			if(trains[i].x == trains[j].x &&
			   trains[i].y == trains[j].y) {
				collision = 1;
				break;
			}
		}
	}
	return collision;
}

int getTrain(train* trains, int numTrains) {
	int top = 0;
	for(int i=1; i<numTrains; i++) {
		if(trains[top].moved == 1) {
			top = i;
		}else if(trains[i].moved == 0 &&
		         trains[i].y     < trains[top].y &&
		         trains[i].x     < trains[top].x) {
			top = i;
		}
	}
	return top;
}
