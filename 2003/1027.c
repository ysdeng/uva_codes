#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 1e9
#define max(a,b) ((a)>(b))?(a):(b)
int distance[100];
bool visited[100];
void dijkstra();
int matrix[100][100];

void init() {
	int i, j;
	for(i = 0; i < 100; i++) {
		distance[i] = INF;
		visited[i] = false;
		for(j = 0; j < 100; j++)
			matrix[i][j] = 0;
	}
}

int charToIndex (char in) {
	if(in >= 'a' && in <= 'z') return in-'a';
	else return in-'A'+26;
}

int main() {
	int i, j, k;

	int testcase = 0;
	int edgeCount;
	char node1[3], node2[3];
	int src, dst;
	while(~scanf("%d", &edgeCount) && edgeCount != -1) {
		init();
		for(i = 0; i < edgeCount; i++) {
			scanf("%s%s", node1, node2);
			int a, b;
			a = charToIndex(node1[0]);
			b = charToIndex(node2[0]);
			if (a != b) {
				matrix[a][b] = matrix[b][a] = 1;
			}
		}
		scanf("%d%s%s", &i, node1, node2);
		src = charToIndex(node1[0]);
		dst = charToIndex(node2[0]);

		distance[dst] = i;
		dijkstra();
		
		printf("Case %d: ", ++testcase);
		printf("%d\n", distance[src]);
	}
	return 0;
}

void dijkstra() {
	int i, j, k;
	int n = 52;
	for(i = 0; i < n; i++) {
		visited[i] = false;
	}

	for(i = 0; i < 52; i++) {
		
		int min_p = -1, min = INF;

		for(j = 0; j < 52; j++) {
			if(min > distance[j] && !visited[j]) {
				min_p = j;
				min = distance[j];
			}
		}
		
		if(min_p == -1) break;
		visited[min_p] = true;

		int d;
		for(j = 0; j < 52; j++) {
			if(0 == matrix[min_p][j]) continue;

			if(min_p < 26) d = min+1;
			else {
				d = max(min + 1, min * 20/19 - 5);
				while (d - (d + 19) / 20 < min) ++d;
			}

			if(!visited[j] && d < distance[j]) {
				distance[j] = d;
			}
		}
	}
	
}
