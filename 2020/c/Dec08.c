#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/08.txt"

typedef enum {
	acc,
	jmp,
	nop
} inst_type;

typedef struct instruction {
	inst_type type;
	int arg;
} instruction;

int get_result(instruction* program, int len, int* errcode);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int part1   = 0;
	int part2   = 0;
	int progLen = 0;
	instruction* program = malloc(sizeof(instruction));
	int errCode;


	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		char type[4];
		instruction inst;
		sscanf(line,"%3s %d",type,&(inst.arg));
		if(!strcmp(type,"acc")) {
			inst.type = acc;
		} else if(!strcmp(type,"jmp")) {
			inst.type = jmp;
		} else if(!strcmp(type,"nop")) {
			inst.type = nop;
		} else {
			fprintf(stderr,"unknown operation \"%s\"\n",type);
		}
		progLen++;
		program = realloc(program,sizeof(instruction)*progLen);
		program[progLen-1] = inst;
	}

	part1 = get_result(program, progLen, &errCode);
	printf("part 1: %d\n", part1);
	for(int i=0; i<progLen && errCode==1; i++) {
		switch(program[i].type) {
			case acc:
				break;
			case jmp:
				program[i].type = nop;
				part2 = get_result(program,progLen, &errCode);
				program[i].type = jmp;
				break;
			case nop:
				program[i].type = jmp;
				part2 = get_result(program,progLen, &errCode);
				program[i].type = nop;
				break;
		}
	}
	printf("part 2: %d\n", part2);
	fclose(fp);
	free(line);
	free(program);
	exit(EXIT_SUCCESS);
}

int get_result(instruction* program, int len, int* errcode) {
	int accumulator = 0;
	*errcode = 0;
	int* visits = calloc(len,sizeof(int));
	for(int i=0; i<len;) {
		if(!visits[i]) { //infinite loop
			visits[i]++;
			switch(program[i].type) {
				case acc:
					accumulator += program[i].arg;
					i++;
					break;
				case jmp:
					i += program[i].arg;
					break;
				case nop:
					i++;
					break;
			}
		} else {
			*errcode = 1;
			break;
		}
	}
	free(visits);
	return accumulator;
}
