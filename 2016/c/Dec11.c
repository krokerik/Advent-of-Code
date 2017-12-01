#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/11.txt"

typedef struct component{
	char* type;
	char* name;
	int floor;
	struct component* next;
}component;

void parse(char* instruction);
void addComponent(char* type, char* name, int floor);

component* components;

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	int pos = 1, moves = 0, heading = 1;
	component* inventory1;
	component* inventory2;

	inventory1 = NULL;
	inventory2 = NULL;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		parse(line);
	}

	//while(!isSolved()){
	for(int i=0; i<3; i++){
		for(component* cur = components; cur!=NULL; cur = cur->next){
			if(cur->floor == pos){
				if(heading == 1){
					if(inventory1==NULL){
						inventory1 = cur;
						printf("taking %s %s\n", cur->name, cur->type);
					}else if(inventory2==NULL){
						inventory2 = cur;
					}
				}else{
					
				}
			}
		}

		if(heading == 1){
			if(pos<4){
				if(inventory1 != NULL)
					inventory1->floor++;
				if(inventory2 != NULL)
					inventory2->floor++;
				pos++;
			}else{
				heading=0;
				inventory1 = NULL;
				inventory2 = NULL;
			}
		}else{
			if(inventory1 != NULL)
				inventory1->floor--;
			if(inventory2 != NULL)
				inventory2->floor--;
			pos--;
		}
		moves++;
	}

	while(components!=NULL){
		component* next = components->next;
		printf("%s %s on floor %d\n",components->name,components->type,components->floor);
		free(components->type);
		free(components->name);
		free(components);
		components = next;
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void parse(char* instruction){
	char *word, *type=NULL, *name=NULL;
	int floor, nothing;

	nothing = 0;
	word = strtok(instruction, " ");
	for(int i=0; word!=NULL && nothing==0; word = strtok(NULL, " "), i++){
		switch(i){
			case 1:
				if(strcmp(word, "first")==0){
					floor = 1;
				}else if(strcmp(word, "second")==0){
					floor = 2;
				}else if(strcmp(word, "third")==0){
					floor = 3;
				}else if(strcmp(word, "fourth")==0){
					floor = 4;
				}else{
					fprintf(stderr,"Invalid floor \"%s\"",word);
					exit(EXIT_FAILURE);
				}
				break;
			case 4:
				if(strcmp(word, "a")!=0){
					nothing = 1;
				}
				break;
			case 5:
				for(int j=0; j<strlen(word); j++){
					if(word[j]=='-'){
						name = malloc((sizeof(char)*j)+1);
						strncpy(name,word,j);
						name[j] = '\0';
						break;
					}
				}
				if(name==NULL){
					name = malloc((sizeof(char)*strlen(word))+1);
					strcpy(name, word);
				}
				break;
			case 6:
				if(word[strlen(word)-3]=='.'){
					type = malloc((sizeof(char)*strlen(word))-2);
					strncpy(type,word,strlen(word)-3);
					type[strlen(word)-3] = '\0';
				}else if(word[strlen(word)-1]==','){
					type = malloc(sizeof(char)*strlen(word));
					strncpy(type, word, strlen(word)-1);
					type[strlen(word)-1] = '\0';
				}else{
					type = malloc((sizeof(char)*strlen(word))+1);
					strcpy(type, word);
					type[strlen(word)] = '\0';
				}
				addComponent(type, name, floor);

				if(word[strlen(word)-1]==','){
					name = NULL;
					i -= 3;
				}
				break;
			case 7:
				if(strcmp(word, "and")==0){
					name = NULL;
					i -= 4;
				}
		}
	}
}

void addComponent(char* type, char* name, int floor){
	component* cur;

	if(components==NULL){
		components = malloc(sizeof(component));
		components->next = NULL;
		cur = components;
	} else {
		cur = components;
		while(cur->next!=NULL){
			cur = cur->next;
		}
		cur->next = malloc(sizeof(component));
		cur = cur->next;
		cur->next = NULL;
	}
	cur->type  = type;
	cur->name  = name;
	cur->floor = floor;
}

int isSolved(){
	int res = 1;
	component* cur = components;
	while(cur!=NULL){
		if(cur->floor!=4){
			res = 0;
		}
	}
	return res;
}