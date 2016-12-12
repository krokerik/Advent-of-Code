#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	cpy,
	inc,
	dec,
	jnz
}command_type;
typedef struct instruction{
	command_type command;
	char arg[2];
	int type[2]; //0 is const, 1 is var
	struct instruction* prev;
	struct instruction* next;
}instruction;

#define INPUT "../input/12.txt"
#define PART1 {0,0,0,0}
#define PART2 {0,0,1,0}

void parse(char* command);
void addCommand(command_type func, char arg[2], int[2]);
int isRegistry(char reg);

instruction* head;

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	instruction* cur;
	int registry[4] = PART2;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		parse(line);
	}

	cur = head;
	while(cur!=NULL){
		printf("\r");
		for(int j=0; j<4; j++){
			printf("%c %-9d ",j+'a',registry[j]);
		}
		fflush(stdout);
		switch(cur->command){
			case cpy:
				if(cur->type[0]==1){
					registry[cur->arg[1]-'a'] = registry[cur->arg[0]-'a'];
				}else{
					registry[cur->arg[1]-'a'] = cur->arg[0];
				}
				cur = cur->next;
				break;
			case inc:
				registry[cur->arg[0]-'a']++;
				cur = cur->next;
				break;
			case dec:
				registry[cur->arg[0]-'a']--;
				cur = cur->next;
				break;
			case jnz:
				if((cur->type[0]==1 && registry[cur->arg[0]-'a']!=0) ||
				(cur->type[0]==0 && cur->arg[0]!=0)){
					int jmp = cur->type[1]==1?registry[cur->arg[1]-'a']:cur->arg[1];
					if(jmp<0){
						for(int i=0; i>jmp; i--){
							cur = cur->prev;
							if(cur == NULL)
								break;
						}
					}else if(jmp>0){
						for(int i=0; i<jmp; i++){
							cur = cur->next;
							if(cur==NULL)
								break;
						}
					}else{
						cur = cur->next;
					}
				}else{
					cur = cur->next;
				}
				break;
		}
	}

	while(head!=NULL){
		instruction* temp = head->next;
		free(head);
		head = temp;
	}

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void parse(char* command){
	char *word;
	command_type method;
	char arg[2];
	int type[2];

	word = strtok(command, " ");
	for(int i=0; word!=NULL; word = strtok(NULL, " "), i++){
		switch(i){
			case 0:
				if(strcmp(word,"cpy")==0){
					method = cpy;
				}else if(strcmp(word,"inc")==0){
					method = inc;
				}else if(strcmp(word,"dec")==0){
					method = dec;
				}else if(strcmp(word,"jnz")==0){
					method = jnz;
				}else{
					fprintf(stderr,"Invalid command \"%s\"\n",word);
					exit(EXIT_FAILURE);
				}
				break;
			case 1:
			case 2:
				if(word[0]>='a' && word[0]<='d'){
					arg[i-1]  = word[0];
					type[i-1] = 1;
				}else if((word[0]>='0' && word[0]<='9')||word[0]=='-'){
					arg[i-1]  = atoi(word);
					type[i-1] = 0;
				}else{
					fprintf(stderr,"Invalid argument \"%s\", only accepts "
					               "registry a-d and integers\n",word);
					exit(EXIT_FAILURE);
				}
				break;
		}
	}
	addCommand(method, arg, type);
}

void addCommand(command_type func, char arg[2], int type[2]){
	instruction* cur;

	if(head==NULL){
		head = malloc(sizeof(instruction));
		head->prev = NULL;
		head->next = NULL;
		cur = head;
	} else {
		cur = head;
		while(cur->next!=NULL){
			cur = cur->next;
		}
		cur->next = malloc(sizeof(instruction));
		cur->next->prev = cur;
		cur->next->next = NULL;
		cur = cur->next;
	}

	cur->command = func;
	cur->arg[0]  = arg[0];
	cur->arg[1]  = arg[1];
	cur->type[0] = type[0];
	cur->type[1] = type[1];
}
