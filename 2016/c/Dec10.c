#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/10.txt"
#define SEARCH1 61
#define SEARCH2 17

typedef struct container{
	int id;
	int values[2];
	struct container* next;
} container;

typedef struct rule{
	int from;
	int lowType; //0 is bot. 1 is output.
	int lowTo;
	int highType; //0 is bot. 1 is output.
	int highTo;
	struct rule* next;
} rule;

void parse(char* instruction);
void addBot(int id, int value);
void addRule(int from, int lowType, int lowTo, int highType, int highTo);
container* getBot(int id);

container* bots;
rule* rules;

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	rule* cur;
	int out[3];

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		parse(line);
	}
	cur=rules;
	while(cur!=NULL){
		container* tmp = getBot(cur->from);
		if(tmp!=NULL && tmp->values[0]!=0 && tmp->values[1]!=0){
			int low, high;
			low  = tmp->values[0]>tmp->values[1]?tmp->values[1]:tmp->values[0];
			high = tmp->values[0]<tmp->values[1]?tmp->values[1]:tmp->values[0];
			if((low==SEARCH1 && high==SEARCH2) || (low==SEARCH2 && high==SEARCH1))
				fprintf(stderr,"  part 1: %d\n",cur->from);
			if(cur->highType==0){
				addBot(cur->highTo,high);
			}else{
				printf("output %d: %d\n",cur->highTo,high);
				if(cur->highTo<3)
					out[cur->highTo] = high;
			}
			if(cur->lowType==0){
				addBot(cur->lowTo,low);
			}else{
				printf("output %d: %d\n",cur->lowTo,low);
				if(cur->lowTo<3)
					out[cur->lowTo] = low;
			}
			tmp->values[0] = 0;
			tmp->values[1] = 0;
			cur  = rules;
		}else{
			cur = cur->next;
		}
	}
	while(bots!=NULL){
		container* tmp = bots->next;
		free(bots);
		bots = tmp;
	}
	while(rules!=NULL){
		rule* tmp = rules->next;
		free(rules);
		rules = tmp;
	}
	fprintf(stderr,"  part 2: %d\n",out[0]*out[1]*out[2]);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void parse(char* instruction){
	char* word;

	word = strtok(instruction, " ");
	if(strcmp(word, "value")==0){
		int value, id;
		word = strtok(NULL, " ");
		value = atoi(word);
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		id = atoi(word);
		addBot(id, value);
	}else if(strcmp(word, "bot")==0){
		int from, lowType, lowTo, highType, highTo;

		word = strtok(NULL, " ");
		from = atoi(word);

		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		if(strcmp(word, "output")==0){
			lowType = 1;
		}else if(strcmp(word, "bot")==0){
			lowType = 0;
		}else{
			fprintf(stderr,"invalid target \"%s\"\n",word);
			exit(EXIT_FAILURE);
		}

		word = strtok(NULL, " ");
		lowTo = atoi(word);

		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		word = strtok(NULL, " ");
		if(strcmp(word, "output")==0){
			highType = 1;
		}else if(strcmp(word, "bot")==0){
			highType = 0;
		}else{
			fprintf(stderr,"invalid target \"%s\"\n",word);
			exit(EXIT_FAILURE);
		}

		word = strtok(NULL, " ");
		highTo = atoi(word);
		addRule(from, lowType, lowTo, highType, highTo);
	}else{
		fprintf(stderr, "Invalid instruction: %s\n",word);
		exit(EXIT_FAILURE);
	}
}

void addBot(int id, int value){
	container* cur;
	if(bots==NULL){
		bots = malloc(sizeof(container));
		bots->values[0] = 0;
		bots->values[1] = 0;
		bots->next = NULL;
		cur = bots;
	} else {
		cur = bots;
		while(cur->next!=NULL && cur->id != id){
			cur = cur->next;
		}
		if(cur->next==NULL && cur->id!=id){
			cur->next = malloc(sizeof(container));
			cur = cur->next;
			cur->values[0] = 0;
			cur->values[1] = 0;
			cur->next = NULL;
		}
	}
	cur->id = id;
	if(cur->values[0]==0)
		cur->values[0]=value;
	else if(cur->values[1]==0)
		cur->values[1]=value;
	else
		fprintf(stderr, "bot %d is full\n",id);
}

void addRule(int from, int lowType, int lowTo, int highType, int highTo) {
	rule* cur;
	if(rules==NULL){
		rules = malloc(sizeof(rule));
		rules->next = NULL;
		cur = rules;
	}else{
		cur = rules;
		while(cur->next!=NULL){
			cur = cur->next;
		}
		cur->next = malloc(sizeof(rule));
		cur = cur->next;
		cur->next = NULL;
	}
	cur->from     = from;
	cur->lowType  = lowType;
	cur->lowTo    = lowTo;
	cur->highType = highType;
	cur->highTo   = highTo;
}

container* getBot(int id){
	container* cur = bots;
	while(cur!=NULL && cur->id!=id){
		cur = cur->next;
	}
	return cur;
}
