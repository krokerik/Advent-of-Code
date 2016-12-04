#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/04.txt"
#define SEARCH "northpole object storage"

int getValidID(char * room);
char* generateChecksum(int* frequency);
int contains(char* word, char letter);
char* rotate(char* word, int times);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	int validTotal = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	for (int i=0;getline(&line, &len, fp) != -1; i++) {
		validTotal += getValidID(line);
	}
	printf("sum sector IDs: %d\n",validTotal);

	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getValidID(char * room) {
	int id = 0, lastDash = 0, numDashes = 0, letters[26];
	char tmpID[4], checksum[6];
	char *genChecksum, *name;

	for(int i=0; i<strlen(room); i++) {
		if('-' == room[i]) {
			lastDash = i;
			numDashes++;
		}
	}
	name = malloc(sizeof(char)*lastDash+1);
	name = strncpy(name,room,lastDash);
	name[lastDash] = '\0';

	for(int i=0; i<26; i++) {
		letters[i] = 0;
	}
	
	for(int i=0; i<3; i++) {
		tmpID[i] = room[lastDash+i+1];
	}
	tmpID[3] = '\0';
	numDashes = 0;
	for(int i=0; i<lastDash; i++) {
		if('-' == room[i]) {
			numDashes++;
		} else {
			letters[room[i]-'a']++;
		}
	}

	for(int i=0; i<5; i++) {
		checksum[i] = room[lastDash+i+5];
	}
	checksum[5] = '\0';
	id = atoi(tmpID);
	genChecksum = generateChecksum(letters);

	if(strcmp(checksum,genChecksum)!=0) {
		id = 0;
	}
	if(strcmp(SEARCH,rotate(name,id))==0) {
		printf("%d is %s\n",id,name);
	}
	free(genChecksum);
	free(name);
	return id;
}

char* generateChecksum(int* frequency) {
	char* checksum;
	checksum = malloc(sizeof(char)*6);

	for(int i=0; i<5; i++)
		checksum[i] = '0';
	for(int i=0; i<26; i++) {
		if(frequency[i] != 0 && contains(checksum,i+'a') != 1) {
			for(int j=0; j<5; j++) {
				if(checksum[j] == '0' || frequency[checksum[j]-'a']<frequency[i] || (frequency[checksum[j]-'a']==frequency[i] && checksum[j]>(i+'a'))) {
					checksum[j] = i+'a';
					i = -1;
					break;
				}
			}
		}
	}
	checksum[5] = '\0';
	return checksum;
}

int contains(char* word, char letter) {
	for(int i=0, len=strlen(word); i<len; i++)
		if(word[i] == letter)
			return 1;
	return 0;
}
char* rotate(char* word, int times) {
	if(times==0)
		return word;
	for(int i=0, len=strlen(word); i<len; i++) {
		switch(word[i]){
			case '-':
				word[i] = ' ';
			case ' ':
				break;
			case 'z':
				word[i] = 'a';
				break;
			default:
				word[i]++;
		}
	}
	return rotate(word,times-1);
}