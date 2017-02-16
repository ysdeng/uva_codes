/*
	shortest path
	i need to find all possible pairs
*/
#include <stdio.h>

int valid[110];
int distance[110][110];

void init() {
	int i, j;
	for(i = 0; i < 110; i++) {
		for(j = 0; j < 110; j++)
			distance[i][j] = 1e9;
	}
}

int main() {
	int testcase = 0;
	while(1) {
		testcase++;
		init();

		int i, j, k;

		int out_node, in_node;
		int max_node = 0;
		while(1) {
			scanf("%d%d", &out_node, &in_node);
			distance[out_node][in_node] = 1;

			if(out_node > in_node) {
				if(max_node < out_node) max_node = out_node;
			}
			else {
				if(max_node < in_node) max_node = in_node;
			}

			if(out_node == 0 && in_node == 0)
				break;
		}
		/*
			check end of file or not
			-> max_node == 0
		*/
		if(max_node == 0) break;

		for(i = 1; i <= max_node; i++)
			distance[i][i] = 0;

		/*
			6 for k from 1 to |V|
			7    for i from 1 to |V|
			8       for j from 1 to |V|
			9          if dist[i][j] > dist[i][k] + dist[k][j] 
			10             dist[i][j] ← dist[i][k] + dist[k][j]
			11         end if
		*/

		for(k = 1; k <= max_node; k++)
			for(i = 1; i <= max_node; i++)
				for(j = 1; j <= max_node; j++)
					if(distance[i][j] > distance[i][k] + distance[k][j])
						distance[i][j] = distance[i][k] + distance[k][j];
	
		
		int count = 0, sum = 0;

		for(i = 1; i <= max_node; i++) {
			for(j = 1; j <= max_node; j++) {
				int dis = distance[i][j];
				if(dis != 0 && dis <= 100)
					count++, sum += dis;
			}
		}

		printf("Case %d: average length between pages = %.3f clicks\n", testcase, (float)sum/count);
	}
	return 0;
}