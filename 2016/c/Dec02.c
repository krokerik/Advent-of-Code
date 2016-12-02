#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/02.txt"
#define UP 'U'
#define DOWN 'D'
#define LEFT 'L'
#define RIGHT 'R'

int getButton(char* instructions, int button);
int moveButton(int button, char instruction);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	int currentButton = 5;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1) {
		currentButton = getButton(line, currentButton);
		printf("%d",currentButton);
	}
	printf("\n");

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getButton(char* instructions, int button) {
	int len = strlen(instructions);
	for(int i=0; i<len-1; i++) {
		char c = instructions[i];
		button = moveButton(button,c);
	}
	return button;
}

int moveButton(int button, char instruction) {
	int init = button;
	switch(instruction) {
		case UP:
			button -= (button>3)?3:0;
			break;
		case LEFT:
			button -= (button%3!=1)?1:0;
			break;
		case DOWN:
			button += (button<7)?3:0;
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
