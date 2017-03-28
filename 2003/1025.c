/*
	simple DP
*/
#include <stdio.h>
#include <stdbool.h>

#define MAX_TIME 260
#define MAX_STATION 52
#define INFINITE 1e9
#define MAX_TRAIN 52
#define min(a,b) ((a>b)?(b):(a))

bool FTimeTable[MAX_STATION][MAX_TIME];
bool BTimeTable[MAX_STATION][MAX_TIME];

int duration[MAX_STATION];
int FArrivalTime[MAX_TRAIN][MAX_STATION];
int BArrivalTime[MAX_TRAIN][MAX_STATION];

int waitingTime[MAX_STATION][MAX_TIME];

void init() {
	int i, j;
	for(i = 0; i < MAX_STATION; i++) {
		duration[i] = 0;
		for(j = 0; j < MAX_TIME; j++) {
			FTimeTable[i][j] = false;
			BTimeTable[i][j] = false;
			waitingTime[i][j] = INFINITE;
		}
	}
	for(i = 0; i < MAX_TRAIN; i++) {
		for(j = 0; j < MAX_STATION; j++)
			FArrivalTime[i][j] = BArrivalTime[i][j] = INFINITE;
	}
}

int main() {
	int N, T, t, M1, M2;
	int i, j, k;
	int Case = 1;
	while(~scanf("%d", &N) && N) {
		init();
		scanf("%d", &T);
		for(i = 1; i < N; i++)
			scanf("%d", &duration[i]);

		int tt;
		scanf("%d", &M1);
		for(i = 0; i < M1; i++) {
			scanf("%d", &tt);
			for(j = 1; j <= N; j++) {
				FArrivalTime[i][j] = tt;
				tt += duration[j];
			}
		}

		scanf("%d", &M2);
		for(i = 0; i < M2; i++) {
			scanf("%d", &tt);
			for(j = N; j >= 1; j--) {
				BArrivalTime[i][j] = tt;
				tt += duration[j-1];
			}
		}
		
		for(i = 0; i < M1; i++) {
			for(j = 1; j <= N; j++) {
				tt = FArrivalTime[i][j];
				if(tt <= T)
					FTimeTable[j][tt] = true;
			}
		}
		for(i = 0; i < M2; i++) {
			for(j = 1; j <= N; j++) {
				tt = BArrivalTime[i][j];
				if(tt <= T)
					BTimeTable[j][tt] = true;
			}
		}
		
		waitingTime[1][0] = 0;

		int t, w;
		int BackStation, FrontStation;
		int Min;
		for(t = 1; t <= T; t++) {
			for(i = 1; i <= N; i++) {
				BackStation = FrontStation = INFINITE;
				if((w = t - duration[i-1]) >= 0)
					if(FTimeTable[i-1][w] == true)
						BackStation = waitingTime[i-1][w];
				if((w = t - duration[i]) >= 0)
					if(BTimeTable[i+1][w] == true)
						FrontStation = waitingTime[i+1][w];
				Min = min(BackStation, FrontStation);
				Min = min(Min, waitingTime[i][t-1]+1);
				waitingTime[i][t] = Min;
			}
		}

		if(waitingTime[N][T] != INFINITE)
			printf("Case Number %d: %d\n", Case++, waitingTime[N][T]);
		else
			printf("Case Number %d: impossible\n", Case++);
	}
	return 0;
}