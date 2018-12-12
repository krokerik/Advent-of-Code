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
pot* createPot(int index, char content, pot* prev, pot* next);

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
			first = createPot(-2,'.',NULL,NULL);
			last = first;
			first->next = createPot(-1,'.',first,NULL);
			last = last->next;
			int numPlants = strlen(line+15);
			for(int i=0; i<numPlants; i++) {
				last->next = createPot(i,line[15+i],last,NULL);
				last = last->next;
			}
			last->next = createPot(last->index+1,'.',last,NULL);
			last = last->next;
			last->next = createPot(last->index+1,'.',last,NULL);
			last = last->next;
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
			if(first->content == '#' || first->next->content == '#') {
				first->prev = createPot(first->index-1,'.',NULL,first);
				first = first->prev;
			}
		}

		for(int i=0; i<2; i++) {
			if(last->content == '#' || last->prev->content == '#') {
				last->next = createPot(last->index+1,'.',last,NULL);
				last = last->next;
			}
		}
		score = getScore(first);
		int scoreDiff = score-prevScore;

		if(diffLen == LINEARLENGTH) {
			for(int i=0; i<diffLen-1; i++) {
				scoreDiffs[i] = scoreDiffs[i+1];
			}
			scoreDiffs[LINEARLENGTH-1] = scoreDiff;
			int equal = 1;
			for(int i=0; i<diffLen; i++) {
				if(scoreDiffs[i]!=scoreDiff) {
					equal = 0;
					break;
				}
			}
			if(equal == 1) {
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

	while(first!=NULL) {
		pot* tmp = first;
		first = first->next;
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

pot* createPot(int index, char content, pot* prev, pot* next) {
	pot* pot = malloc(sizeof(pot)*3);
	pot->index = index;
	pot->content = content;
	if(prev == NULL) {
		pot->prev = 0;
	} else {
		pot->prev = prev;
	}
	if(next == NULL) {
		pot->next = 0;
	} else {
		pot->next = next;
	}
	return pot;
}
