/*
	This is a small program that i practice 
	simple division and multiplication.
*/

#include <stdio.h>
#include <string.h>

char num_ch[100];
int num_bit[100];

void StringToBitArray();
int CharToInt(char c);
void BitArrayToString();

int main () {
	//num_ch = "7427958190";
	scanf("%s", num_ch);
	StringToBitArray();
	BitArrayToString();
	return 0;
}

int CharToInt(char c) {
	return c-'0';
}

void StringToBitArray() {
	int origin_num[100];
	int reversed_bits[100];
	int i, j, k, l;

	// initialize
	for(i = 0; i < 100; i++)
		origin_num[i] = reversed_bits[i] = 0;

	int len = (int)strlen(num_ch);

	for(i = 100-len, j = 0; i < 100; i++, j++) {
		origin_num[i] = CharToInt(num_ch[j]);
	}

	/*
		start StringToBitArray
	*/

	int finish = 4*len;
	if(finish>100) finish = 100;
	int count = 0;
	while(finish --) {
		int quotient = 0, rest = 0;

		for(i = 0; i < 100; i++) {
			
			origin_num[i] += rest * 10;

			quotient = origin_num[i] / 2;
			rest = origin_num[i] % 2;

			origin_num[i] = quotient;
		}
		reversed_bits[count++] = rest;
		/*
		printf("round %d: rest = %d, ", count, reversed_bits[count-1]);
		for(i = 0; i < 100; i++) {
			printf("%d", origin_num[i]);
		}
		puts("");
		*/
	}

	for(i = 99, j = 0; j < 100; i--, j++)
		num_bit[j] = reversed_bits[i];
	
	printf("convert to bit string:");
	for(i = 0; i < 100; i++) {
		if(i%10 == 0) puts("");
		printf("%d", num_bit[i]);
	}
	puts("");

}
void BitArrayToString() {
	int final_num[100];

	int i, j, k;
	//initialize
	for(i = 0; i < 100; i++)
		final_num[i] = 0;
	
	for(i = 0; i < 100; i++) {
		final_num[99] += num_bit[i];
		if(i == 99) break;
		for(j = 99; j >= 0; j--) {
			final_num[j] *= 2;
		}
		for(j = 99; j >= 0; j--) {
			if(final_num[j] > 9) {
				final_num[j-1] += final_num[j] /10;
				final_num[j] = final_num[j] % 10;
			}
		}
	}

	printf("from bit string to decimal string:");
	for(i = 90; i < 100; i++) {
		if(i%10 == 0) puts("");
		printf("%d", final_num[i]);
	}
	puts("impossible");
}
