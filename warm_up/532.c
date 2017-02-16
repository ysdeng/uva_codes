#include <stdio.h>
#include <stdbool.h>

char maze[32][32][32];
int l, r, c;
int starti, startj, startk;
// ring...
int qi[5000], qj[5000], qk[5000];
int ind[5000];
int head;
int tail;

// directions
int dir_i[] = {1, -1, 0, 0, 0, 0};
int dir_j[] = {0, 0, 1, -1, 0, 0};
int dir_k[] = {0, 0, 0, 0, 1, -1};

void init() {
	int i, j, k;

	// map init.
	for(i = 0; i < 32; i++)
		for(j = 0; j< 32; j++)
			for(k = 0; k < 32; k++)
				maze[i][j][k] = '#';

	l = r = c = 0;
	starti = startj = startk = 1;

	// queue init.
	head = tail = -1;

	//ind init. to record the steps
	for(i = 0; i < 5000; i++)
		ind[i] = 0;
	
}

int bfs(int start_i, int start_j, int start_k);

int main() {

	while(1) {
		init();

		int i, j, k;
		scanf("%d%d%d", &l, &r, &c);
		if(l == 0 && r == 0 && c == 0) break;

		for(i = 1; i <= l; i++) {
			for(j = 1; j <= r; j++) {
				scanf("%s", maze[i][j]);
				for(k = 0; k < c; k++) 
					if(maze[i][j][k] == 'S') {
						starti = i;
						startj = j;
						startk = k;
					}

			}
		}

		int min = bfs(starti, startj, startk);

		if(min == 0) puts("Trapped!");
		else printf("Escaped in %d minute(s).\n", min);

	}
	
	return 0;
}

int bfs (int start_i, int start_j, int start_k) {
	
	// how many steps to arrive end point
	int cur_steps = 0;

	// add start point into queue
	tail++;
	qi[tail] = start_i;
	qj[tail] = start_j;
	qk[tail] = start_k;
	ind[tail] = 0;
	// arrive end point
	bool finish = false;

	while (1) {
		if(tail == head) break;
		
		// pop the first point
		int fi, fj, fk;
		head++;
		head %= 5000;
		fi = qi[head];
		fj = qj[head];
		fk = qk[head];
		//cur_steps = ind[head];
		
		// add other points into queue
		// it can go six directions
		/*
			(+1, 0, 0) (-1, 0, 0) (0, +1, 0)
			(0, -1, 0) (0, 0, +1) (0, 0, -1)
		*/
		int i;
		for(i = 0; i < 6; i++) {
			int pi, pj, pk;
			pi = fi + dir_i[i];
			pj = fj + dir_j[i];
			pk = fk + dir_k[i];
			
			// think more about boundary
			if(pi > l || pj > r || pk > c) continue;
			if(pi < 1 || pj < 1 || pk < 0) continue;

			if(maze[pi][pj][pk] == '.') {
				maze[pi][pj][pk] = '#';
				tail++;
				tail %= 5000;
				qi[tail] = pi;
				qj[tail] = pj;
				qk[tail] = pk;
				ind[tail] = ind[head]+1;
			}
			else if(maze[pi][pj][pk] == 'E') {
				tail++;
				tail %= 5000;
				qi[tail] = pi;
				qj[tail] = pj;
				qk[tail] = pk;
				ind[tail] = ind[head]+1;
				finish = true;
			}
			else if(maze[pi][pj][pk] == '#')
				continue;
		}
		if(finish)
			return ind[tail];
	}
	
	return 0;
}