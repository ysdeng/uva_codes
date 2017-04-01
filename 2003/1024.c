#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DOLLAR 1024

typedef struct {
	char name[9];
	int value;
	int duplicate;
} Symbol;
Symbol symbols[128];
int symbolsCount;

typedef struct {
	int start;
	int refs[512];
	int refsCount;
	unsigned short bytes[8192];
	int bytesCount;
} Object;
Object objects[1024];
int objectsCount;

unsigned short charToHex(char in) {
	if(in == '0') return 0x0;
	if(in == '1') return 0x1;
	if(in == '2') return 0x2;
	if(in == '3') return 0x3;
	if(in == '4') return 0x4;
	if(in == '5') return 0x5;
	if(in == '6') return 0x6;
	if(in == '7') return 0x7;
	if(in == '8') return 0x8;
	if(in == '9') return 0x9;
	if(in == 'A') return 0xA;
	if(in == 'B') return 0xB;
	if(in == 'C') return 0xC;
	if(in == 'D') return 0xD;
	if(in == 'E') return 0xE;
	if(in == 'F') return 0xF;
	return 0;
	/*
	unsigned short a = 0;
	if(in >= '0' && in <= '9') a = in - '0';
	else a = in - 'A' + 10;
	return (unsigned short)a;
	*/
}

int cmp(const void *pa,const void *pb) {
	Symbol *a = (Symbol *)pa;
	Symbol *b = (Symbol *)pb;
	return strcmp(a->name, b->name);
}

int main () {
	int i, j, k, l;
	int Case = 0;
	while(1) {
		int line = 0;
		char op[2];
		/* simple init */
		symbolsCount = 0;
		objectsCount = 1;
		objects[0].start = 0x100;
		objects[0].bytesCount = 0;
		objects[0].refsCount = 0;

		while(1) {
			scanf("%s", op);
			
			if(op[0] == 'D') {
				char Dname[9]; int Dvalue;
				scanf("%s%x", Dname, &Dvalue);
				bool existed = false;
				for(i = 0; i < symbolsCount; i++) {
					if(strcmp(Dname, symbols[i].name) == 0) {
						if(symbols[i].value != -1)
							symbols[i].duplicate = 1;
						else 
							symbols[i].value = objects[objectsCount-1].start + Dvalue;
						existed = true;
						break;
					}
				}
				if(!existed) {
					strcpy(symbols[i].name, Dname);
					symbols[i].value = objects[objectsCount-1].start + Dvalue;
					symbols[i].duplicate = 0;
					symbolsCount++;
				}
			}
			else if(op[0] == 'E') {
				char Ename[9];
				scanf("%s", Ename);
				bool existed = false;
				for(i = 0; i < symbolsCount; i++) {
					if(strcmp(Ename, symbols[i].name) == 0) {
						existed = true;
						objects[objectsCount-1].refs[objects[objectsCount-1].refsCount++] = i;
						break;
					}
				}
				if(!existed) {
					strcpy(symbols[symbolsCount].name, Ename);
					symbols[symbolsCount].value = -1;
					symbols[i].duplicate = 0;
					objects[objectsCount-1].refs[objects[objectsCount-1].refsCount++] = symbolsCount;
					symbolsCount++;
				}
			}
			else if(op[0] == 'C') {
				int scanCount;
				char CName[3];
				scanf("%x", &scanCount);
				for(i = 0; i < scanCount; i++) {
					scanf("%s", CName);
					if(CName[0] == '$') {
						objects[objectsCount-1].bytes[objects[objectsCount-1].bytesCount++] = DOLLAR;
					}
					else {
						int len = strlen(CName);
						unsigned short ttt;
						ttt = 0;
						for(j = 0; j < len; j++) {
							if(j) ttt *= 16;
							ttt += charToHex(CName[j]);
						}
						objects[objectsCount-1].bytes[objects[objectsCount-1].bytesCount++] = ttt;
					}
				}
			}
			else if(op[0] == 'Z'){
				objects[objectsCount].start = objects[objectsCount-1].start + objects[objectsCount-1].bytesCount;
				objects[objectsCount].refsCount = 0;
				objects[objectsCount].bytesCount = 0;
				objectsCount++;
			}
			else if(op[0] == '$') break;
			line++;
		}
		if(line == 0) break;

		/* checksum calculating */
		
		int checksum = 0;
		for (i = 0; i < objectsCount; i++) {
			for (j = 0; j < objects[i].bytesCount; j++) {
				
				if (objects[i].bytes[j] == DOLLAR) {
					if (symbols[objects[i].refs[objects[i].bytes[j+1]]].value < 0) {
						objects[i].bytes[j] = objects[i].bytes[j+1] = 0;
					}
					else {
						objects[i].bytes[j] = symbols[objects[i].refs[objects[i].bytes[j+1]]].value / (16*16);
						objects[i].bytes[j+1] = symbols[objects[i].refs[objects[i].bytes[j+1]]].value & 0x000000ff;
					}
				}
				checksum = (checksum << 1 & 0x0000ffff) | ((checksum >>15&1));
				checksum += objects[i].bytes[j];
				checksum &= 0x0000ffff;
				
			}
		}

		/* output */
		if(Case) puts("");
		printf("Case %d: checksum = %04X\n", ++Case, checksum);
		printf(" SYMBOL   ADDR\n");
    	printf("--------  ----\n");
    	qsort(symbols, symbolsCount, sizeof(Symbol), cmp);
    	for(i = 0; i < symbolsCount; i++) {
    		printf("%-8s  ", symbols[i].name);
    		if(symbols[i].value == -1)
    			printf("????");
    		else printf("%04X", symbols[i].value);
    		if(symbols[i].duplicate == 1) printf(" M");
    		puts("");
    	}
	}
	return 0;
}