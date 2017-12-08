#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/07.txt"

typedef struct program{
	char* name;
	struct program** children;
	char** backupChildren;
	int numChildren;
	int weight;
} program;

program* createProgram(char* program);
program* findProgram(char* name);
program* getRoot();
long getWeight(program* root);
program* getImbalanced(program* root);

program** list = NULL;
int numProgs = 0;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		program* prog = createProgram(line);
		if(list == NULL) {
			list = malloc(sizeof(program*));
		} else {
			list = realloc(list,sizeof(program*)*(numProgs+1));
		}
		list[numProgs++] = prog;
		
	}

	//Set up final links.
	for(int i=0; i<numProgs; i++) {
		for(int j=0; j<list[i]->numChildren; j++) {
			if(list[i]->children[j] == NULL) {
				list[i]->children[j] = findProgram(list[i]->backupChildren[j]);
				free(list[i]->backupChildren[j]);
			} 
		}
	}

	program* root = getRoot();
	if(root!=NULL) {
		printf("part 1: %s\n", root->name);
		program* broken = getImbalanced(root), *ref[2] = {NULL};
		int num[2] = {0}, val[2] = {0}, newWeight;
		for(int i=0; i<broken->numChildren; i++) {
			long weight = getWeight(broken->children[i]);
			if(num[0] == 0 || val[0] == weight) {
				num[0]++;
				val[0] = weight;
				ref[0] = broken->children[i];
			} else {
				num[1]++;
				val[1] = weight;
				ref[1] = broken->children[i];
			}
		}
		if(num[0]==1) {
			if(val[0]>val[1]) {
				newWeight = ref[0]->weight - (val[0]-val[1]);
			} else {
				newWeight = ref[0]->weight + (val[1]-val[0]);
			}
		} else if(num[1]==1) {
			if(val[1]>val[0]) {
				newWeight = ref[1]->weight - (val[1]-val[0]);
			} else {
				newWeight = ref[1]->weight + (val[0]-val[1]);
			}
		}
		printf("part 2: %d\n",newWeight);
	}

	//Free all memory
	for(int i=0; i<numProgs; i++) {
		
		free(list[i]->name);
		if(list[i]->children != NULL) {
			free(list[i]->children);
		}
		if(list[i]->backupChildren != NULL) {
			free(list[i]->backupChildren);
		}
		free(list[i]);
	}
	fclose(fp);
	free(line);
	free(list);
	exit(EXIT_SUCCESS);
}

program* createProgram(char* prog) {
	program* newProg, **children = NULL;
	int weight = 0, numChildren = 0;
	char* token, *name, *end, **backupChildren = NULL;

	token = strtok(prog," ");
	name = malloc(strlen(token)+1);
	strcpy(name, token);
	
	token = strtok(NULL, " ");
	weight = (int)strtol(token+1, &end, 10);
	
	token = strtok(NULL, " ");
	token = strtok(NULL, " "); //skip arrow if it's there.
	while(token != NULL) {
		if(token[strlen(token)-1] == ',') {
			token[strlen(token)-1] = '\0';
		}
		program* child = findProgram(token);
		if(children == NULL) {
			children = malloc(sizeof(program*));
			backupChildren = malloc(sizeof(char*));
		} else {
			children = realloc(children, sizeof(program*)*(numChildren+1));
			backupChildren = realloc(backupChildren, sizeof(char*) * (numChildren+1));
		}
		if(child == NULL) {
			backupChildren[numChildren] = malloc(strlen(token)+1);
			strcpy(backupChildren[numChildren],token);
			children[numChildren] = NULL;
		} else {
			children[numChildren] = child;
			backupChildren[numChildren] = NULL;
		}
		numChildren++;
		token = strtok(NULL, " ");
	}

	newProg                 = malloc(sizeof(program));
	newProg->name           = name;
	newProg->children       = children;
	newProg->backupChildren = backupChildren;
	newProg->numChildren    = numChildren;
	newProg->weight         = weight;
	return newProg;
}

program* findProgram(char* name) {
	program* res = NULL;
	for(int i=0; i<numProgs; i++) {
		if(strcmp(name,list[i]->name)==0) {
			res = list[i];
			break;
		}
	}
	return res;
}

program* getRoot() {
	program* root = NULL;
	for(int i=0; i<numProgs; i++) {
		int isRoot = 1;
		for(int j=0; j<numProgs; j++) {
			for(int k=0; k<list[j]->numChildren; k++) {
				if(strcmp(list[i]->name,list[j]->children[k]->name) == 0) {
					isRoot = 0;
				}
			}
		}
		if(isRoot == 1) {
			root = list[i];
			break;
		}
	}
	return root;
}

long getWeight(program* root) {
	long tot = root->weight;
	
	for(int i=0; i<root->numChildren; i++) {
		tot += getWeight(root->children[i]);
	}
	
	return tot;
}

program* getImbalanced(program* root) {
	program* odd = NULL, *ref[2] = {NULL}, **progs = root->children;
	int num[2] = {0}, val[2] = {0}, len = root->numChildren;
	
	for(int i=0; i<len; i++) {
		long weight = getWeight(progs[i]);
		if(num[0] == 0 || val[0] == weight) {
			num[0]++;
			val[0] = weight;
			ref[0] = progs[i];
		} else {
			num[1]++;
			val[1] = weight;
			ref[1] = progs[i];
		}
	}
	if(num[1]==0) return NULL;
	if(num[0]==1) {
		odd = ref[0];
	} else if(num[1]==1) {
		odd = ref[1];
	}
	program* ret = getImbalanced(odd);
	if(ret == NULL) return root;
	return ret;
}