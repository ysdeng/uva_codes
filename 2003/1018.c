/*
	this is a special case of Minimum Spanning Tree problem.
	use Kruskal's Algorithm
	time complexity is O(ElgV)
	V = 10^4, E is about 10^5
*/
#include <stdio.h>
#include <stdlib.h>

char charmap[100][100];
int mapset[100][100];

struct Edge {
	int ai, aj; /* node a */
	int bi, bj; /* node b */
	int len; /* length between a and b */
} edge[100000];
int edgecount;

int row, col;

void findEdge();

void init() {
	edgecount = 0;

	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			if(charmap[i][j] == '.')
				mapset[i][j] = -1;
			else
				mapset[i][j] = i*col+j;
		}
	}
}

int cmp(const void * a, const void * b) {
	struct Edge *edge_a=(struct Edge *)a;
	struct Edge *edge_b=(struct Edge *)b;
	int la = edge_a->len;
	int lb = edge_b->len;
	if(la < lb)
		return -1;
	else
		return 1;
}


int main() {
	int caseNum = 0;
	while(1) {
		int i, j, k;
		
		scanf("%d%d", &row, &col);
		if(row == 0 && col == 0)
			break;
		for(i = 0; i < row; i++) {
			scanf("%s", charmap[i]);
		}

		init();

		findEdge();
		qsort((void *) edge, edgecount, sizeof(edge[0]), cmp);

		if(caseNum) puts("");
		printf("City %d\n", ++caseNum);
		
	}
	return 0;
}

void findEdge() {
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			/* node[i][j] find its closest points */
			if(charmap[i][j] == '.') continue;
			if(i+1 < row && j+1 < col)
				if(charmap[i+1][j+1] == '#') {
					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = i+1, e.bj = j+1;
					e.len = 0;

					edge[edgecount++] = e;
				}

			/* go through col_[j] */
			for(k = i+1; k < row; k++) {
				if(charmap[k][j] == '#') {

					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = k, e.bj = j;
					e.len = k-i-1;

					edge[edgecount++] = e;

					break;
				}
			}
			/* go through col_[j+1] */
			for(k = i+1; k < row; k++) {
				if(charmap[k][j+1] == '#') {

					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = k, e.bj = j+1;
					e.len = k-i-1;

					edge[edgecount++] = e;

					break;
				}
			}
			/* go through row_[i] */
			for(k = j+1; k < col; k++) {
				if(charmap[i][k] == '#') {

					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = i, e.bj = k;
					e.len = k-j-1;

					edge[edgecount++] = e;

					break;
				}
			}
			/* go through row_[i+1] */
			for(k = j+1; k < col; k++) {
				if(charmap[i+1][k] == '#') {

					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = i+1, e.bj = k;
					e.len = k-j-1;

					edge[edgecount++] = e;

					break;
				}
			}
		}
	}
}