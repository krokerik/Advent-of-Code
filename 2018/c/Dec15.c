#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/15.txt"

typedef enum type {
	elf,
	goblin
} type;

typedef struct position {
	int x;
	int y;
} position;

typedef struct creature {
	position pos;
	type type;
	int hp;
	int ap;
	int moved;
} creature;

creature* createCreature(char type, int x, int y);
int pos_compare(position lhs, position rhs);
int part1(char** map, int h, int w, creature** creatures, int n);
int getHPOfType(creature** list, int n, type t);
creature* getCreature(creature** creatures, int n);
int getUnmoved(creature** creatures, int n);
position getMove(creature* c, char ** map, int h, int w, creature** creatures, int n);
int positionCmp(const void * a, const void * b);
creature* getTarget(creature* c,creature** creatures,int n);
position getPath(position start, position goal, int** distance);
int part2(char** map, int h, int w, creature** creatures, int n);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	char ** map = malloc(sizeof(char*));
	int width   = 0;
	int height  = 0;
	creature ** creatures = malloc(sizeof(creature));
	int numCreatures      = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		int len = strlen(line);
		if(len>width) {
			width = len;
		}
		char* row = malloc(sizeof(char)*len);
		for(int i=0; i<len; i++) {
			int makeCreature = 0;
			switch(line[i]) {
				case '#':
					row[i] = '#';
					break;
				case 'E':
				case 'G':
					makeCreature = 1;
				default:
					row[i] = '.';
			}
			if(makeCreature) {
				numCreatures++;
				creatures = realloc(creatures,sizeof(creature *)*numCreatures);
				creatures[numCreatures-1] = createCreature(line[i],i,height);
			}
		}
		height++;
		map = realloc(map,sizeof(char*) * height);
		map[height-1] = row;
	}


	char** map2 = malloc(sizeof(char*)*height);
	for(int i=0; i<height; i++) {
		map2[i] = malloc(sizeof(char)*width);
		memcpy(map2[i],map[i],sizeof(char)*width);
	}
	creature** creatures2 = malloc(sizeof(creature*)*numCreatures);
	for(int i=0; i<numCreatures; i++) {
		creatures2[i] = malloc(sizeof(creature));
		memcpy(creatures2[i],creatures[i],sizeof(creature));
	}

	printf("part1: %d\n", part1(map, height, width, creatures, numCreatures));
	printf("part2: %d\n", part2(map2, height, width, creatures2, numCreatures));
	for(int i=0; i<numCreatures; i++) {
		free(creatures[i]);
	}
	for(int i=0; i<height; i++) {
		free(map[i]);
	}
	free(creatures);
	free(map);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

creature* createCreature(char type, int x, int y) {
	creature* c = malloc(sizeof(creature));
	position p = {x,y};
	c->pos = p;
	c->moved = 0;
	switch(type) {
		case 'E':
			c->type = elf;
			c->hp   = 200;
			c->ap   = 3;
			break;
		case 'G':
			c->type = goblin;
			c->hp   = 200;
			c->ap   = 3;
			break;
		default:
			fprintf(stderr,"Invalid type when creating new creature\n");
	}
	return c;
}

int pos_compare(position lhs, position rhs) {
	int equal = 0;
	if(lhs.x == rhs.x && lhs.y == rhs.y) {
		equal = 1;
	}
	return equal;
}

int part1(char** map, int h, int w, creature** creatures, int n) {
	int elfHP      = getHPOfType(creatures,n,elf);
	int goblinHP   = getHPOfType(creatures,n,goblin);
	int round      = 0;
	int turn       = 0;

	while(elfHP>0 && goblinHP>0) {
		turn++;
		//aquire
		creature* curr = getCreature(creatures,n);

		//move
		position move = getMove(curr,map,h,w,creatures,n);
		curr->pos = move;
		curr->moved = 1;

		//attack
		creature* target = getTarget(curr,creatures,n);
		if(target!=NULL) {
			target->hp -= curr->ap;
		}

		//reset
		elfHP    = getHPOfType(creatures,n,elf);
		goblinHP = getHPOfType(creatures,n,goblin);
		if(getUnmoved(creatures,n) == 0) {
			round++;
			for(int i=0; i<n; i++) {
				creatures[i]->moved = 0;
			}
			turn = 0;
		}
	}

	return elfHP>goblinHP ? elfHP*round : goblinHP*round;
}

int getHPOfType(creature** list, int n, type t) {
	int tot = 0;
	for(int i=0; i<n; i++) {
		if(list[i]->type == t && list[i]->hp > 0) {
			tot += list[i]->hp;
		}
	}
	return tot;
}

creature* getCreature(creature** creatures, int n) {
	creature* c = creatures[0];
	for(int i=0; i<n; i++) {
		if(c->moved == 1 || c->hp <= 0 ||
		   ((creatures[i]->pos.y < c->pos.y ||
		    (creatures[i]->pos.x < c->pos.x &&
		    creatures[i]->pos.y <= c->pos.y)) &&
		    creatures[i]->moved == 0 &&
		    creatures[i]->hp > 0)) {
		   	c = creatures[i];
		   }
	}
	if(c->hp<0) {
		fprintf(stderr,"returning dead character!\n");
		exit(EXIT_FAILURE);
	}
	return c;
}

int getUnmoved(creature** creatures, int n) {
	int unmoved = 0;
	for(int i=0; i<n; i++) {
		if(creatures[i]->moved == 0 &&
		   creatures[i]->hp > 0) {
			unmoved++;
		}
	}
	return unmoved;
}


//breadth first
position getMove(creature* c, char ** map, int h, int w, creature** creatures, int n) {
/*
 * Create distance graph
 */

	int** distance = malloc(sizeof(int*)*h);
	position* unvisited = malloc(sizeof(position));
	int numUnvisited = 1;
	int pos = 0;

	for(int y=0; y<h; y++) {
		distance[y] = malloc(sizeof(int)*w);
		for(int x=0; x<w; x++) {
			distance[y][x] = -1;
			if(map[y][x] == '#') {
				distance[y][x] = -2;
			}
		}
	}
	for(int i=0; i<n; i++) {
		if(creatures[i]->hp>0) {
			distance[creatures[i]->pos.y][creatures[i]->pos.x] = -2;
		}
	}


	position tmp = {c->pos.x, c->pos.y};
	unvisited[pos] = tmp;
	distance[c->pos.y][c->pos.x] = 0;
	while(pos<numUnvisited) {
		position curr = unvisited[pos];
		int x = curr.x;
		int y = curr.y;
		int ownDist = distance[y][x];
		pos++;
		position up    = {x,y-1};
		position down  = {x,y+1};
		position left  = {x-1,y};
		position right = {x+1,y};

		//check up
		if(distance[up.y][up.x] != -2) {
			if(distance[up.y][up.x] == -1) {
				distance[up.y][up.x] = ownDist+1;
				numUnvisited++;
				unvisited = realloc(unvisited,sizeof(position)*numUnvisited);
				unvisited[numUnvisited-1] = up;
			}
		}
		//check down
		if(distance[down.y][down.x] != -2) {
			if(distance[down.y][down.x] == -1) {
				distance[down.y][down.x] = ownDist+1;
				numUnvisited++;
				unvisited = realloc(unvisited,sizeof(position)*numUnvisited);
				unvisited[numUnvisited-1] = down;
			}
		}
		//check left
		if(distance[left.y][left.x] != -2) {
			if(distance[left.y][left.x] == -1) {
				distance[left.y][left.x] = ownDist+1;
				numUnvisited++;
				unvisited = realloc(unvisited,sizeof(position)*numUnvisited);
				unvisited[numUnvisited-1] = left;
			}
		}
		//check right
		if(distance[right.y][right.x] != -2) {
			if(distance[right.y][right.x] == -1) {
				distance[right.y][right.x] = ownDist+1;
				numUnvisited++;
				unvisited = realloc(unvisited,sizeof(position)*numUnvisited);
				unvisited[numUnvisited-1] = right;
			}
		}
	}

/*
 * search for candidate enemies.
 */
	position closest = {-1, -1};
	type enemy = !c->type;
	position* candidates = malloc(sizeof(position));
	int numCandidates = 0;

	for(int i=0; i<n; i++) {
		if(creatures[i]->type == enemy && creatures[i]->hp >0) {
			int x = creatures[i]->pos.x;
			int y = creatures[i]->pos.y;
			position up    = {x,y-1};
			position down  = {x,y+1};
			position left  = {x-1,y};
			position right = {x+1,y};

			if(distance[up.y][up.x] >= 0) {
				int isCandidate = 0;
				for(int j=0; j<numCandidates; j++) {
					if(candidates[j].x == up.x && candidates[j].y == up.y) {
						isCandidate = 1;
						break;
					}
				}
				if(isCandidate == 0) {
					numCandidates++;
					candidates = realloc(candidates,sizeof(position)*numCandidates);
					candidates[numCandidates-1] = up;
				}
			}

			if(distance[down.y][down.x] >= 0) {
				int isCandidate = 0;
				for(int j=0; j<numCandidates; j++) {
					if(candidates[j].x == down.x && candidates[j].y == down.y) {
						isCandidate = 1;
						break;
					}
				}
				if(isCandidate == 0) {
					numCandidates++;
					candidates = realloc(candidates,sizeof(position)*numCandidates);
					candidates[numCandidates-1] = down;
				}
			}

			if(distance[left.y][left.x] >= 0) {
				int isCandidate = 0;
				for(int j=0; j<numCandidates; j++) {
					if(candidates[j].x == left.x && candidates[j].y == left.y) {
						isCandidate = 1;
						break;
					}
				}
				if(isCandidate == 0) {
					numCandidates++;
					candidates = realloc(candidates,sizeof(position)*numCandidates);
					candidates[numCandidates-1] = left;
				}
			}

			if(distance[right.y][right.x] >= 0) {
				int isCandidate = 0;
				for(int j=0; j<numCandidates; j++) {
					if(candidates[j].x == right.x && candidates[j].y == right.y) {
						isCandidate = 1;
						break;
					}
				}
				if(isCandidate == 0) {
					numCandidates++;
					candidates = realloc(candidates,sizeof(position)*numCandidates);
					candidates[numCandidates-1] = right;
				}
			}

		}
	}

	int closestDist = INT_MAX;
	position* closeArr = malloc(sizeof(position));
	closeArr[0] = c->pos;
	int numClosest = 0;
	for(int i=0; i<numCandidates; i++) {
		if(distance[candidates[i].y][candidates[i].x] < closestDist) {
			free(closeArr);
			numClosest = 1;
			closeArr = malloc(sizeof(position));
			closeArr[0] = candidates[i];
			closestDist = distance[candidates[i].y][candidates[i].x];
		} else if(distance[candidates[i].y][candidates[i].x] == closestDist) {
			numClosest++;
			closeArr = realloc(closeArr, sizeof(position) * numClosest);
			closeArr[numClosest-1] = candidates[i];
		}
	}
	qsort(closeArr,numClosest,sizeof(position),positionCmp);
	closest = closeArr[0];

	position move = getPath(closest,c->pos,distance);

	free(candidates);
	free(closeArr);
	free(unvisited);
	for(int i=0; i<h; i++) {
		free(distance[i]);
	}
	free(distance);
	return move;
}

int positionCmp(const void * a, const void * b) {
	position lhs = *(position*) a;
	position rhs = *(position*) b;
	int res = lhs.y - rhs.y;
	if(res == 0) {
		res = lhs.x - rhs.x;
	}
	return res;
}

creature* getTarget(creature* c,creature** creatures,int n) {
	creature* t = NULL;
	int lowest = INT_MAX;
	type enemy = !c->type;

	position up    = {c->pos.x,c->pos.y-1};
	position left  = {c->pos.x-1,c->pos.y};
	position right = {c->pos.x+1,c->pos.y};
	position down  = {c->pos.x,c->pos.y+1};

	for(int i=0; i<n; i++) {
		if(creatures[i]->type==enemy && creatures[i]->hp>0) { //alive and enemy
			if(pos_compare(up,creatures[i]->pos) ||
			   pos_compare(left,creatures[i]->pos) ||
			   pos_compare(right,creatures[i]->pos) ||
			   pos_compare(down,creatures[i]->pos)) { //is next to player
			   	if(creatures[i]->hp<lowest) { //has lower hp
			   		lowest = creatures[i]->hp;
			   		t = creatures[i];
				} else if(creatures[i]->hp == lowest) { //has the same hp
			   		if(positionCmp((const void*)&creatures[i]->pos,(const void*)&t->pos)<0) { //is ahead in reading order
			   			lowest = creatures[i]->hp;
			   			t = creatures[i];
					}
				}
			}
		}
	}

	return t;
}

position getPath(position start, position goal, int** distance) {
	position curr   = start;
	int own         = distance[curr.y][curr.x];
	if(own == 1) {
		return start;
	}
	position up     = {curr.x,curr.y-1};
	position down   = {curr.x,curr.y+1};
	position left   = {curr.x-1,curr.y};
	position right  = {curr.x+1,curr.y};
	position* paths = malloc(sizeof(position));
	int nPath       = 0;
	paths[0]        = start;
	if(distance[up.y][up.x]>=0 && distance[up.y][up.x]==own-1) {
		nPath++;
		paths = realloc(paths,sizeof(position)*nPath);
		curr = getPath(up,goal,distance);
		paths[nPath-1] = curr;
	}
	if(distance[left.y][left.x]>=0 && distance[left.y][left.x]==own-1) {
		nPath++;
		paths = realloc(paths,sizeof(position)*nPath);
		curr = getPath(left,goal,distance);
		paths[nPath-1] = curr;
	}
	if(distance[right.y][right.x]>=0 && distance[right.y][right.x]==own-1) {
		nPath++;
		paths = realloc(paths,sizeof(position)*nPath);
		curr = getPath(right,goal,distance);
		paths[nPath-1] = curr;
	}
	if(distance[down.y][down.x]>=0 && distance[down.y][down.x]==own-1) {
		nPath++;
		paths = realloc(paths,sizeof(position)*nPath);
		curr = getPath(down,goal,distance);
		paths[nPath-1] = curr;
	}
	qsort(paths,nPath,sizeof(position),positionCmp);
	curr = paths[0];
	free(paths);
	return curr;
}

int part2(char** map, int h, int w, creature** creatures, int n) {
	int elfHP      = getHPOfType(creatures,n,elf);
	int goblinHP   = getHPOfType(creatures,n,goblin);
	int round      = 0;
	int turn       = 0;
	int boost      = 0;
	type winner    = goblin;

	while(winner != elf) {
		round = 0;
		turn  = 0;
		int numElves = 0;
		boost++;
		creature** clones = malloc(sizeof(creature*)*n);
		for(int i=0; i<n; i++) {
			clones[i] = malloc(sizeof(creature));
			memcpy(clones[i],creatures[i],sizeof(creature));
			if(clones[i]->type == elf) {
				clones[i]->ap += boost;
				numElves++;
			}
		}
		elfHP    = getHPOfType(clones,n,elf);
		goblinHP = getHPOfType(clones,n,goblin);
		while(elfHP>0 && goblinHP>0) {
			turn++;
			//aquire
			creature* curr = getCreature(clones,n);

			//move
			position move = getMove(curr,map,h,w,clones,n);
			curr->pos = move;
			curr->moved = 1;

			//attack
			creature* target = getTarget(curr,clones,n);
			if(target!=NULL) {
				target->hp -= curr->ap;
			}

			//reset
			elfHP    = getHPOfType(clones,n,elf);
			goblinHP = getHPOfType(clones,n,goblin);
			if(getUnmoved(clones,n) == 0) {
				round++;
				for(int i=0; i<n; i++) {
					clones[i]->moved = 0;
				}
				turn = 0;
			}
		}
		for(int i=0; i<n; i++) {
			if(clones[i]->type == elf && clones[i]->hp>0) {
				numElves--;
			}
		}
		if(numElves==0) {
			winner = elf;
		}
		free(clones);
	}
	return elfHP>goblinHP ? elfHP*round : goblinHP*round;
}
