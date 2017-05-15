#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 120

int dayPerMon1[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int dayPerMon2[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

typedef struct {
	int day, month, year;
	int sorf; /*- start or finish -*/
} DATE;
DATE date[100];
int dateCount;

typedef struct {
	DATE in, out;
} Record;
Record nx[100], nr[100];
int nxCount, nrCount;
int NX, NR;

Record output[200];
int outputCount;

void readInput ();
int cmp (const void *a, const void *b);
int mergeDay (DATE old, DATE new);
void FindDiff ();

int main () {
	int i, j, k;
	while(~scanf("%d%d", &NX, &NR)) {
		if(NX == 0 && NR == 0) break;

		/*- read input data -*/
		readInput ();
		/*- find all diff sets -*/
		FindDiff ();
		/*- print output -*/
	}
	return 0;
}

int cmp (const void *a, const void *b) {
	DATE *aa = (DATE *) a;
	DATE *bb = (DATE *) b;

	if(aa->year == bb->year) {
		if(aa->month == bb->month) {
			return(aa->day > bb->day)?1:-1;
		}
		else return(aa->month > bb->month)?1:-1;
	}
	else return (aa->year > bb->year)?1:-1;
}

void readInput () {
	int i, j, k;
	char ss[10];
	puts("============");
	puts("=====NX=====");
	dateCount = 0;
	nxCount = 0;
	if(NX != 0) {
		for(i = 0; i < NX; i++) {
			for(j = 0; j < 2; j++) {
				scanf("%s", ss);
				int dd = atoi(ss);
				date[dateCount].day = dd % 100;
				date[dateCount].month = (dd/100)%100;
				date[dateCount].year = (dd/10000);
				date[dateCount].sorf = j;
				dateCount++;
			}
		}

		/*- merge some date -*/
		qsort(date, dateCount, sizeof(DATE), cmp);

		/*- plane sweeping -*/
		int in;
		in = 0;
		DATE s, f;
		bzero(&s, sizeof(DATE));
		bzero(&f, sizeof(DATE));

		for(i = 0; i < dateCount; i++) {
			if (date[i].sorf) {
				in--;
				if(in == 0) {
					f = date[i];

					if(nxCount) {
						if(mergeDay(nx[nxCount-1].out, s)) {
							nx[nxCount-1].out = f;
						}
						else {
							nx[nxCount].in = s;
							nx[nxCount].out = f;
							nxCount++;
						}
					}
					else {
						nx[nxCount].in = s;
						nx[nxCount].out = f;
						nxCount++;
					}

				}
			}
			else {
				/*- i'm the first -*/
				if(in == 0) {
					s = date[i];
				}
				in++;
			}
		}

		for(i = 0; i < dateCount; i++) {
			printf("%d/%d/%d %d\n", date[i].year, date[i].month, date[i].day, date[i].sorf);
		}
		puts("=====merged=====");
		for(i = 0; i < nxCount; i++) {
			printf(" in: %d/%d/%d\n", nx[i].in.year, nx[i].in.month, nx[i].in.day);
			printf("out: %d/%d/%d\n", nx[i].out.year, nx[i].out.month, nx[i].out.day);
		}
	}
	
	puts("=====NR=====");
	dateCount = 0;
	nrCount = 0;
	if(NR != 0) {
		for(i = 0; i < NR; i++) {
			for(j = 0; j < 2; j++) {
				scanf("%s", ss);
				int dd = atoi(ss);
				date[dateCount].day = dd % 100;
				date[dateCount].month = (dd/100)%100;
				date[dateCount].year = (dd/10000);
				date[dateCount].sorf = j;
				dateCount++;
			}
		}

		/*- merge some date -*/
		qsort(date, dateCount, sizeof(DATE), cmp);

		/*- plane sweeping -*/
		int in;
		in = 0;
		DATE s, f;
		bzero(&s, sizeof(DATE));
		bzero(&f, sizeof(DATE));

		for(i = 0; i < dateCount; i++) {
			if (date[i].sorf) {
				in--;
				if(in == 0) {
					f = date[i];
					
					if(nrCount) {
						if(mergeDay(nr[nrCount-1].out, s)) {
							nr[nrCount-1].out = f;
						}
						else {
							nr[nrCount].in = s;
							nr[nrCount].out = f;
							nrCount++;
						}
					}
					else {
						nr[nrCount].in = s;
						nr[nrCount].out = f;
						nrCount++;
					}

				}
			}
			else {
				/*- i'm the first -*/
				if(in == 0) {
					s = date[i];
				}
				in++;
			}
		}

		for(i = 0; i < dateCount; i++) {
			printf("%d/%d/%d %d\n", date[i].year, date[i].month, date[i].day, date[i].sorf);
		}

		puts("=====merged=====");
		for(i = 0; i < nrCount; i++) {
			printf(" in: %d/%d/%d\n", nr[i].in.year, nr[i].in.month, nr[i].in.day);
			printf("out: %d/%d/%d\n", nr[i].out.year, nr[i].out.month, nr[i].out.day);
		}
	}
}

int mergeDay (DATE old, DATE new) {
	/*- add 1 day -*/
	old.day++;

	/*- reformat the old date -*/
	if(old.year % 4 == 0) {
		if(old.day > dayPerMon2[old.month-1]) {
			old.day = old.day - (dayPerMon2[old.month-1]);
			old.month++;
			if(old.month > 12) {
				old.month = 1;
				old.year++;
			}
		}
	}
	else {
		if(old.day > dayPerMon1[old.month-1]) {
			old.day = old.day - (dayPerMon1[old.month-1]);
			old.month++;
			if(old.month > 12) {
				old.month = 1;
				old.year++;
			}
		}
	}

	/*- we are the same -*/
	if(old.day == new.day && old.month == new.month && old.year == new.year) return 1;
	else return 0;
}