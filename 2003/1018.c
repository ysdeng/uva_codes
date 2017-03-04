/*
	this is a special case of Minimum Spanning Tree problem.
	use Kruskal's Algorithm
	time complexity is O(ElgV)
	V = 10^4, E is about 10^5
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char charmap[200][200];
int mapset[200][200];

struct Edge {
	int ai, aj; /* node a */
	int bi, bj; /* node b */
	int len; /* length between a and b */
} edge[100000];
int edgecount;

int row, col;

int bridgelen;
int bridgenum;
void findEdge();

bool Union(struct Edge e);
int Find_set(int i, int j);

void init() {
	edgecount = 0;
	bridgelen = 0;
	bridgenum = 0;
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			if(charmap[i][j] == '.') {
				mapset[i][j] = -1;
			}
			else {
				mapset[i][j] = i*col+j;
			}
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
	else if(la > lb)
		return 1;
	else
		return 0;
}

int main() {
	int caseNum = 0;
	while(~scanf("%d%d", &row, &col) && row && col) {
		int i, j, k;
		
		if(row == 0 || col == 0)
			break;
		for(i = 0; i < row; i++) {
			scanf("%s", charmap[i]);
		}

		init();

		findEdge();
		qsort((void *) edge, edgecount, sizeof(struct Edge), cmp);

		for(i = 0; i < edgecount; i++)
			Union(edge[i]);
		
		int setcount = 0;
		for(i = 0; i < row; i++) {
			for(j = 0; j < col; j++) {
				if(mapset[i][j] == (i*col+j))
					setcount++;
			}
		}
		
		if(caseNum) puts("");
		printf("City %d\n", ++caseNum);
		if(bridgenum == 0){
			if(setcount > 1) puts("No bridges are possible.");
			else puts("No bridges are needed.");
		}
		else {
			if(bridgenum == 1)
				printf("1 bridge of total length %d\n", bridgelen);
			else
				printf("%d bridges of total length %d\n", bridgenum, bridgelen);
		}
		if(setcount > 1)
			printf("%d disconnected groups\n", setcount);

	}
	return 0;
}

void findEdge() {
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			/* node[i][j] find its closest points */
			if(charmap[i][j] == '.') continue;
			if( (i+1) < row && (j+1) < col)
				if(charmap[i+1][j+1] == '#') {
					struct Edge e;
					e.ai = i, e.aj = j;
					e.bi = i+1, e.bj = j+1;
					e.len = 0;

					edge[edgecount++] = e;
				}
			/* go through col_[j-1] */
			if((j-1) >= 0) {
				for(k = i+1; k < row; k++) {
					if(charmap[k][j-1] == '#') {

						struct Edge e;
						e.ai = i, e.aj = j;
						e.bi = k, e.bj = j-1;
						e.len = k-i-1;

						edge[edgecount++] = e;

						break;
					}
				}
			}
			/* go through col_[j] */
			if((i+1) < row) {
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
			}
			/* go through col_[j+1] */
			if((j+1) < col) {
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
			}
			/* go through row_[i-1] */
			if((i-1) >= 0) {
				for(k = j+1; k < col; k++) {
					if(charmap[i-1][k] == '#') {

						struct Edge e;
						e.ai = i, e.aj = j;
						e.bi = i-1, e.bj = k;
						e.len = k-j-1;

						edge[edgecount++] = e;

						break;
					}
				}
			}
			/* go through row_[i] */
			if((j+1) < col) {
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
			}
			/* go through row_[i+1] */
			if((i+1) < row) {
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
}

/* modify following part */
bool Union(struct Edge e) {
	int set_a = Find_set(e.ai, e.aj);
    int set_b = Find_set(e.bi, e.bj);
    if (set_a != set_b) {
        mapset[set_a/col][set_a%col] = set_b;
        bridgelen += e.len;
        if(e.len)bridgenum++;
        return true;
    }
    return false;
}

int Find_set(int i, int j) {
	int setnum = mapset[i][j];
	if (setnum == (i*col+j))
        return setnum;
    mapset[i][j] = Find_set(setnum/col, setnum%col);
    return mapset[i][j];
}