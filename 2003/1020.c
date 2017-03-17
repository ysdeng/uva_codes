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
void init_para();

int order;
float input[2][2];
float dist_func();

int main() {
	init_para();
	int testcaseNum = 1;
	int i, j, k;
	while(~scanf("%d", &order) && order != 0) {
		for(i = 0; i < 2; i++)
			scanf("%f%f", &input[i][0], &input[i][1]);

		//float dist = dist_func();
		printf("Case %d.\n", testcaseNum++);
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

	/*
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			printf("%2d", type[i][j]);
		}
		puts("");
	}
	puts("i know the type.");
	*/
}

float dist_func() {
	int i, j, k, l;
	/* find connecting points */
	int grid[2][2];

	for (i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			grid[i][j] = 0;

	float gridnum = pow(3, order-1);
	
	float tmpf = 0.0;

	
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 2; j++) {
			tmpf = 0.0;
			tmpf = input[i][j] * pow(3, order-1);

			if((tmpf - (int)tmpf) > 0.0) {
				grid[i][j] = (int)tmpf;
			}
			else {
				if((int)tmpf) grid[i][j] = (int)tmpf-1;
				else grid[i][j] = 0;
			}
		}
	}

	/*
	for (i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			printf("%d\n", grid[i][j]);
	printf("i know the grid's type.\n");
	*/

	/* connecting point */
	int c[2][2];
	int checkp[2];
	float mindis[2];
	float len = 1 / partition[order];


	for(i = 0; i < 2; i++) {
		tmpf = input[i][0] * partition[order];
		checkp[0] = (int)tmpf;
		tmpf = input[i][1] * partition[order];
		checkp[1] = (int)tmpf;

		mindis[i] = 1.0*partition[order];

		for(j = 0; j < 2; j++) {
			for(k = 0; k < 2; k++) {
				tmpf = sqrt(pow((input[i][0]*partition[order]-(checkp[0]+j)),2) + 
					pow((input[i][1]*partition[order]-(checkp[1]+k)),2));
				if(tmpf < mindis[i]) {
					mindis[i] = tmpf/partition[order];
					c[i][0] = (checkp[0]+j);
					c[i][1] = (checkp[1]+k);
				}
			}
		}
	}

	/*
 	for(i = 0; i < 2; i++) {
 		printf("mindis = %.3f\n", mindis[i]);
 		for(j = 0; j < 2; j++) {
 			printf("%.3f ", (float)c[i][j]/partition[order]);
 		}
 		puts("");
 	}
 	printf("i know the connecting point.\n");
 	*/

 	/* calculate complete s/z */
 	int mid = (abs(grid[0][1] - grid[1][1]) -1) * pow(3, order-1);
 	int lowpart, highpart;
 	if(type[grid[0][0]][grid[0][1]] < 2) {
 		lowpart = partition[order] - grid[0][0] - 1;
 	}
 	else lowpart = grid[0][0];
 	if(type[grid[0][0]][grid[0][1]] < 2) {
 		highpart = partition[order] - grid[0][0] - 1;
 	}
 	else highpart = grid[0][0];

 	/* calculate partial s/z */
 	int partlen = 0;
 	int typet[2];
 	int typet[0] = type[grid[0][0]][grid[0][1]];
 	int typet[1] = type[grid[1][0]][grid[1][1]];
 	if(grid[0][0] == grid[1][0] && grid[0][1] == grid[1][1]) {
 		/* in the same grid */
 		if(typet[0] == 0) {
 			/* *z */
 			int dp[2], m;
 			for(m = 0; m < 2; m++) {
 				dp[m] = (c[m][0] % 3)+(c[m][1] % 3)*3;
 				if(dp[m] == 3) dp[m] = 5;
 				else if(dp[m] == 5) dp[m] = 3;
 			}
 			partlen = abs(dp[1] - dp[0]);
 		}
 		else if(typet[0] == 1) {
 			/* *s */
 			int dp[2], m;
 			for(m = 0; m < 2; m++) {
 				dp[m] = (c[m][0] % 3)+(c[m][1] % 3)*3;
 				if(dp[m] == 3) dp[m] = 5;
 				else if(dp[m] == 5) dp[m] = 3;
 				if(dp[m] > 5) dp[m] -= 6;
 				else if(dp[m] < 3) dp[m] += 6;
 			}
 			partlen = abs(dp[1] - dp[0]);
 		}
 		else if(typet[0] == 2) {
 			/* s* */
 			int dp[2], m;
 			for(m = 0; m < 2; m++) {
 				dp[m] = (c[m][0] % 3)+(c[m][1] % 3)*3;
 				if(dp[m] == 3) dp[m] = 5;
 				else if(dp[m] == 5) dp[m] = 3;
 				if(dp[m] > 5) dp[m] -= 6;
 				else if(dp[m] < 3) dp[m] += 6;
 			}
 			partlen = abs(dp[1] - dp[0]);
 		}
 		else if(typet[0] == 3) {
 			/* z* */
 			int dp[2], m;
 			for(m = 0; m < 2; m++) {
 				dp[m] = (c[m][0] % 3)+(c[m][1] % 3)*3;
 				if(dp[m] == 3) dp[m] = 5;
 				else if(dp[m] == 5) dp[m] = 3;
 			}
 			partlen = abs(dp[1] - dp[0]);
 		}
 	}
 	else {
 		/* in different grid */
 		for(i = 0; i < 2; i++) {
 			if(typet[i] == 0) {
 				/* *z */
	 			int dp;
	 			dp = (c[i][0] % 3)+(c[i][1] % 3)*3;
	 			if(dp == 3) dp = 5;
	 			else if(dp == 5) dp = 3;
	 			partlen = abs(dp - 8);
 			}
 			else if(typet[i] == 1) {
 				/* *s */
 				int dp;
 				dp = (c[i][0] % 3)+(c[i][1] % 3)*3;
 				if(dp == 3) dp = 5;
 				else if(dp == 5) dp = 3;
 				if(dp > 5) dp -= 6;
 				else if(dp < 3) dp += 6;
 				partlen = abs(dp - 8);
 			}
 			else if(typet[i] == 2) {
 				/* s* */
 				int dp;
 				dp = (c[i][0] % 3)+(c[i][1] % 3)*3;
 				if(dp == 3) dp = 5;
 				else if(dp == 5) dp = 3;
 				if(dp > 5) dp -= 6;
 				else if(dp < 3) dp += 6;
 				partlen = abs(dp - 0);
 			}
 			else if(typet[i] == 3) {
 				/* z* */
	 			int dp;
	 			dp = (c[i][0] % 3)+(c[i][1] % 3)*3;
	 			if(dp == 3) dp = 5;
	 			else if(dp == 5) dp = 3;
	 			partlen = abs(dp - 0);
 			}
 		}
 	}
	return 0;
}