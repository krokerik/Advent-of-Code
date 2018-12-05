#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define INPUT "../input/05.txt"

typedef struct thread_args {
	char* polymer;
	char unit;
} thread_args;

void* part1(void* arg);
void* part2(void* arg);
char* react(char* polymer);
char changePolarity(char unit);
void removeUnit(char* str, char unit);

int shortest;
pthread_mutex_t shortest_lock;

int main() {
	FILE * fp;
	char * line      = NULL;
	size_t len       = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	pthread_mutex_init(&shortest_lock,NULL);
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		pthread_t part1_t;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&part1_t,&attr,part1,line);
		pthread_join(part1_t,NULL);

		shortest = len;
		pthread_t part2_t[26];
		for(char c = 'a'; c<='z'; c++) {
			pthread_attr_t attributes;
			pthread_attr_init(&attributes);
			thread_args* arg = malloc(sizeof(thread_args));
			arg->polymer = line;
			arg->unit = c;
			pthread_create(&part2_t[c-'a'],&attr,part2,arg);
		}
		for(int i=0; i<26; i++) {
			pthread_join(part2_t[i],NULL);
		}

		printf("part2: %d\n",shortest);
	}

	pthread_mutex_destroy(&shortest_lock);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

void* part1(void * arg) {
	char* polymer =  arg;
	printf("part1: %zu\n",strlen(react(polymer)));
	pthread_exit(0);
}
void* part2(void* arg) {
	thread_args* args = arg;
	char* polymer = malloc(strlen(args->polymer)+1);
	strcpy(polymer,args->polymer);
	removeUnit(polymer,args->unit);
	int len = strlen(react(polymer));
	pthread_mutex_lock(&shortest_lock);
	if(len<shortest) {
		shortest = len;
	}
	pthread_mutex_unlock(&shortest_lock);
	free(polymer);
	free(args);
	pthread_exit(0);
}

char* react(char* polymer) {
	int len = strlen(polymer);
	for(int i=0; i<len-1; i++) {
		if(changePolarity(polymer[i]) == polymer[i+1]) {
			memmove(polymer+i,polymer+i+2,len-i-2);
			polymer[len-2] = '\0';
			i = i-2<-1 ? -1 : i-2;
		}
	}
	return polymer;
}

char changePolarity(char unit) {
	if(unit<'a') {
		unit += 32;
	} else {
		unit -= 32;
	}
	return unit;
}

void removeUnit(char* str, char unit) {
	char polar = changePolarity(unit);
	char *dst;
	for(dst = str; *str != '\0'; str++) {
		*dst = *str;
		if(*dst != unit && *dst != polar) {
			dst++;
		}
	}
	*dst = '\0';
}
