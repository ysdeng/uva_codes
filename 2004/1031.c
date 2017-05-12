#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main () {
	char cypher[40];
	int rest0[26];
	char used0[40];
	char picked[40];
	char pass[40];
	int i;
	int testcase = 1;
	while(1) {
		/*- init -*/
		bzero(rest0, sizeof(rest0));
		bzero(used0, sizeof(used0));

		/*- input -*/
		scanf("%s", cypher);
		if(strcmp(cypher,"X") == 0) break;

		int m = strlen(cypher);

		for(i = 0; i < m; i++)
			rest0[cypher[i]-'A']++;

		for(i = 0; i < 26; i++)
			if(rest0[i]) {
				rest0[i] /= 2;
			}

		int usedQ0[40], cur0;
		for(i = 0; i < 40; i++) {
			usedQ0[i] = i;
		}
		cur0 = m;

		int success = 0;

		/*- simulate all possible solution -*/
		bool flag = false;
		int RoundCount = 1;
		int n, s, t, j;
		for(n = m/2; n > 0; n--) {
			if(success) break;

			for(s = 0; s < m; s++) {
				if(success > 1) break;
				for(i = 0; i < m; i++) {
					if(success > 1) break;
					int used1[40], rest1[26], usedQ1[40];
					int cur1 = cur0;
					int tmpcur;
					/*
					for(tmpcur = 0; tmpcur < 40; tmpcur++) used1[tmpcur] = used0[tmpcur];
					*/
					for(tmpcur = 0; tmpcur < cur0; tmpcur++) usedQ1[tmpcur] = usedQ0[tmpcur];
					for(tmpcur = 0; tmpcur < 26; tmpcur++) rest1[tmpcur] = rest0[tmpcur];

					/*- 填第一次 -*/
					int ll, counti;
					int starts, nowcur1;

					/*- find s -*/
					for(ll = 0; ll < cur1; ll++) {
						if(usedQ1[ll] == s) {
							nowcur1 = ll;
							starts = s;
							break;
						}
					}
					for(ll = nowcur1; ll < cur1-1; ll++) {
						usedQ1[ll] = usedQ1[ll+1];
					}
					cur1--;
					/*
					used1[starts] = 1;
					*/
					rest1[cypher[starts]-'A']--;
					picked[0] = cypher[starts];

					if(rest1[cypher[starts]-'A'] < 0) {
						break;
					}
					bool gg = false;
					
					for(ll = 1; ll < n; ll++) {
						counti = i;
						/*- 找到下i個空白 -*/
						nowcur1 = (nowcur1+i)%cur1;
						starts = usedQ1[nowcur1];
						int lll;
						for(lll = nowcur1; lll < cur1-1; lll++) {
							usedQ1[lll] = usedQ1[lll+1];
						}
						cur1--;
						/*
						while(1) {
							if(used1[starts] == 0) {
								if(counti != 0) counti--;
								else break;
							}
							starts = (starts+1) % m;
						}
						used1[starts] = 1;
						*/
						rest1[cypher[starts]-'A']--;
						picked[ll] = cypher[starts];
						if(rest1[cypher[starts]-'A'] < 0) {
							gg = true;
							break;
						}
					}
					if(gg) continue;

					for(t = 0; t < m; t++) {
						if(success > 1) break;
						for(j = i+1; j <= m; j++) {
							if(j == m) break;
							if(cypher[t] != picked[0]) break;

							int usedQ2[40], cur2 = cur1;
							int nowcur2;
							int idx, ok = 0;
							for(idx = 0; idx < cur1; idx++)
								if(usedQ1[idx] == t) {
									ok  = 1; nowcur2 = idx; break;
								}
							if(ok == 0) break;
							
							int tmpcur;
							for(tmpcur = 0; tmpcur < cur1; tmpcur++) usedQ2[tmpcur] = usedQ1[tmpcur];
							
							int jj, countj;
							int startt = usedQ2[nowcur2];

							for(idx = nowcur2; idx < cur2-1; idx++) {
								usedQ2[idx] = usedQ2[idx+1];
							}
							cur2--;

							bool ggt = false;
							
							for(jj = 1; jj < n; jj++) {

								countj = j;
								/*- 找到下j個空白 -*/
								nowcur2 = (nowcur2+j)%cur2;
								startt = usedQ2[nowcur2];
								int lll;
								for(lll = nowcur2; lll < cur2-1; lll++) {
									usedQ2[lll] = usedQ2[lll+1];
								}
								cur2--;
								/*
								while(1) {
									if(used2[startt] == 0) {
										if(countj != 0) countj--;
										else break;
									}
									startt = (startt+1) % m;
								}
								*/
								if(cypher[startt] != picked[jj]) {
									ggt = true;
									break;
								}
								/*
								used2[startt] = 1;
								*/
							}

							if(!ggt) {
								int lll;
								if(success == 0){
									for(lll = 0; lll < n; lll++) {
										pass[lll] = picked[lll];
									}
									pass[lll] = '\0';
									success++;
								}
								else {
									int notsame = 0;
									for(lll = 0; lll < n; lll++) {
										if(pass[lll] != picked[lll]) {
											notsame = 1;
											break;
										}
									}
									if(notsame)
										success++;
								}
								
								if(success > 1) break;
							}
							if(ggt) continue;
						}
					}
				}
			}
		}

		printf("Code %d: ", testcase++);
		if(success == 1) {
			printf("%s\n", pass);
		}
		if(success > 1) {
			puts("Codeword not unique");
		}
	}
	return 0;
}