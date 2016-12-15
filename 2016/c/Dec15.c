#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/15.txt"

typedef struct disc_type {
	int positions;
	int current;
}disc_type;
typedef struct statue_type{
	disc_type* disc;
	struct statue_type* next;
}statue_type;

disc_type* parse(char* row);
statue_type* addDisc(statue_type* statue, disc_type* disc);
int isSolved(statue_type* statue, int dropTime);
void tick(statue_type* statue);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	statue_type* statue = NULL;
	int time=0;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		statue = addDisc(statue,parse(line));
	}

	time = statue->disc->positions-statue->disc->current-1;
	while(!isSolved(statue,time)){
		printf("\rtime: %d",time);
		fflush(stdout);
		time+=statue->disc->positions;
	}
	printf("\rpart 1: %d\n",time);
	time = statue->disc->positions-statue->disc->current-1;
	disc_type* new = malloc(sizeof(disc_type));
	new->positions = 11;
	new->current = 0;
	addDisc(statue,new);
	while(!isSolved(statue,time)){
		printf("\rtime: %d",time);
		fflush(stdout);
		time+=statue->disc->positions;
	}
	printf("\rpart 2: %d\n",time);

	while(statue!=NULL){
		free(statue->disc);
		statue_type* next = statue->next;
		free(statue);
		statue = next;
	}
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

disc_type* parse(char* row){
	disc_type* disc = malloc(sizeof(disc_type));
	char* word;

	word = strtok(row, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	disc->positions = atoi(word);
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	word = strtok(NULL, " ");
	disc->current = atoi(word);

	return disc;
}

statue_type* addDisc(statue_type* statue, disc_type* disc){
	statue_type* head = statue;
	if(head==NULL){
		head = malloc(sizeof(statue_type));
		head->next = NULL;
		statue = head;
	}else{
		while(statue->next!=NULL){
			statue = statue->next;
		}
		statue->next = malloc(sizeof(statue_type));
		statue->next->next = NULL;
		statue = statue->next;
	}
	statue->disc = disc;
	return head;
}

int isSolved(statue_type* statue, int dropTime){
	int time = dropTime+1;
	int res = 1;
	while(statue!=NULL){
		int current = (statue->disc->current+time)%statue->disc->positions;
		if(current!=0){
			res = 0;
			break;
		}
		time++;
		statue = statue->next;
	}
	return res;
}
