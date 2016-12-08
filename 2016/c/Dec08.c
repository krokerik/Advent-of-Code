#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/08.txt"
#define on    '#'
#define off   ' '
#define rows  6
#define cols  50

void draw(char screen[rows][cols]);
void parse(char screen[rows][cols], char* instruction);
void drawRect(char screen[rows][cols], int height, int width);
void rotateRow(char screen[rows][cols], int row, int amount);
void rotateCol(char screen[rows][cols], int col, int amount);
int countPixels(char screen[rows][cols]);

int main() {
	FILE* fp;
	char* line  = NULL;
	size_t len  = 0;
	char screen[rows][cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			screen[i][j] = off;

	fp = fopen(INPUT, "r");
	if(fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for(int i = 0;getline(&line, &len, fp) != -1; i++) {
		parse(screen,line);
	}
	draw(screen);
	printf("num pixels: %d\n", countPixels(screen));
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void draw(char screen[rows][cols]){
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++) {
			printf("%c",screen[i][j]);
		}
		printf("\n");
	}
}

void parse(char screen[rows][cols], char* instruction){
	char* word;
	
	word = strtok(instruction, " ");
	if(strcmp(word, "rect") == 0){
		word = strtok(NULL, " ");
		int pos=0;
		for(int i=0; i<strlen(word); i++){
			if(word[i]=='x'){
				pos = i;
				break;
			}
		}
		if(pos==0){
			fprintf(stderr, "Invalid instruction:\n%s\n",instruction);
			exit(EXIT_FAILURE);
		}
		
		int height = atoi(word+pos+1);
		int width = atoi(word);
		drawRect(screen, height, width);
		
	} else if(strcmp(word, "rotate") == 0) {
		word = strtok(NULL, " ");
		if(strcmp(word, "row") == 0){
			word = strtok(NULL, " ");
			int row = atoi(word+2);
			word = strtok(NULL, " ");
			word = strtok(NULL, " ");
			int amount = atoi(word);
			rotateRow(screen, row, amount);			
		} else if(strcmp(word, "column") == 0) {
			word = strtok(NULL, " ");
			int col = atoi(word+2);
			word = strtok(NULL, " ");
			word = strtok(NULL, " ");
			int amount = atoi(word);
			rotateCol(screen, col, amount);
			
		} else {
			fprintf(stderr,"invalid instruction to rotate %s\n", word);
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, "Invalid instruction:\n%s\n",instruction);
		exit(EXIT_FAILURE);
	}
}

void drawRect(char screen[rows][cols], int height, int width) {
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			screen[i][j] = on;
}

void rotateRow(char screen[rows][cols], int row, int amount){
	for(int i=0; i<amount; i++){
		char tmp = screen[row][cols-1];
		for(int j=0; j<cols; j++){
			char tmp2 = tmp;
			tmp = screen[row][j];
			screen[row][j] = tmp2;
		}
	}
}
void rotateCol(char screen[rows][cols], int col, int amount){
	for(int i=0; i<amount; i++){
		char tmp = screen[rows-1][col];
		for(int j=0; j<rows; j++){
			char tmp2 = tmp;
			tmp = screen[j][col];
			screen[j][col] = tmp2;
		}
	}
}

int countPixels(char screen[rows][cols]){
	int amount = 0;

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			if(screen[i][j] == on)
				amount++;

	return amount;
}