#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxN 50
#define MaxM 100
#define MaxL 250
#define SHIFT 100
typedef struct {
	int x, y;
	int len;
	int wait;
	int dir;
} AntsInfo;

int Direct[4][2]={-1, 0,
				0, 1,
				1, 0,
				0, -1};

/*-
	N 有幾筆測資
	n 有幾條路
	m 螞蟻數量
	D 幾秒產生一隻
-*/
int N, n, m, D; 

int finishCount, startCount;
int Rs;
int T;
int ex, ey;

int route[MaxN*MaxL];

/*- map information -*/
int map[MaxL+1][MaxL+1];
int AntsIndex[MaxL+1][MaxL+1][4];

int list[MaxM];
AntsInfo ant[MaxM];

void Input();
void walking();
void simulate();
void Output(int count) ;

int main() {
	int cases;
	int X, Y;
	scanf("%d", &N);
	for(cases = 1; cases <= N; cases++) {
		/*- read input and some data initialization -*/
		Input();
		/*- simulate -*/
		simulate();
		/*- generate output -*/
		Output(cases);
	}
	return 0;
}

void Input() {
	int i, j, k;
	int t, x1, y1, x2, y2;
	scanf("%d%d%d", &n, &m, &D);
	x1 = y1 = Rs = 0;

	for(i = 0; i < n; i++) {
		scanf("%d%d",&x2,&y2);
		if(x1 > x2) t = 0;
		if(y1 < y2) t = 1;
		if(x1 < x2) t = 2;
		if(y1 > y2) t = 3;
		for(;x1 != x2 || y1 != y2;) {
			route[Rs] = t;
			Rs++;
			x1 += Direct[t][0];
			y1 += Direct[t][1];
		}
	}
	finishCount = startCount = 0;
	for(i = 0; i <= MaxL; i++)
		for(j = 0; j <= MaxL; j++)
			for(k = 0; k < 4; k++)
				AntsIndex[i][j][k] = -1;
}

void simulate() {
	int X, Y;
	X = Y = 100;
	ex = ey = -1;
	for( T = 0; finishCount < m; T++) {
		if(T < Rs) {
			map[X][Y] = route[T];
			X += Direct[route[T]][0];
			Y += Direct[route[T]][1];
			if(T == Rs-1) {
				ex = X;
				ey = Y;
			}
		}
		if( T % D == 0 && startCount < m)
		{
			if(AntsIndex[100][100][map[100][100]])
				AntsIndex[100][100][map[100][100]] = startCount;
			ant[startCount].x = 100;
			ant[startCount].y = 100;
			ant[startCount].len = 0;
			ant[startCount].wait = 0;
			ant[startCount].dir = map[100][100];
			startCount++;
		}
		walking();
	}
}

void walking() {
	bool ok;
	int i, j, k, l;
	int x, y;
	int d, p, tmp;
	int go[MaxM];
	memset(go, 0, sizeof(go));

	ok = 0;
	/*- check all ants arrive target point -*/
	for(i = 0; i < startCount; i++)
		if(ant[i].x < 0)
			ok++;

	/*- 往前走一步看看 -*/
	for(i = 0; i < startCount; i++) {
		if(ant[i].x >= 0) {
			x = ant[i].x, y = ant[i].y;
			for(j = 0; j < 4; j++) {
				if(AntsIndex[x][y][j] >= 0) {
					tmp = AntsIndex[x][y][j];
					if(ant[tmp].wait > ant[i].wait
						|| (ant[tmp].wait == ant[i].wait && ant[tmp].len > ant[i].len)) {
						p = 1, go[i] = 1; ok++;
						break;
					}
				}
			}
		}
	}

	do {
		ok = 0;
		for(i = 0; i < startCount; i++) {
			if(!go[i] && ant[i].x > 0) {
				d = map[ant[i].x][ant[i].y];
				x = ant[i].x + Direct[d][0];
				y = ant[i].y + Direct[d][1];
				if(AntsIndex[x][y][d] >= 0 && go[AntsIndex[x][y][d]] == 1) {
					go[i] = 1, ok = 1;
					continue;
				}
			}
		}
	} while(ok);

	for(i = 0; i < startCount; i++) {
		if(!go[i] && ant[i].x >= 0) {
			ant[i].len++;
			ant[i].wait = 0;
			AntsIndex[ant[i].x][ant[i].y][ant[i].dir] = -1;
		}
		else if(ant[i].x >= 0)
			ant[i].wait++;
	}

	for(i = 0; i < startCount; i++) {
		if(!go[i] && ant[i].x >= 0) {
			x = ant[i].x, y = ant[i].y;
			if(x == SHIFT && y == SHIFT && i != startCount-1) {
				AntsIndex[SHIFT][SHIFT][map[SHIFT][SHIFT]] = i+1;
			}
			d = map[x][y];
			ant[i].x += Direct[d][0];
			ant[i].y += Direct[d][1];
			ant[i].dir = d;
			if(ant[i].x == ex && ant[i].y == ey) {
				list[finishCount] = i;
				finishCount++;
				ant[i].x = -1;
			}
			else
				AntsIndex[ant[i].x][ant[i].y][d]=i;
		}
	}

}

void Output(int count) {
	int i;
	printf("Case %d:\n", count);
	printf("Carl finished the path at time %d\n", ant[0].len+1);
	printf("The ants finished in the following order:\n");
	printf("%d", list[0]);
	for(i = 1; i < m; i++)
		printf(" %d", list[i]);
	printf("\n");
	printf("The last ant finished the path at time %d\n", T+1);
	if(count < N)
		printf("\n");
}