#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/07.txt"

#define LOCKSID 5
#define LOCKEDID 36
#define NONODE '.'
#define WORKERS 5

int hasNode(char* nodes, int numNodes, char node);
void part1(char node, int numNodes, char* nodes, int numJobs, char (*jobs)[2]);
void part2(char node, int numNodes, char* nodes, int numJobs, char (*jobs)[2], int numWorkers);
char* freeNodes(char* nodes, int numNodes, char (*jobs)[2], int numJobs);
int charcmp(const void * a, const void * b);

int main() {
	FILE * fp;
	char * line    = NULL;
	size_t len     = 0;
	char (*jobs)[2] = malloc(sizeof(char[2]));
	int numJobs    = 0;
	char* nodes = malloc(sizeof(char));
	int numNodes = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		char job[2] = {line[LOCKSID], line[LOCKEDID]};
		numJobs++;
		jobs = realloc(jobs,sizeof(char[2])*numJobs);
		jobs[numJobs-1][0] = job[0]; //First position is the node that unlocks
		jobs[numJobs-1][1] = job[1]; //Second position is the node it unlocks

		if(!hasNode(nodes,numNodes,job[0])) {
			numNodes++;
			nodes = realloc(nodes, sizeof(char)*numNodes);
			nodes[numNodes-1] = job[0];
		}
		if(!hasNode(nodes,numNodes,job[1])) {
			numNodes++;
			nodes = realloc(nodes, sizeof(char)*numNodes);
			nodes[numNodes-1] = job[1];
		}
	}

	char* avail = freeNodes(nodes,numNodes,jobs,numJobs);
	char root = avail[0]; // find unhindered node
	free(avail);

	char* nodeBackup = malloc(sizeof(char)*numNodes);
	memcpy(nodeBackup,nodes,numNodes);
	char (*jobBackup)[2] = malloc(sizeof(char[2])*numJobs);
	for(int i=0; i<numJobs; i++) {
		jobBackup[i][0] = jobs[i][0];
		jobBackup[i][1] = jobs[i][1];
	}

	printf("part1: ");
	part1(root, numNodes, nodes, numJobs, jobs);
	printf("\n");

	part2(root, numNodes, nodeBackup, numJobs, jobBackup, WORKERS);

	free(jobs);
	free(nodes);
	free(nodeBackup);
	free(jobBackup);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int hasNode(char* nodes, int numNodes, char node) {
	int found = 0;
	for(int i=0; i<numNodes; i++) {
		if(nodes[i]==node) {
			found = 1;
			break;
		}
	}
	return found;
}

char* freeNodes(char* nodes, int numNodes, char (*jobs)[2], int numJobs) {
	char *free  = malloc(sizeof(char));
	int numFree = 0;

	for(int i=0; i<numNodes; i++) { // for every node
		int found = 0;
		for(int j=0; j<numJobs; j++) { //check every job
			if(jobs[j][1]==nodes[i]) { // if the node is locked by a job
				found = 1; // don't use it
				break;
			}
		}
		if(found == 0) {
			numFree++;
			free = realloc(free,sizeof(char)*numFree);
			free[numFree-1] = nodes[i];
		}
	}
	qsort(free,numFree,sizeof(char),charcmp);//sorted string
	free = realloc(free,sizeof(char)*(numFree+1));
	free[numFree] = '\0'; //made it a proper string to do strlen
	return free;
}

void part1(char node, int numNodes, char* nodes, int numJobs, char (*jobs)[2]) {
	printf("%c",node);
	// remove jobs that rely on node
	for(int i=0; i<numJobs; i++) {
		if(jobs[i][0] == node) {
			jobs[i][0] = jobs[numJobs-1][0];
			jobs[i][1] = jobs[numJobs-1][1];
			numJobs--;
			i--;
		}
	}

	// remove node
	for(int i=0; i<numNodes; i++) {
		if(nodes[i]==node) {
			nodes[i] = nodes[numNodes-1];
			numNodes--;
			break;
		}
	}
	char* avail = freeNodes(nodes,numNodes,jobs,numJobs);
	int len = strlen(avail);
	if(len>0) { // if there are still nodes available, complete them.
		part1(avail[0],numNodes,nodes,numJobs,jobs);
	}
	free(avail);
}

int charcmp(const void * a, const void * b) {
	return ( *(char*)a - *(char*)b );
}

void part2(char node, int numNodes, char* nodes, int numJobs, char (*jobs)[2], int numWorkers) {
	char workers[numWorkers];
	int finish[numWorkers];
	int seconds = 0;
	int len = 1;

	memset(workers, NONODE, numWorkers);
	memset(finish, -1, numWorkers);

	while(len>0) {
		for(int i=0; i<numWorkers; i++) {
			if(workers[i]==NONODE) {
				char* avail = freeNodes(nodes,numNodes,jobs,numJobs);
				int len = strlen(avail);
				for(int j=0; j<len; j++) {
					int taken = 0;
					//find node not currently worked on
					for(int k=0; k<numWorkers; k++) {
						if(avail[j]==workers[k]) {
							taken = 1;
							break;
						}
					}
					if(taken == 0) {
						workers[i] = avail[j];
						finish[i] = seconds+avail[j]-'A'+61;
						break;
					}
				}
				free(avail);
			} else if(finish[i] == seconds) {
				//remove jobs
				for(int j=0; j<numJobs; j++) {
					if(jobs[j][0] == workers[i]) {
						jobs[j][0] = jobs[numJobs-1][0];
						jobs[j][1] = jobs[numJobs-1][1];
						numJobs--;
						j--;
					}
				}
				//remove node
				for(int j=0; j<numNodes; j++) {
					if(nodes[j] == workers[i]) {
						nodes[j] = nodes[numNodes-1];
						numNodes--;
						j--;
					}
				}
				workers[i] = NONODE;
				i--; // try to find another job for worker
			}
		}
		seconds++;
		char* avail = freeNodes(nodes,numNodes,jobs,numJobs);
		len = strlen(avail);
		free(avail);
	}
	printf("part2: %d\n",seconds-1);
}
