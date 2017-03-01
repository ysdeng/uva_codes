/*
	This is a small program that i practice big number division.
*/

#include <stdio.h>
#include <string.h>

char num_ch[100];
int num_bit[100];

void StringToBitArray();
int CharToInt(char c);

int main () {
	//num_ch = "7427958190";
	scanf("%s", num_ch);
	StringToBitArray();
	return 0;
}

int CharToInt(char c) {
	return c-'0';
}
void StringToBitArray() {
	int origin_num[100];

	int i, j, k, l;

	// initialize
	for(i = 0; i < 100; i++)
		origin_num[i] = 0;

	int len = (int)strlen(num_ch);

	for(i = 100-len, j = 0; i < 100; i++, j++) {
		origin_num[i] = CharToInt(num_ch[j]);
	}

	//print out the result
	for(i = 0; i < 100; i++) {
		if(i%10 == 0) puts("");
		printf("%d", origin_num[i]);
	}
	puts("");
}