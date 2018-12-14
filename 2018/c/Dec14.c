#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/14.txt"

long part1(int* recipes, int numRecipes, int goal);
int part2(int* recipes, int numRecipes, char* goal);
int getPos(int* arr1,int* arr2,int len1,int len2);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		int* recipes = malloc(sizeof(int)*2);
		int numRecipes = 2;
		recipes[0] = 3;
		recipes[1] = 7;
		printf("%s\n",line);
		int goal = atoi(line);
		printf("part1: %010ld\n", part1(recipes,numRecipes,goal));
		recipes = malloc(sizeof(int)*2);
		recipes[0] = 3;
		recipes[1] = 7;
		printf("part2: %d\n", part2(recipes,numRecipes,line));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long part1(int* recipes, int numRecipes, int goal) {
	long score = 0;
	int workers[2] = {0,1};
	while(numRecipes < goal+10) {

		int scores[2] = {recipes[workers[0]], recipes[workers[1]]};
		int tot = scores[0] + scores[1];
		int second = tot%10;
		int first  = (tot/10)%10;


		if(first == 0) {
			numRecipes += 1;
			recipes = realloc(recipes,sizeof(int)*numRecipes);
			recipes[numRecipes-1] = second;
		} else {
			numRecipes += 2;
			recipes = realloc(recipes,sizeof(int)*numRecipes);
			recipes[numRecipes-2] = first;
			recipes[numRecipes-1] = second;

		}
		workers[0] = (1+scores[0]+workers[0])%numRecipes;
		workers[1] = (1+scores[1]+workers[1])%numRecipes;
	}

	long times = 1000000000;
	for(int i=goal; i<goal+10; i++) {
		long tot = recipes[i]*times;
		score += tot;
		times /= 10;
	}
	free(recipes);
	return score;
}

int part2(int* recipes, int numRecipes, char* goal) {
	int workers[2] = {0,1};
	int nDigits = strlen(goal);
	int goalArr[nDigits];
	for(int i=0; i<nDigits; i++) {
		goalArr[i] = goal[i]-'0';
	}

	while(getPos(recipes+numRecipes-(nDigits+1),goalArr,nDigits+1,nDigits) == -1) {
		int scores[2] = {recipes[workers[0]], recipes[workers[1]]};
		int tot = scores[0] + scores[1];
		int second = tot%10;
		int first  = (tot/10)%10;


		if(first == 0) {
			numRecipes += 1;
			recipes = realloc(recipes,sizeof(int)*numRecipes);
			recipes[numRecipes-1] = second;
		} else {
			numRecipes += 2;
			recipes = realloc(recipes,sizeof(int)*numRecipes);
			recipes[numRecipes-2] = first;
			recipes[numRecipes-1] = second;

		}
		workers[0] = (1+scores[0]+workers[0])%numRecipes;
		workers[1] = (1+scores[1]+workers[1])%numRecipes;
	}
	return getPos(recipes,goalArr,numRecipes,nDigits);
}

// gets the starting position of the second array in the first array, returns
// -1 if the second array is not part of the first array.
int getPos(int* arr1,int* arr2,int len1,int len2) {
	int pos = -1;
	if(len2>len1) {
		return -1;
	}
	for(int i=0; i<len1-len2; i++) {
		int score = 0;
		for(int j=0; j<len2; j++) {
			if(arr1[i+j]==arr2[j]) {
				score++;
			}
		}
		if(score == len2) {
			pos = i;
			break;
		}
	}
	return pos;
}
