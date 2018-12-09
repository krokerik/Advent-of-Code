#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/09.txt"

typedef struct marble {
	struct marble * prev;
	struct marble * next;
	long long val;
} marble;

long long getHighscore(int numPlayers, int lastMarble);

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

		int players = atoi(line);
		char* temp = strstr(line,"worth ");
		int lastPoint = atoi(temp+6);
		printf("%d players; last marble is worth %d points: high score is %lld\n",players,lastPoint,getHighscore(players,lastPoint));
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

long long getHighscore(int numPlayers, int lastMarble) {
	long long highscore = 0;
	long long players[numPlayers];
	memset(players,0,sizeof(long long)*numPlayers);

	marble * current = NULL;
	for(int currMarble = 0, currPlayer=0; currMarble<=lastMarble; currMarble++, currPlayer++) {
		if(currPlayer==numPlayers) {
			currPlayer=0;
		}
		long long currScore = 0;
		if(currMarble != 0 && currMarble%23==0) {
			currScore = currMarble;
			for(int i=0; current!=NULL && i<7; i++) {
				current = current->prev;
			}
			marble * temp = current;
			currScore += current->val;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
			free(temp);
		} else {
			if(current==NULL) {
				current = malloc(sizeof(marble));
				current->next = current;
				current->prev = current;
				current->val = currMarble;
			} else {
				marble * newMarble = malloc(sizeof(marble));
				newMarble->val = currMarble;
				current = current->next;
				newMarble->prev = current;
				newMarble->next = current->next;
				current->next = newMarble;
				newMarble->next->prev = newMarble;
				current = newMarble;
			}

		}
		players[currPlayer] += currScore;
	}
	for(int i=0; i<numPlayers; i++) {
		if(players[i]>highscore) {
			highscore = players[i];
		}
	}

	current->prev->next = NULL;
	while(current->next != NULL) {
		marble* temp = current;
		current = current->next;
		free(temp);
	}
	free(current);
	return highscore;
}
