#include <stdio.h>
#include <stdbool.h>

int map[100][100];
int visited[100];
int point;
bool dominator[100][100];

void init() {

	point = 0;

	int i, j;
	for(i = 0; i < 100; i++) {
		visited[i] = 0;
		for(j = 0; j < 100; j++){
			map[i][j] = -1;
			dominator[i][j] = false;
		}
	}
}
void dfs(int cur_node);

int main () {
	int testcase;
	scanf("%d", &testcase);

	int i, j, k;
	for(i = 0; i < testcase; i++) {
		init();
		
		scanf("%d", &point);

		for(j = 0; j < point; j++)
			for(k = 0; k < point; k++)
				scanf("%d", &map[j][k]);

		// start dfs
		dominator[0][0] = true;
		dfs(0);
		for(j = 0; j < point; j++)
			if(visited[j]) dominator[0][j] = true;

		for(j = 1; j < point; j++) {
			if(!dominator[0][j]) continue;
			
			for(k = 0; k < point; k++) visited[k] = false;
			visited[j] = true;
			
			dfs(0);

			// check dominate or not
			for(k = 0; k < point; k++)
				if(!visited[k] & dominator[0][k])
					dominator[j][k] = true;
			dominator[j][j] = true;
		}

		// output result
		printf("Case %d:\n", i+1);
		printf("+");
		for(j = 0; j < 2*point-1; j++)
			printf("-");
		printf("+\n");
		
		for(j = 0; j < point; j++) {
			printf("|");
			for(k = 0; k < point; k++){
				if(dominator[j][k]) printf("Y|");
				else printf("N|");
			}
			puts("");
			printf("+");
			int l;
			for(l = 0; l < 2*point-1; l++)
				printf("-");
			printf("+\n");
		}

	}
	return 0;
}

void dfs(int cur_node) {
	visited[cur_node] = true;
	int i;
	for(i = 0; i < point; i++) {
		if(map[cur_node][i] == 1 && !visited[i])
			dfs(i);
	}
}