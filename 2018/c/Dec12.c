#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/12.txt"

#define PART1 20
#define PART2 50000000000
#define LINEARLENGTH 10

typedef struct rule {
	char pattern[6];
	char becomes;
} rule;

typedef struct pot {
	int index;
	char content;
	char nextGen;
	struct pot * next;
	struct pot * prev;
} pot;

long getScore(pot* root);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	rule * rules = malloc(sizeof(rule));
	int numRules = 0;
	int lineNum = 0;
	pot* first = NULL;
	pot* last = NULL;
	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		if(lineNum==0) {
			first = malloc(sizeof(pot));
			first->prev = NULL;
			first->next = NULL;
			first->content = '.';
			first->index = -2;
			last = first;
			pot* tmp = malloc(sizeof(pot));
			tmp->prev = last;
			tmp->next = NULL;
			tmp->content = '.';
			tmp->index = -1;
			first->next = tmp;
			last = tmp;
			int numPlants = strlen(line+15);
			for(int i=0; i<numPlants; i++) {
				pot* plant = malloc(sizeof(pot));
				plant->index = i;
				plant->content = line[15+i];
				plant->next = NULL;
				if(first == NULL) {
					first = plant;
					first->prev = NULL;
					last = first;
				} else {
					last->next = plant;
					plant->prev = last;
					last = plant;
				}
			}
			tmp = malloc(sizeof(pot));
			tmp->index = last->index+1;
			tmp->prev = last;
			tmp->content = '.';
			tmp->next = NULL;
			last->next = tmp;
			last = tmp;

			tmp = malloc(sizeof(pot));
			tmp->index = last->index+1;
			tmp->prev = last;
			tmp->content = '.';
			tmp->next = NULL;
			last->next = tmp;
			last = tmp;
		} else if(lineNum>1) {
			rule rule;
			for(int i=0; i<5; i++) {
				rule.pattern[i] = line[i];
			}
			rule.pattern[5] = '\0';
			rule.becomes = line[strlen(line)-1];

			numRules++;
			rules = realloc(rules, sizeof(rule)*numRules);
			rules[numRules-1] = rule;
		}
		lineNum++;
	}

	long score = getScore(first);
	int prevScore = score;
	long generation = 0;
	int scoreDiffs[LINEARLENGTH] = {0};
	int diffLen = 0;
	while(generation<PART2) {
		prevScore = score;
		pot* cur = first;
		while(cur!=NULL) {
			char current[6];

			if(cur->prev!=NULL && cur->prev->prev!=NULL) {
				current[0] = cur->prev->prev->content;
			} else {
				current[0] = '.';
			}
			if(cur->prev!=NULL) {
				current[1] = cur->prev->content;
			} else {
				current[1] = '.';
			}
			current[2] = cur->content;
			if(cur->next!=NULL) {
				current[3] = cur->next->content;
			} else {
				current[3] = '.';
			}
			if(cur->next!=NULL && cur->next->next!=NULL) {
				current[4] = cur->next->next->content;
			} else {
				current[4] = '.';
			}
			current[5] = '\0';

			int matches = 0;
			for(int j=0; j<numRules; j++) {
				if(strcmp(current,rules[j].pattern)==0) {
					matches++;
					cur->nextGen = rules[j].becomes;
					break;
				}
			}
			if(matches==0) {
				cur->nextGen = '.';
			}
			cur = cur->next;
		}
		cur = first;
		while(cur!=NULL) {
			cur->content = cur->nextGen;
			cur = cur->next;
		}

		for(int i=0; i<2; i++) {
			cur = first;
			if(cur->content == '#' || cur->next->content == '#') {
				int index = cur->index-1;
				pot* plant = malloc(sizeof(pot));
				plant->content = '.';
				plant->index = index;
				plant->prev = NULL;
				plant->next = first;
				first->prev = plant;
				first = plant;
			}
		}

		for(int i=0; i<2; i++) {
			cur = last;
			if(cur->content == '#' || cur->prev->content == '#') {
				int index = cur->index+1;
				pot* plant = malloc(sizeof(pot));
				plant->content =  '.';
				plant->index = index;
				plant->prev = last;
				plant->next = NULL;
				last->next = plant;
				last = plant;
			}
		}
		score = getScore(first);
		int scoreDiff = score-prevScore;
		if(diffLen == LINEARLENGTH) {
			for(int i=0; i<diffLen-1; i++) {
				scoreDiffs[i] = scoreDiffs[i+1];
			}
			scoreDiffs[LINEARLENGTH-1] = scoreDiff;
			int equal = 0;
			for(int i=0; i<diffLen; i++) {
				if(scoreDiffs[i]==scoreDiff) {
					equal++;
				}
			}
			if(equal == LINEARLENGTH) {
				long gen = PART2 - (generation+1);
				score += scoreDiff*gen;
				printf("part2: %ld\n",score);
				generation = PART2;
			}
		} else {
			scoreDiffs[diffLen++] = scoreDiff;
		}
		generation++;
		if(generation==PART1) {
			printf("part1: %ld\n",score);
		}
	}

	pot* cur = first;
	while(cur!=NULL) {
		pot* tmp = cur;
		cur = cur->next;
		free(tmp);
	}

	free(rules);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long getScore(pot* root) {
	long score = 0;
	pot* cur = root;
	while(cur!=NULL) {
		if(cur->content == '#') {
			score += cur->index;
		}
		cur = cur->next;
	}
	return score;
}
