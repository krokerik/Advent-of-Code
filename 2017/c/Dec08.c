#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/08.txt"

#define INC 0
#define DEC 1

#define GT 0
#define GE 1
#define EQ 2
#define NE 3
#define LE 4
#define LT 5

typedef struct memBlock{
	char* name;
	int val;
} memBlock;

void parseRow(char* instruction);
memBlock* getMemBlock(char* name);
memBlock* createMemBlock(char* name);
int getBiggest();

memBlock** memory = NULL;
int numRegs       = 0;

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	int biggest = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		parseRow(line);
		int temp = getBiggest();
		biggest = temp>biggest ? temp : biggest;
	}

	printf("Part 1: %d\n",getBiggest());
	printf("Part 2: %d\n",biggest);

	for(int i=0; i<numRegs; i++) {
		free(memory[i]->name);
		free(memory[i]);
	}
	fclose(fp);
	free(line);
	free(memory);
	exit(EXIT_SUCCESS);
}

void parseRow(char* instruction) {
	char *token = strtok(instruction," "),
	     *end;
	memBlock *dest = getMemBlock(token),
	         *dep;
	int direction,
	    cond,
	    val,
	    operand,
	    passed = 0;

	token = strtok(NULL, " ");
	if(strcmp(token, "inc")==0) {
		direction = INC;
	} else if(strcmp(token, "dec")==0) {
		direction = DEC;
	}

	token = strtok(NULL, " ");
	val   = (int)strtol(token,&end,10);

	token = strtok(NULL, " ");
	token = strtok(NULL, " "); //skip "if"
	dep   = getMemBlock(token);

	token = strtok(NULL, " ");
	if(strcmp(token,">")==0) {
		cond = GT;
	} else if(strcmp(token,">=")==0) {
		cond = GE;
	} else if(strcmp(token,"==")==0) {
		cond = EQ;
	} else if(strcmp(token,"!=")==0) {
		cond = NE;
	} else if(strcmp(token,"<=")==0) {
		cond = LE;
	} else if(strcmp(token,"<")==0) {
		cond = LT;
	}
	
	token   = strtok(NULL, " ");
	operand = (int)strtol(token,&end,10);

	switch(cond) {
		case GT:
			if(dep->val > operand)  passed = 1;
			break;
		case GE:
			if(dep->val >= operand) passed = 1;
			break;
		case EQ:
			if(dep->val == operand) passed = 1;
			break;
		case NE:
			if(dep->val != operand) passed = 1;
			break;
		case LE:
			if(dep->val <= operand) passed = 1;
			break;
		case LT:
			if(dep->val < operand)  passed = 1;
			break;
	}
	if(passed == 1) {
		if(direction == INC) {
			dest->val += val;
		} else if(direction == DEC) {
			dest->val -= val;
		}
	}
}
memBlock* getMemBlock(char* name) {
	memBlock* reg = NULL;
	if(memory == NULL) {
		memory    = malloc(sizeof(memBlock*));
		memory[0] = createMemBlock(name);
		numRegs++;
	}
	for(int i=0; i<numRegs; i++) {
		if(strcmp(memory[i]->name,name)==0) {
			reg = memory[i];
			break;
		}
	}
	if(reg == NULL) {
		memory          = realloc(memory,sizeof(memBlock*)*(numRegs+1));
		memory[numRegs] = createMemBlock(name);
		reg             = memory[numRegs];
		numRegs++;
	}
	return reg;
}

memBlock* createMemBlock(char* name) {
	memBlock* newMemBlock = malloc(sizeof(memBlock));
	newMemBlock->name    = malloc(strlen(name)+1);
	newMemBlock->val     = 0;
	strcpy(newMemBlock->name,name);
	return newMemBlock;
}

int getBiggest() {
	int biggest = 0;
	for(int i=0; i<numRegs; i++) {
		if(memory[i]->val > memory[biggest]->val) {
			biggest = i;
		}
	}
	return memory[biggest]->val;
}