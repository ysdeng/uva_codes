/*
	classical MST problem
	i want to use array to implement set
	a set contains 'find', 'create', 'union'

*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

int location_x[510];
int location_y[510];

double distance[510];
int distance_size;

struct Edge {
	int a, b;
	double dis;
} heap[510*510];
int heap_size;
void insert(struct Edge node);
struct Edge delete();

int pointset[510];
bool Union(struct Edge e);
int Find_set(int index);

void init() {
	int i;
	for (i = 0; i < 510; i++)
	{
		location_x[i] = location_y[i] = 0;
		distance[i] = 0;
		pointset[i] = i;
	}
	distance_size = 0; heap_size = 0;
}

int main () {
	int testcase;

	int i, j, k;
	scanf("%d", &testcase);
	while(testcase--) {

		init();

		int satellite, station;
		scanf("%d%d", &satellite, &station);

		for(i = 0; i < station; i++)
			scanf("%d%d", &location_x[i], &location_y[i]);
		
		for(i = 0; i < station; i++) {
			for(j = i; j < station; j++) {
				double dis = sqrt(pow(location_x[i] - location_x[j], 2)
					+pow(location_y[i] - location_y[j], 2));
				struct Edge e;
				e.a = i; e.b = j; e.dis = dis;
				insert(e);
			}
		}

		/*
			find n edges
			n = stations-1
			need to record edge into distance[] if the edge is choosen
		*/

		int n = station-1;
		
		while(n--) {
			while(1) {
				if(Union(delete()) == true) break;
			}
		}

		printf("%.2f\n",distance[station-satellite-1]);
	}
	return 0;
}

bool Union(struct Edge e) {
	int set_a = Find_set(e.a);
    int set_b = Find_set(e.b);
    if (set_a != set_b) {
        pointset[set_a] = set_b;
        distance[distance_size++] = e.dis;
        return true;
    }
    return false;
}

int Find_set(int index) {
	if (index == pointset[index])
        return index;
    pointset[index] = Find_set(pointset[index]);
    return pointset[index];
}


void insert(struct Edge node){
    int now = ++heap_size, p;
    struct Edge x;
    heap[heap_size] = node;

    while(now > 1) {
        p = now / 2;
        if(heap[now].dis - heap[p].dis > 0) break;
        
        x = heap[now];
        heap[now] = heap[p];
        heap[p] = x;
        
        now = p;
    }
}

struct Edge delete(){
    struct Edge v = heap[1], x;
    int now, change;

    heap[1] = heap[heap_size--];
    now = 1;
    while(now * 2 <= heap_size) {
        int fb = 1;
        if(heap[2*now].dis - heap[now].dis < 0)
        	fb = 0;
        else if((2 * now + 1)<= heap_size 
        	&& heap[2* now + 1].dis - heap[now].dis < 0)
        	fb = 0;
        if(fb) break;
        change = 2* now;
        if((2 * now + 1) <= heap_size 
        	&& heap[2 * now + 1].dis - heap[2 * now].dis < 0)
        	change = 2 * now + 1;
        
        x = heap[change];
        heap[change] = heap[now];
        heap[now] = x;
        
        now = change;
    }
    return v;
}
