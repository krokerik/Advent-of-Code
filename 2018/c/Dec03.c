#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/03.txt"

typedef struct Claim {
	int id;
	int x;
	int y;
	int width;
	int height;
} Claim;

int advanceTo(char * string, char c);
int part1(Claim* claims, int len, int width, int height);
int part2(Claim* claims, int len);
int overlaps(Claim c1, Claim c2);

int main() {
	FILE * fp;
	char * line   = NULL;
	size_t len    = 0;
	Claim * claims = malloc(sizeof(Claim));
	int claimLen = 0;
	int width  = 0;
	int height = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		Claim claim = {atoi(line + 1),
		               atoi(line + advanceTo(line,'@') + 1),
		               atoi(line + advanceTo(line,',') + 1),
		               atoi(line + advanceTo(line,':') + 2),
		               atoi(line + advanceTo(line,'x') + 1)};

		claimLen++;
		claims = realloc(claims, sizeof(Claim)*claimLen);
		claims[claimLen-1] = claim;
		if(claim.x+claim.width>width) {
			width = claim.x+claim.width;
		}
		if(claim.y+claim.height>height) {
			height = claim.y+claim.height;
		}
	}

	printf("part 1: %d\n",part1(claims,claimLen,width,height));
	printf("part 2: %d\n",part2(claims,claimLen));
	free(claims);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int advanceTo(char * string, char c) {
	int pos = -1;
	int len = strlen(string);
	for(int i = 0; i<len; i++) {
		if(string[i]==c) {
			pos = i;
			break;
		}
	}
	return pos;
}

int part1(Claim* claims, int len, int width, int height) {
	int paper[width][height];
	int overlapping = 0;
	memset(paper, 0, sizeof(paper));

	//perform every claim
	for(int i=0; i<len; i++) {
		for(int j=claims[i].x; j<claims[i].x+claims[i].width; j++) {
			for(int k=claims[i].y; k<claims[i].y+claims[i].height; k++) {
				paper[j][k]++;
			}
		}
	}

	//count overlaps
	for(int i=0; i<width; i++) {
		for(int j=0; j<height; j++) {
			if(paper[i][j]>1) {
				overlapping++;
			}
		}
	}
	return overlapping;
}

int part2(Claim* claims, int len) {
	int id = -1;
	for(int i=0; i<len; i++) {
		id = claims[i].id;
		for(int j=0; j<len; j++) {
			if(i!=j && overlaps(claims[i],claims[j])) {
				id = -1;
			}
		}
		if(id!=-1) {
			break;
		}
	}
	return id;
}

int overlaps(Claim c1, Claim c2) {
	int left1 = c1.x, right1 = c1.x+c1.width, top1 = c1.y, bot1 = c1.y+c1.height;
	int left2 = c2.x, right2 = c2.x+c2.width, top2 = c2.y, bot2 = c2.y+c2.height;
	if(left1 >= right2 || left2 >= right1) {
		return 0;
	} else if(top1 >= bot2 || top2 >= bot1) {
		return 0;
	}
	return 1;
}
