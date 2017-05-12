#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10
char pos[MAXN][MAXN][MAXN];
char view[6][MAXN][MAXN];
int n;

char get_char() {
	char  ch;
	while (1) {
		ch = getchar();
		if ((ch >= 'A' && ch <= 'Z') || ch == '.') break;
	}
	return ch;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		int i, j, k, l;
		
		for(i = 0; i < n; i++) {
			for(k = 0; k < 6; k++) {
				for(j = 0; j < n; j++) {
					view[k][i][j] = get_char();
				}
			}
		}
		
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				for(k = 0; k < n; k++) {
					pos[i][j][k] = '#';
				}
			}
		}
		
		for(k = 0; k < 6; k++) {
			for(i = 0; i < n; i++) {
				for(j = 0; j < n; j++) {
					if(view[k][i][j] == '.') {
						for(l = 0; l < n; l++) {
							int x, y, z;
							
							if (k == 0) x = l, y = j, z = i;
							if (k == 1) x = n - 1 - j, y = l, z = i;
							if (k == 2) x = n - 1 - l, y = n - 1 - j, z = i;
							if (k == 3) x = j, y = n - 1 - l, z = i;
							if (k == 4) x = n - 1 - i, y = j, z = l;
							if (k == 5) x = i, y = j, z = n - 1 - l;

							pos[x][y][z] = '.';
						}
					}
				}
			}
		}

		while (1) {
			bool flag = true;
			for(k = 0; k < 6; k++) {
				for(i = 0; i < n; i++) {
					for(j = 0; j < n; j++) {
						if(view[k][i][j] != '.') {
							for(l = 0; l < n; l++) {
								int x, y, z;

								if (k == 0) x = l, y = j, z = i;
								if (k == 1) x = n - 1 - j, y = l, z = i;
								if (k == 2) x = n - 1 - l, y = n - 1 - j, z = i;
								if (k == 3) x = j, y = n - 1 - l, z = i;
								if (k == 4) x = n - 1 - i, y = j, z = l;
								if (k == 5) x = i, y = j, z = n - 1 - l;
								
								if (pos[x][y][z] == '.') continue;
								if (pos[x][y][z] == '#') {
									pos[x][y][z] = view[k][i][j];
									break;
								}
								if (pos[x][y][z] == view[k][i][j]) break;
								pos[x][y][z] = '.';
								flag = false;
							}
						}
					}
				}
			}
			if (flag) break;
		}

		int ret = 0;
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				for(k = 0; k < n; k++) {
					if (pos[i][j][k] != '.') ret ++;
				}
			}
		}
		
		printf("Maximum weight: %d gram(s)\n", ret);
	}
	return 0;
}