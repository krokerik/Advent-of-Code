#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/07.txt"

typedef struct Bag Bag;

struct Bag {
	char* hue;
	char* colour;
	Bag** bags;
	int* amounts;
	int numRules;
};

Bag* createBag(char* hue, char* colour);
Bag* findBag(Bag*** bags, int* numBags, char* hue, char* colour);
void addBag(Bag* bag, Bag* subBag, int amount);
int validParent(Bag* bags, char* hue, char* colour);
long totalChildren(Bag* root);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int part1   = 0;
	int numBags = 0;
	Bag** bags   = malloc(sizeof(Bag*));

	bags[0] = NULL;


	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		char* field  = strtok(line," ");
		char* hue    = field;
		char* colour = strtok(NULL," ");
		field = strtok(NULL," "); //bags
		field = strtok(NULL," "); //contain
		Bag* bag = findBag(&bags,&numBags,hue,colour);
		field = strtok(NULL," ,"); //number or "no"
		while(field!=NULL) {
			char* remainder;
			int num = (int)strtol(field,&remainder,10);
			if(!strcmp(remainder,"no")) {
				break;
			}
			hue    = strtok(NULL," ,");
			colour = strtok(NULL," ,");
			Bag* subBag = findBag(&bags,&numBags,hue,colour);
			addBag(bag,subBag,num);
			field  = strtok(NULL," ,"); //bag(s)
			field  = strtok(NULL," ,"); //bag(s)
		}
	}
	for(int i=0; i<numBags; i++) {
		part1 += validParent(bags[i],"shiny","gold");
	}
	printf("part 1: %d\n", part1);
	printf("part 2: %ld\n", totalChildren(findBag(&bags, &numBags, "shiny","gold")));
	for(int i=0; i<numBags; i++) {
		free(bags[i]->hue);
		free(bags[i]->colour);
		free(bags[i]->bags);
		free(bags[i]->amounts);
		free(bags[i]);
	}
	fclose(fp);
	free(line);
	free(bags);
	exit(EXIT_SUCCESS);
}

Bag* createBag(char* hue, char* colour) {
	Bag* bag   = malloc(sizeof(Bag));
	bag->hue    = malloc((strlen(hue)+1)*sizeof(char));
	bag->colour = malloc((strlen(colour)+1)*sizeof(char));
	strcpy(bag->hue,hue);
	strcpy(bag->colour,colour);
	bag->bags     = malloc(sizeof(Bag*));
	bag->amounts  = malloc(sizeof(int));
	bag->numRules = 0;
	return bag;
}

Bag* findBag(Bag*** bags, int* numBags, char* hue, char* colour) {
	Bag* bag = NULL;
	for(int i=0; i<*numBags; i++) {
		if((*bags)[i] != NULL) {
			if(!strcmp((*bags)[i]->hue,hue)) {
				if(!strcmp((*bags)[i]->colour,colour)) {
					bag = (*bags)[i];
					break;
				}
			}
		}
	}
	if(bag == NULL) {
		bag = createBag(hue,colour);
		(*numBags)++;
		Bag** tmp = realloc(*bags,sizeof(Bag*) * (*numBags));
		if(tmp != NULL) {
			*bags = tmp;
		} else {
			printf("realloc failed\n");
		}
		(*bags)[*numBags-1] = bag;
	}
	return bag;
}

void addBag(Bag* bag, Bag* subBag, int amount) {
	bag->bags[bag->numRules]    = subBag;
	bag->amounts[bag->numRules] = amount;
	bag->numRules++;
	bag->bags    = realloc(bag->bags,sizeof(Bag)*(bag->numRules+1));
	bag->amounts = realloc(bag->amounts,sizeof(int)*(bag->numRules+1));
	return;
}

int validParent(Bag* root, char* hue, char* colour) {
	int found = 0;
	for(int i=0; i<root->numRules && found==0; i++) {
		if(!strcmp(root->bags[i]->hue,hue) && !strcmp(root->bags[i]->colour,colour)) {
			found = 1;
		} else {
			found = validParent(root->bags[i],hue,colour);
		}
	}
	return found;
}

long totalChildren(Bag* root) {
	long tot = 0;
	for(int i=0; i<root->numRules; i++) {
		tot += root->amounts[i] + totalChildren(root->bags[i]) * root->amounts[i];
	}
	return tot;
}
