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

char origin_char[100], final_char[100];
int origin_bit[100], final_bit[100];
int switch_state[100];

void charTobit();
void bitTochar();

void init() {
	int i;
	for(i = 0; i < 100; i++) {
		origin_char[i] = final_char[i] = '0';
		origin_bit[i] = final_bit[i] = 0;
		switch_state[i] = 0;
	}
}

int main() {
	while(1) {
		init();
		scanf("%s%s", origin_char, final_char);
		/*
		printf("origin: %s, %d bits,final: %s, %d bits.\n",
			origin_char, (int)strlen(origin_char),
			final_char, (int)strlen(final_char));
		*/
		if(origin_char[0] == '0' && final_char[0] == '0')
			break;
		
		//charTobit();

	}
	return 0;
}

void charTobit() {
	/*
		implement big number's division in this function
	*/
	int origin_len, final_len;
	//origin_len = (int)strlen(origin_char);
	//final_len = (int)strlen(final_char);
	
	int len;
	len = (int)strlen(origin_char);
	int intarr[100];

	int i, j, k;

	for(i = 0;i < 100; i++) intarr[i] = 0;
	
	for(i = 100-len, j = 0; i < 100; i++, j++) {
		intarr[i] = origin_char[j] - '0';
	}

}