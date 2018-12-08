#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/08.txt"

int getMetadata(int* tree, int numElem, int *pos);
int getNodeValue(int* tree, int numElem, int *pos);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int * tree  = malloc(sizeof(int));
	int numElem = 1;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.

		int found = 0;
		for(int i=0; i<strlen(line); i++) {
			if(line[i]==' ') { //new node
				numElem++;
				tree = realloc(tree, sizeof(int)*numElem);
				found = 0;
			} else if(found == 0){
				tree[numElem-1] = atoi(line+i);
				found = 1;
			}
		}
	}

	int *pos = malloc(sizeof(int));
	*pos = 0;
	printf("part1: %d\n",getMetadata(tree,numElem,pos));
	*pos = 0;
	printf("part2: %d\n",getNodeValue(tree,numElem,pos));

	free(pos);
	free(tree);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int getMetadata(int* tree, int numElem, int *pos) {
	int tot      = 0;
	int numChild = tree[*pos];
	int numMeta  = tree[(*pos)+1];
	*pos += 2;
	for(int i=0; i<numChild; i++) {
		tot += getMetadata(tree, numElem, pos);
	}
	for(int i=0; i<numMeta && *pos<numElem; i++, *pos += 1) {
		tot += tree[*pos];
	}
	return tot;
}

int getNodeValue(int* tree, int numElem, int *pos) {
	int val      = 0;
	int numChild = tree[*pos];
	int numMeta  = tree[(*pos)+1];
	int children[numChild];
	*pos += 2;
	if(numChild == 0) {
		for(int i=0; i<numMeta; i++, *pos += 1) {
			val += tree[*pos];
		}
	} else {
		for(int i=0; i<numChild; i++) {
			children[i] = getNodeValue(tree,numElem, pos);
		}
		for(int i=0; i<numMeta; i++, *pos += 1) {
			int meta = tree[*pos];
			if(meta>0 && meta<=numChild) {
				val += children[meta-1];
			}
		}
	}

	return val;
}

