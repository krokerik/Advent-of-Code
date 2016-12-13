#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/13.txt"
#define GOALX 31
#define GOALY 39
#define INIT  {1,1}

typedef struct state_type {
	int x;
	int y;
	int moves;
}state_type;
typedef struct state_list{
	state_type* state;
	struct state_list* next;
}state_list;

char getSquare(int x, int y, int fav);
state_list* expand(state_type* state);
int exists(state_type* state, state_list* head);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	int favourite = 0, found = 0;
	int pos[2] = INIT;
	state_type* cur;
	state_list* head;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		favourite = atoi(line);
	}
	
	cur = malloc(sizeof(state_type));
	cur->x     = pos[0];
	cur->y     = pos[1];
	cur->moves = 0;
	head = malloc(sizeof(state_list));
	
	head->state = cur;
	head->next  = NULL;
	state_list* tmp  = head;
	state_list* last = head;
	while(last->next!=NULL){
		last = last->next;
	}
	while(!found && tmp!=NULL){
		state_list* tmp2 = expand(tmp->state);
		while(tmp2!=NULL){
			if(getSquare(tmp2->state->x,tmp2->state->y,favourite)=='.' && !exists(tmp2->state, head)){
				last->next = malloc(sizeof(state_list));
				last = last->next;
				last->state = tmp2->state;
				last->state->moves = tmp->state->moves+1;
				last->next = NULL;
				if(tmp2->state->x == GOALX && tmp2->state->y == GOALY){
					printf("part1: %d\n",tmp2->state->moves);
					found = 0;
				}
			} else {
				free(tmp2->state);
			}
			state_list* next = tmp2->next;
			free(tmp2);
			tmp2 = next;
		}
		tmp = tmp->next;
	}
	
	int length = 0;
	state_list* lentmp = head;
	while(lentmp != NULL){
		if(lentmp->state->moves<=50)
			length++;
		lentmp = lentmp->next;
	}
	
	printf("part2: %d\n",length);
	
	while(head!=NULL){
		state_list* tmp = head->next;
		free(head->state);
		free(head);
		head = tmp;
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

char getSquare(int x, int y, int fav){
	uint32_t sum = (x*x) + (3*x) + (2*x*y) + y + (y*y) + fav;
	int count = 0;

	while(sum){
		count += sum&1;
		sum  >>= 1;
	}

	return count%2==0?'.':'#';
}

state_list* expand(state_type* state){
	state_list* head = NULL;
	for(int i=-1; i<2; i++){
		if(state->x+i >= 0){
			for(int j=-1; j<2; j++){
				if(state->y+j>=0 && ((i==0 && j!=0) || (i!=0 && j==0))){
					state_type* cur = malloc(sizeof(state_type));
					state_list* tmp = head;

					cur->x     = state->x+i;
					cur->y     = state->y+j;
					cur->moves = state->moves+1;
					
					if(head==NULL){
						head = malloc(sizeof(state_list));
						head->next = NULL;
						tmp = head;
					}else{
						while(tmp->next != NULL){
							tmp = tmp->next;
						}
						tmp->next = malloc(sizeof(state_list));
						tmp = tmp->next;
						tmp->next = NULL;
					}
					tmp->state = cur;
				}
			}
		}
	}
	return head;
}

int exists(state_type* state, state_list* head){
	while(head!=NULL){
		if(state->x == head->state->x && state->y == head->state->y)
			return 1;
		head = head->next;
	}
	return 0;
}