/*
	this is a simulation problem
	there are 100 light bulbs and 100 switches
	each switch can control 2 or 3 light bulbs
	input: light bulbs' origin and final state
	output: could light bulbs be converted to the final state
			if success, print out the swithes' state

	In this problem, using following skill:
		big number multiplication and division
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char origin_char[100], final_char[100];
int origin_bit[100], final_bit[100];
int switch_state[100];
int swithes_decimal[100];

void StringToBitArray(int p);
void BitArrayToString();

int simulator();

void init() {
	int i;
	for(i = 0; i < 100; i++) {
		origin_bit[i] = final_bit[i] = 0;
		switch_state[i] = 0;
	}
}

int main() {
	int caseNum = 0;
	while(1) {
		init();
		

		scanf("%s%s", origin_char, final_char);
		if(origin_char[0] == '0' && final_char[0] == '0')
			break;
		if(caseNum) puts("");
		StringToBitArray(0);
		StringToBitArray(1);

		int success = simulator();

		BitArrayToString();
		
		printf("Case Number %d: ",++caseNum);
		if(success) {
			int i;
			int start = 0;
			for(i = 0; i < 100; i++) {
				if(swithes_decimal[i] != 0) start = 1;
				if(start) printf("%d", swithes_decimal[i]);
			}
			if(!start) printf("0");
			puts("");
		}
		else
			puts("impossible");
	}
	return 0;
}

int simulator() {
	int i, j;
	int success = 1;

	for(j = 1; j >= 0; j--) {
		for(i = j; i < 100; i++) {
			if(i == 0) {
				if(origin_bit[0] != final_bit[0]) {
					switch_state[0] = 1;
					origin_bit[0] = abs(origin_bit[0]-1);
					origin_bit[1] = abs(origin_bit[1]-1);
				}
			}
			else if(i == 99) {
				if(origin_bit[98] != final_bit[98]) {
					switch_state[99] = 1;
					origin_bit[98] = abs(origin_bit[98]-1);
					origin_bit[99] = abs(origin_bit[99]-1);
				}
			}
			else {
				if(origin_bit[i-1] != final_bit[i-1]) {
					switch_state[i] = 1;
					origin_bit[i-1] = abs(origin_bit[i-1]-1);
					origin_bit[i] = abs(origin_bit[i]-1);
					origin_bit[i+1] = abs(origin_bit[i+1]-1);
				}
			}
		}
		success = 1;
		for(i = 0; i < 100; i++) {
			if(origin_bit[i] != final_bit[i])
				success = 0;
		}
		if(success) break;
	}

	return success;
}

void StringToBitArray(int p) {
	int origin_num[100];
	int reversed_bits[100];
	int i, j, k, l;

	/* initialize */
	for(i = 0; i < 100; i++)
		origin_num[i] = reversed_bits[i] = 0;

	int len;
	if(p == 0) len = (int)strlen(origin_char);
	else len = (int)strlen(final_char);
	for(i = 100-len, j = 0; i < 100; i++, j++) {
		if(p == 0) origin_num[i] = origin_char[j] - '0';
		else origin_num[i] = final_char[j] - '0';
	}

	/* start StringToBitArray */

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
	}

	for(i = 99, j = 0; j < 100; i--, j++) {
		if(p == 0) origin_bit[i] = reversed_bits[j];
		else final_bit[i] = reversed_bits[j];
	}
}

void BitArrayToString() {

	int i, j, k;
	/* initialize */
	for(i = 0; i < 100; i++)
		swithes_decimal[i] = 0;
	
	for(i = 0; i < 100; i++) {
		swithes_decimal[99] += switch_state[i];
		if(i == 99) break;
		for(j = 99; j >= 0; j--) {
			swithes_decimal[j] *= 2;
		}
		for(j = 99; j >= 0; j--) {
			if(swithes_decimal[j] > 9) {
				swithes_decimal[j-1] += swithes_decimal[j] /10;
				swithes_decimal[j] = swithes_decimal[j] % 10;
			}
		}
	}

}