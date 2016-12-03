#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/02.txt"
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

char getSquareButton(char* instructions, char button);
char moveSquareButton(char button, char instruction);
char getDiamondButton(char* instructions, char button);
char moveDiamondButton(char button, char instruction);
int getDiamondRowLen(char button);
int isDiamondTop(char button);
int isDiamondBottom(char button);
int isDiamondLeft(char button);
int isDiamondRight(char button);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	char currentSquare  = '5';
	char currentDiamond = '5';

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1) {
		currentSquare  = getSquareButton(line, currentSquare);
		currentDiamond = getDiamondButton(line, currentDiamond);
		printf("%c\t%c\n",currentSquare, currentDiamond);
	}
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

char getSquareButton(char* instructions, char button) {
	int len = strlen(instructions);
	for(int i=0; i<len-1; i++) {
		char c = instructions[i];
		button = moveSquareButton(button,c);
	}
	return button;
}

char moveSquareButton(char button, char instruction) {
	switch(instruction) {
		case UP:
			button -= (button>'3')?3:0;
			break;
		case LEFT:
			button -= (button%3!=1)?1:0;
			break;
		case DOWN:
			button += (button<'7')?3:0;
			break;
		case RIGHT:
			button += (button%3!=0)?1:0;
			break;
		default:
			fprintf(stderr, "Invalid instruction '%c'\n",instruction);
			exit(EXIT_FAILURE);
	}
	return button;
}

char getDiamondButton(char* instructions, char button) {
	int len = strlen(instructions);
	for(int i=0; i<len-1; i++) {
		char c = instructions[i];
		button = moveDiamondButton(button,c);
	}
	return button;
}

char moveDiamondButton(char button, char instruction) {
	int rowLen = getDiamondRowLen(button);
	switch(instruction) {
		case UP:
			if(!isDiamondTop(button))
				if(rowLen==1)
					button -= 2;
				else if(rowLen==3 && button>'4')
					button -= 11;
				else if(rowLen==3 && button=='3')
					button -= 2;
				else if(rowLen==5)
					button -= 4;
			break;
		case DOWN:
			if(!isDiamondBottom(button))
				if(rowLen==1)
					button += 2;
				else if(rowLen==3 && button<'5')
					button += 4;
				else if(rowLen==3 && button=='B')
					button += 2;
				else if(rowLen==5)
					button += 11;
			break;
		case LEFT:
			if(!isDiamondLeft(button))
				button--;
			break;
		case RIGHT:
			if(!isDiamondRight(button))
				button++;
			break;
		default:
			fprintf(stderr, "Invalid instruction '%c'\n",instruction);
			exit(EXIT_FAILURE);
	}
	return button;
}

int getDiamondRowLen(char button) {
	int len = 0;
	switch(button) {
		case '1':
		case 'D':
			len = 1;
			break;
		case '2':
		case '3':
		case '4':
		case 'A':
		case 'B':
		case 'C':
			len = 3;
			break;
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			len = 5;
			break;
		default:
			fprintf(stderr,"invalid button '%c'\n",button);
			exit(EXIT_FAILURE);
	}
	return len;
}

int isDiamondTop(char button){
	int top = 0;
	switch(button){
		case '1':
		case '2':
		case '4':
		case '5':
		case '9':
			top = 1;
			break;
	}
	return top;
}

int isDiamondBottom(char button){
	int bottom = 0;
	switch(button){
		case '5':
		case 'A':
		case 'D':
		case 'C':
		case '9':
			bottom = 1;
			break;
	}
	return bottom;
}

int isDiamondLeft(char button){
	int left = 0;
	switch(button){
		case '1':
		case '2':
		case '5':
		case 'A':
		case 'D':
			left = 1;
			break;
	}
	return left;
}

int isDiamondRight(char button){
	int right = 0;
	switch(button){
		case '1':
		case '4':
		case '9':
		case 'C':
		case 'D':
			right = 1;
			break;
	}
	return right;
}
