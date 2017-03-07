/*
	This is a simple simulation problem.
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct Node {
	int coins[25];
	int delta[25];
	bool valid;
} map[11][11];

struct countryInfo {
	char name[25];
	int xl, yl;
	int xh, yh;
	int finishday;
} countries[25];
int countryCount;

void initMap();
bool simulation();
	int day;

int cmp(const void * a, const void * b) {
	struct countryInfo *country_a=(struct countryInfo *)a;
	struct countryInfo *country_b=(struct countryInfo *)b;
	int da = country_a->finishday;
	int db = country_b->finishday;
	if(da < db)
		return -1;
	else if(da > db)
		return 1;
	else {
		char *cha = country_a->name;
		char *chb = country_b->name;
		return strcmp(cha,chb);
	}
}

int main() {
	int i, j, k;
	int testcaseNum = 1;
	while(~scanf("%d", &countryCount) && countryCount != 0) {
		for(i = 0; i < countryCount; i++) {
			scanf("%s%d%d%d%d", countries[i].name, 
				&countries[i].xl, &countries[i].yl, 
				&countries[i].xh, &countries[i].yh);
			countries[i].finishday = -1;
		}
		
		initMap();
		bool a = false;
		while(!a) {
			a = simulation();
		}
		qsort((void *) countries, countryCount,
			sizeof(struct countryInfo), cmp);

		printf("Case Number %d\n", testcaseNum++);
		for(i = 0; i < countryCount; i++)
			printf("   %s   %d\n", countries[i].name, countries[i].finishday);
	}
	return 0;
}

void initMap() {
	int i, j, k, l;
	for(i = 0; i < 11; i++) {
		for(j = 0; j < 11; j++) {
			map[i][j].valid = false;
			for(k = 0; k < 25; k++) {
				map[i][j].coins[k] = 0;
				map[i][j].delta[k] = 0;
			}
		}
	}

	for(k = 0; k < countryCount; k++) {
		for(i = countries[k].xl; i <= countries[k].xh; i++) {
			for(j = countries[k].yl; j <= countries[k].yh; j++) {
				map[i][j].valid = true;
				map[i][j].coins[k] = 1000000;
			}
		}
	}

	/* init other vars */
	
	day = 0;
}

bool simulation() {
	/* check before sending money */
	int i, j, k, l;

	for(k = 0; k < countryCount; k++) {
		int cityCount = (countries[k].xh-countries[k].xl+1)
						*(countries[k].yh-countries[k].yl+1);
		int c = 0;
		/* traverse cities in this country */
		for(i = countries[k].xl; i <= countries[k].xh; i++) {
			for(j = countries[k].yl; j <= countries[k].yh; j++) {
				bool cityFinished = true;
				/* traverse motif coin in this city */
				for(l = 0; l < countryCount; l++) {
					if(map[i][j].coins[l] == 0)
						cityFinished = false;
				}
				if(cityFinished) c++;
			}
		}
		if(cityCount == c) {
			if(countries[k].finishday == -1)
				countries[k].finishday = day;
		}
	}

	/* check terminate this simulation */
	bool finished = true;
	for(i = 0; i < countryCount; i++) {
		if(countries[i].finishday == -1) {
			finished = false;
		}
	}
	if(finished) return true;
	else day++;
	
	/* sending money */
	/* traverse all the map */
	for(i = 1; i < 11; i++) {
		for(j = 1; j < 11; j++) {
			if(map[i][j].valid == false) continue;
			/* for a city */
			int outmoney[25];
			/* calculate how many dollars the city need to send out*/
			for(k = 0; k < 25; k++)
				outmoney[k] = map[i][j].coins[k]/1000;

			if(i-1 >= 0)
				if(map[i-1][j].valid == true) {
					for(k = 0; k < 25; k++) {
						map[i-1][j].delta[k] += outmoney[k];
						map[i][j].coins[k] -= outmoney[k];
					}
				}
			if(i+1 < 11)
				if(map[i+1][j].valid == true) {
					for(k = 0; k < 25; k++) {
						map[i+1][j].delta[k] += outmoney[k];
						map[i][j].coins[k] -= outmoney[k];
					}
				}
			if(j-1 >= 0)
				if(map[i][j-1].valid == true) {
					for(k = 0; k < 25; k++) {
						map[i][j-1].delta[k] += outmoney[k];
						map[i][j].coins[k] -= outmoney[k];
					}
				}
			if(j+1 < 11)
				if(map[i][j+1].valid == true) {
					for(k = 0; k < 25; k++) {
						map[i][j+1].delta[k] += outmoney[k];
						map[i][j].coins[k] -= outmoney[k];
					}
				}
		}
	}

	/* after a day, sum up all money */
	for(i = 1; i < 11; i++) {
		for(j = 1; j < 11; j++) {
			if(map[i][j].valid) {
				for(k = 0; k < 25; k++) {
					map[i][j].coins[k] += map[i][j].delta[k];
					map[i][j].delta[k] = 0;
				}
			}
		}
	}
	return false;
}
