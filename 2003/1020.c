/*
	This is a simple math problem.
	in order-k:
		len = 1 / partition[k]
		total_len = numsz[k] * len
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int numsz[9]; /* how many 's' and 'z' in the map */
int partition[9]; 
int type[2187][2187];
int unit[6561][6561];

void init_para();

int order;
double input[2][2];
int c[2][2];
double dist_func();
void bridge_1(int m);
int bridge_2(int x, int y, int type, int dir, int corder);
int getLeftPart(int xx, int yy, int type, int dir);

int main() {
	init_para();
	int testcaseNum = 0;
	int i, j, k;
	while(~scanf("%d", &order) && order != 0) {
		for(i = 0; i < 2; i++)
			scanf("%lf%lf", &input[i][0], &input[i][1]);

		if(testcaseNum) puts("");
		printf("Case %d.  Distance is %.4f\n", ++testcaseNum, dist_func());
	}
	return 0;
}

void init_para() {
	int i, j, k;
	for(i = 1; i < 9; i++) {
		numsz[i] = pow(9, i-1);
		partition[i] = (int)pow(3, i) - 1;
	}

	for(i = 0; i < 2187; i++) {
		for(j = 0; j < 2187; j++) {
			if(i%2 == 0) {
				if(j%2 == 0) type[i][j] = 0;
				else type[i][j] = 1;
			}
			else {
				if(j%2 == 0) type[i][j] = 2;
				else type[i][j] = 3;
			}
		}
	}
	
	
}

double dist_func() {
	int i, j, k, l;
	/* find connecting points */
	int grid[2][2];

	for (i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			grid[i][j] = 0;
	
	double tmpf = 0.0;

	/* connecting point */
	
	int checkp[2];
	double mindis[2];
	
	double len = 1.0 / partition[order];

	for(i = 0; i < 2; i++) {
		tmpf = input[i][0] * partition[order];
		checkp[0] = (int)tmpf;
		tmpf = input[i][1] * partition[order];
		checkp[1] = (int)tmpf;
		
		mindis[i] = partition[order];

		for(j = 0; j < 2; j++) {
			for(k = 0; k < 2; k++) {
				tmpf = sqrt(pow((input[i][0]*partition[order]-(checkp[0]+j)),2)
						+ pow((input[i][1]*partition[order]-(checkp[1]+k)),2));
				if(tmpf < mindis[i]) {
					mindis[i] = tmpf;
					c[i][0] = (checkp[0]+j);
					c[i][1] = (checkp[1]+k);
				}
			}
		}
		mindis[i] /= partition[order];
	}
	/*
	printf("%d %d\n", c[0][0], c[0][1]);
	printf("%d %d\n", c[1][0], c[1][1]);
	*/
	double dis = 0.0;
 	for(i = 0; i < 2; i++) {
 		dis += mindis[i];
 	}

 	int d1 = bridge_2(c[0][0], c[0][1], 1, 1, order);
 	int d2 = bridge_2(c[1][0], c[1][1], 1, 1, order);
 	/*
 	printf("d1 = %d\nd2 = %d\n", d1, d2);
	*/
 	dis += (double)(abs(d2-d1)) * len;
	
	return dis;
}

int bridge_2(int x, int y, int type, int dir, int corder) {
	/*
		type 1: z, -1: s
		dir  1: >, -1: <
	*/
 	if(corder == 1) return getLeftPart(x, y, type, dir);
 	else {
 		int x_pr = x%((int)pow(3, corder-1));
 		int y_pr = y%((int)pow(3, corder-1));
 		x /= (int)pow(3, corder-1);
 		y /= (int)pow(3, corder-1);
 		int left = getLeftPart(x, y, type, dir)*((int)pow(9, corder-1));
 		if((x%2) != (y%2)) type *= -1;
 		if(y%2) dir *= -1;
 		return bridge_2(x_pr, y_pr, type, dir, corder-1)
 			+ left;
 	}
}

int getLeftPart(int xx, int yy, int type, int dir) {
	/*
		type 1: z, -1: s
		dir  1: >, -1: <
	*/
	int dp = (xx % 3)+(yy % 3)*3;
 	if(type == 1 && dir == 1) {
 		/* *z */
 		if(dp == 3) dp = 5;
	 	else if(dp == 5) dp = 3;
	 	return dp;
 	}
 	else if(type == -1 && dir == 1) {
 		/* *s */
 		if(dp == 0) dp = 2;
 		else if(dp == 2) dp = 0;
 		else if(dp == 6) dp = 8;
 		else if(dp == 8) dp = 6;
 		return abs(dp-8);
 	}
 	else if(type == -1 && dir == -1) {
 		/* s* */
 		if(dp == 0) dp = 2;
 		else if(dp == 2) dp = 0;
 		else if(dp == 6) dp = 8;
 		else if(dp == 8) dp = 6;
 		return dp;
 	}
 	else if(type == 1 && dir == -1) {
 		/* z* */
 		if(dp == 3) dp = 5;
	 	else if(dp == 5) dp = 3;
	 	return abs(dp-8);
 	}
 	return 0;
}