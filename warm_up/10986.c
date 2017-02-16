/*
	this is a shortest path problem.
	use dijkstra algorithm to solve it.
	there's a lot of node(2-20000).
	cannot use adjacency matrix to store the graph.
	and i found that edge is less then 0.5n^2.
	so edge list may be a good idea.
	QQ TLE!!!
	use heap to optimize...
	but i don't know how to implement
*/

#include <stdio.h>
#include <stdbool.h>

struct Edge {
	int a, b, w;
} edge[50000];

bool visited[20000];
int distance[20000];

void dijkstra(int S);

void init() {
	int i;
	for(i = 0; i < 20000; i++) {
		visited[i] = false;
		distance[i] = 2147483647;
	}
}


/* input: n, m, S, T
	n: num of nodes
	m: next m lines construct the graph
	S: starting node
	T: target node
*/
int n, m, S, T;

int main () {

	int testcase;
	scanf("%d", &testcase);
	int i, j, k;
	for(i = 1; i <= testcase; i++) {
		init();
		/* input: n, m, S, T
			n: num of nodes
			m: next m lines construct the graph
			S: starting node
			T: target node
		*/
		
		scanf("%d%d%d%d", &n, &m, &S, &T);
		for(j = 0; j < m; j++) {
			/*
				each line contains 3 numbers: a, b, w
				there's an edge between a and b.
				and its weight is w.
			*/
			scanf("%d%d%d", &edge[j].a, &edge[j].b, &edge[j].w);

		}
		dijkstra(S);
		// print result start with "i" not "i+1"
		printf("Case #%d: ", i);
		if(distance[T] != 2147483647) printf("%d\n", distance[T]);
		else puts("unreachable");
	}
	return 0;
}

void dijkstra(int S) {
	int i, j, k;
	distance[S] = 0;

	for(i = 0; i < n; i++)
		visited[i] = false;

	for(i = 0; i < n; i++) {
		
		int min_p = -1, min = 2147483647;
		for (j = 0; j < n; j++) {
			if (!visited[j] && distance[j] < min) {
				min_p = j;
				min = distance[j];
			}
		}
		
		if(min_p == -1) break;
		visited[min_p] = true;
 
		for (j = 0; j < m; j++) {
			if (edge[j].a == min_p) {
				int out_node = edge[j].b, w = edge[j].w;

				if (!visited[out_node] 
					&& distance[min_p] + w < distance[out_node]) {
					distance[out_node] = distance[min_p] + w;
				}
			}
			else if (edge[j].b == min_p) {
				int out_node = edge[j].a, w = edge[j].w;

				if (!visited[out_node] 
					&& distance[min_p] + w < distance[out_node]) {
					distance[out_node] = distance[min_p] + w;
				}
			}
			
		}
			
	}

}