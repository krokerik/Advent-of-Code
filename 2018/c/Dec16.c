#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT "../input/16.txt"
#define MEMLEN 4
#define OPCODES 16

int behavesLike(int* before, int* after, int* instr);
void add_candidate(int prog,int op);
int get_operation(int code);
void addr(int a, int b, int c, int* reg);
void addi(int a, int b, int c, int* reg);
void mulr(int a, int b, int c, int* reg);
void muli(int a, int b, int c, int* reg);
void banr(int a, int b, int c, int* reg);
void bani(int a, int b, int c, int* reg);
void borr(int a, int b, int c, int* reg);
void bori(int a, int b, int c, int* reg);
void setr(int a, int b, int c, int* reg);
void seti(int a, int b, int c, int* reg);
void gtir(int a, int b, int c, int* reg);
void gtri(int a, int b, int c, int* reg);
void gtrr(int a, int b, int c, int* reg);
void eqir(int a, int b, int c, int* reg);
void eqri(int a, int b, int c, int* reg);
void eqrr(int a, int b, int c, int* reg);

void (*prog[OPCODES])(int, int, int, int*) = {addr,
                                              addi,
                                              mulr,
                                              muli,
                                              banr,
                                              bani,
                                              borr,
                                              bori,
                                              setr,
                                              seti,
                                              gtir,
                                              gtri,
                                              gtrr,
                                              eqir,
                                              eqri,
                                              eqrr};
int opcodes[OPCODES];
int candidates[OPCODES][OPCODES];

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int before[MEMLEN];
	int instr[MEMLEN];
	int after[MEMLEN];
	int reg[MEMLEN];
	int stage   = 0;
	int part1   = 0;
	int empties = 0;

	memset(opcodes,-1,sizeof(int)*OPCODES);

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1) {
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		if(strlen(line)==0) {
			empties++;
		}
		if(stage == 0 && strstr(line,"Before")==line) {
			empties = 0;
			for(int i=0; i<MEMLEN; i++) {
				before[i] = atoi(line+9+(i*3));
			}
			stage++;
		} else if(stage == 1) {
			for(int i=0; i<MEMLEN; i++) {
				instr[i] = atoi(line+i*2);
			}
			stage++;
		} else if(stage == 2) {
			for(int i=0; i<MEMLEN; i++) {
				after[i] = atoi(line+9+(i*3));
			}
			stage = 0;
			int tmp = behavesLike((int *)before,(int*)after,(int*)instr);
			if(tmp>=3) {
				part1 ++;
			}
		}
		if(empties == 3) {
			empties = 0;
			printf("part1: %d\n",part1);
			memset(reg,0,sizeof(int)*MEMLEN);
			stage = 3;

			int hasEmpties = 1;
			while(hasEmpties) {
				hasEmpties = 0;
				for(int i=0; i<OPCODES; i++) {
					if(opcodes[i] == -1) {
						hasEmpties = 1;
						int testOp = get_operation(i);

						if(testOp != -1) {
							opcodes[i] = testOp;
							for(int j=0; j<OPCODES; j++) {
								candidates[j][testOp] = 0; //remove candidate from matrix;
							}
						}
					}
				}
			}
		} else if(stage == 3) {
			for(int i=0; i<MEMLEN; i++) {
				instr[i] = atoi(line+i*2);
			}
			prog[opcodes[instr[0]]](instr[1],instr[2],instr[3],reg);
		}
	}
	printf("part2: %d\n",reg[0]);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int behavesLike(int* before, int* after, int* instr) {
	int numOpCodes = 0;
	int reg[MEMLEN];
	for(int i=0; i<OPCODES; i++) {
		memcpy(reg,before,sizeof(int)*MEMLEN);

		prog[i](instr[1],instr[2],instr[3],reg);
		int eq = 1;
		for(int j=0; j<MEMLEN; j++) {
			if(reg[j] != after[j]) {
				eq = 0;
				break;
			}
		}
		if(eq == 1) {
			numOpCodes++;
			add_candidate(i,instr[0]);
		}
	}
	return numOpCodes;
}

void add_candidate(int prog,int op) {
	candidates[op][prog]++;
}

int get_operation(int code) {
	int operation = 0;
	int highest = INT_MIN;
	int equaled = 0;
	for(int i=0; i<OPCODES; i++) {
		if(candidates[code][i]>highest) {
			equaled = 0;
			operation = i;
			highest = candidates[code][i];
		}else if(candidates[code][i] == highest) {
			equaled = 1;
		}
	}
	if(equaled == 1) {
		operation = -1;
	}
	return operation;
}

void addr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] + reg[b];
}

void addi(int a, int b, int c, int* reg) {
	reg[c] = reg[a] + b;
}
void mulr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] * reg[b];
}
void muli(int a, int b, int c, int* reg) {
	reg[c] = reg[a] * b;
}
void banr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] & reg[b];
}
void bani(int a, int b, int c, int* reg) {
	reg[c] = reg[a] & b;
}
void borr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] | reg[b];
}
void bori(int a, int b, int c, int* reg) {
	reg[c] = reg[a] | b;
}
void setr(int a, int b, int c, int* reg) {
	reg[c] = reg[a];
}
void seti(int a, int b, int c, int* reg) {
	reg[c] = a;
}
void gtir(int a, int b, int c, int* reg) {
	reg[c] = a > reg[b];
}
void gtri(int a, int b, int c, int* reg) {
	reg[c] = reg[a] > b;
}
void gtrr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] > reg[b];
}
void eqir(int a, int b, int c, int* reg) {
	reg[c] = a == reg[b];
}
void eqri(int a, int b, int c, int* reg) {
	reg[c] = reg[a] == b;
}
void eqrr(int a, int b, int c, int* reg) {
	reg[c] = reg[a] == reg[b];
}
