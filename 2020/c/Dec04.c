#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "../input/04.txt"

typedef struct Passport {
	char* byr;
	char* iyr;
	char* eyr;
	char* hgt;
	char* hcl;
	char* ecl;
	char* pid;
	char* cid;
} Passport;

int part1isValid(Passport pass);
int part2isValid(Passport pass);
int checkByr(char* byr);
int checkIyr(char* iyr);
int checkEyr(char* eyr);
int checkHgt(char* hgt);
int checkHcl(char* hcl);
int checkEcl(char* ecl);
int checkPid(char* pid);
void freePassport(Passport pass);

int main() {
	FILE * fp;
	char * line = NULL;
	size_t len  = 0;
	int part1   = 0;
	int part2   = 0;

	fp = fopen(INPUT, "r");
	if (fp == NULL) {
		perror(INPUT);
		exit(EXIT_FAILURE);
	}
	Passport pass = {0};
	Passport reset = pass;
	while (getline(&line, &len, fp) != -1){
		line[strcspn(line, "\r\n")] = 0; //remove line breaks.
		if(line[0] == '\0') {
			part1 += part1isValid(pass);
			part2 += part2isValid(pass);
			freePassport(pass);
			pass = reset;
		}
		char* field = strtok(line," ");
		while(field!=NULL) {
			int fieldId = field[0]+field[1]+field[2];
			switch(fieldId) {
				case 323:
					pass.hgt = malloc(strlen(field+4)+1);
					strcpy(pass.hgt,field+4);
					break;
				case 308:
					pass.ecl = malloc(strlen(field+4)+1);
					strcpy(pass.ecl,field+4);
					break;
				case 340:
					pass.iyr = malloc(strlen(field+4)+1);
					strcpy(pass.iyr,field+4);
					break;
				case 317:
					pass.pid = malloc(strlen(field+4)+1);
					strcpy(pass.pid,field+4);
					break;
				case 336:
					pass.eyr = malloc(strlen(field+4)+1);
					strcpy(pass.eyr,field+4);
					break;
				case 311:
					pass.hcl = malloc(strlen(field+4)+1);
					strcpy(pass.hcl,field+4);
					break;
				case 333:
					pass.byr = malloc(strlen(field+4)+1);
					strcpy(pass.byr,field+4);
					break;
				case 304:
					pass.cid = malloc(strlen(field+4)+1);
					strcpy(pass.cid,field+4);
					break;
				default:
					printf("unknown field \"%s\" with id %d\n",field,fieldId);
					break;
			}
			field = strtok(NULL," ");
		}
	}
	part1 += part1isValid(pass);
	part2 += part2isValid(pass);
	freePassport(pass);
	printf("part 1: %d\n", part1);
	printf("part 2: %d\n", part2);
	fclose(fp);
	free(line);
	exit(EXIT_SUCCESS);
}

int part1isValid(Passport pass) {
	return !(!pass.byr || !pass.iyr || !pass.eyr || !pass.hgt || !pass.hcl || !pass.ecl || !pass.pid);
}

int part2isValid(Passport pass) {
	int valid = 1;

	if(!pass.byr || !checkByr(pass.byr)) {
		valid = 0;
	} else if(!pass.iyr || !checkIyr(pass.iyr)) {
		valid = 0;
	} else if(!pass.eyr || !checkEyr(pass.eyr)) {
		valid = 0;
	} else if(!pass.hgt || !checkHgt(pass.hgt)) {
		valid = 0;
	} else if(!pass.hcl || !checkHcl(pass.hcl)) {
		valid = 0;
	} else if(!pass.ecl || !checkEcl(pass.ecl)) {
		valid = 0;
	} else if(!pass.pid || !checkPid(pass.pid)) {
		valid = 0;
	}
	return valid;
}

int checkByr(char* byr) {
	int valid=1;
	int year = (int)strtol(byr,NULL,10);
	if(year<1920 || year>2002) {
		valid=0;
	}
	return valid;
}
int checkIyr(char* iyr) {
	int valid=1;
	int year = (int)strtol(iyr,NULL,10);
	if(year<2010 || year>2020) {
		valid=0;
	}
	return valid;
}
int checkEyr(char* eyr) {
	int valid=1;
	int year = (int)strtol(eyr,NULL,10);
	if(year<2020 || year > 2030) {
		valid=0;
	}
	return valid;
}
int checkHgt(char* hgt) {
	int valid=1;
	char* unit;
	int height = (int)strtol(hgt,&unit, 10);
	if(!strcmp(unit,"cm") && (height < 150 || height > 193)) {
		valid=0;
	} else if(!strcmp(unit,"in") && (height < 59 || height > 76)) {
		valid=0;
	} else if(unit[0] == '\0') {
		valid=0;
	}
	return valid;
}
int checkHcl(char* hcl) {
	int valid = 1;
	char* colour = hcl+1;
	int len   = strlen(colour);
	if(hcl[0]!='#' || len!=6) {
		valid=0;
	} else {
		for(int i=0; i<len; i++) {
			char c = colour[i];
			if((c<'0' || c>'9') && (c<'a' || c>'f')) {
				valid=0;
				break;
			}
		}
	}
	return valid;
}
int checkEcl(char* ecl) {
	int valid=0;
	if(!strcmp(ecl,"amb") || !strcmp(ecl,"blu") || !strcmp(ecl,"brn") ||
	   !strcmp(ecl,"gry") || !strcmp(ecl,"grn") || !strcmp(ecl,"hzl") ||
	   !strcmp(ecl,"oth")) {
		valid=1;
	}
	return valid;
}
int checkPid(char* pid) {
	int valid=1;
	int len = strlen(pid);
	if(len!=9) {
		valid=0;
	} else {
		for(int i=0; i<len; i++) {
			if(!(pid[i]>='0' && pid[i]<='9')) {
				valid=0;
				break;
			}
		}
	}
	return valid;
}

void freePassport(Passport pass) {
	if(pass.byr != 0) {
		free(pass.byr);
	}
	if(pass.iyr != 0) {
		free(pass.iyr);
	}
	if(pass.eyr != 0) {
		free(pass.eyr);
	}
	if(pass.hgt != 0) {
		free(pass.hgt);
	}
	if(pass.hcl != 0) {
		free(pass.hcl);
	}
	if(pass.ecl != 0) {
		free(pass.ecl);
	}
	if(pass.pid != 0) {
		free(pass.pid);
	}
	if(pass.cid != 0) {
		free(pass.cid);
	}
	return;
}
