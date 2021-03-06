/*
	this is a shortest path problem.
	use dijkstra algorithm to solve it.
	there's a lot of node(2-20000).
	cannot use adjacency matrix to store the graph.
	so use adjacency to store the graph
	and use heap to speed up.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
	int a, dis;
} node[50000];

struct Edge {
	int to, dis;
	struct Edge *next;
};

int heap_size;
void insert(struct Node nodes);
struct Node popout();

bool visited[20000];
int distance[20000];
struct Edge *matrix[20000];

void dijkstra(int S);

void init() {
	int i, j;
	for(i = 0; i < 20000; i++) {
		visited[i] = false;
		distance[i] = 2147483647;

		matrix[i] = (struct Edge *)malloc(sizeof(struct Edge));
		matrix[i]->next = NULL;
	}
	heap_size = 0;
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
			int a, b, w;
			scanf("%d%d%d", &a, &b, &w);

			struct Edge *eda;
			eda = (struct Edge *)malloc(sizeof(struct Edge));
			eda->to = b, eda->dis = w;
			eda->next = matrix[a]->next;
			matrix[a]->next = eda;
			
			struct Edge *edb;
			edb = (struct Edge *)malloc(sizeof(struct Edge));
			edb->to = a, edb->dis = w;
			edb->next = matrix[b]->next;
			matrix[b]->next = edb;

		}
		/*
		for(j = 0; j < n; j++) {
			struct Edge *cur = matrix[j]->next;
			while(cur != NULL) {
				printf("%d -> %d, dis %d.\n", j, cur->to, cur->dis);
				cur = cur->next;
			}
		}
		*/
		dijkstra(S);
		
		printf("Case #%d: ", i);
		if(distance[T] != 2147483647) printf("%d\n", distance[T]);
		else puts("unreachable");
	}
	return 0;
}

void dijkstra(int S) {
	int i, j, k;
	distance[S] = 0;

	for(i = 0; i < n; i++) {
		visited[i] = false;
	}

	struct Node src;
	src.a = S, src.dis = distance[S];
	insert(src);

	for(i = 0; i < n; i++) {
		
		int min_p = -1, min = 2147483647;

		while(heap_size != 0) {
			min_p = node[1].a;
			if(!visited[min_p]) break;
			struct Node a;
			a = popout();
		}

		if(min_p == -1) break;
		visited[min_p] = true;
		
		/*
		for (j = 0; j < count[min_p]; j++) {
			
			struct Node ed = matrix[min_p][j];
			if (!visited[ed.a] && distance[min_p] + ed.dis < distance[ed.a])
			{
				distance[ed.a] = distance[min_p] + ed.dis;
				struct Node addnode;
				addnode.a = ed.a, addnode.dis = distance[ed.a];
				insert(addnode);
			}
        }
        */

		struct Edge *current = matrix[min_p]->next;
		while(current != NULL) {
			int v, d;
			v = current->to, d = current->dis;
			if (!visited[v] && distance[min_p] + d < distance[v])
			{
				distance[v] = distance[min_p] + d;
				struct Node addnode;
				addnode.a = v, addnode.dis = distance[v];
				insert(addnode);
			}
			current = current->next;
		}
	}

}
/*
	heap part:
	include two functions: insert and popout
		-insert: add a new element into the heap
		-popout: remove the smallest element from the heap
*/
void insert(struct Node nodes){
    int now = ++heap_size, p;
    struct Node x;
    node[heap_size] = nodes;

    while(now > 1) {
        p = now / 2;
        if(node[now].dis - node[p].dis > 0) break;
        
        x = node[now];
        node[now] = node[p];
        node[p] = x;
        
        now = p;
    }
}

struct Node popout(){
    struct Node v = node[1], x;
    int now, change;

    node[1] = node[heap_size--];
    now = 1;
    while(now * 2 <= heap_size) {
        int fb = 1;
        if(node[2*now].dis - node[now].dis < 0)
        	fb = 0;
        else if((2 * now + 1)<= heap_size 
        	&& node[2* now + 1].dis - node[now].dis < 0)
        	fb = 0;
        if(fb) break;
        change = 2* now;
        if((2 * now + 1) <= heap_size 
        	&& node[2 * now + 1].dis - node[2 * now].dis < 0)
        	change = 2 * now + 1;
        
        x = node[change];
        node[change] = node[now];
        node[now] = x;
        
        now = change;
    }
    return v;
}