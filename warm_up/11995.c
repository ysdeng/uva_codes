/**
i need to implement a queue, stack, priority queue.
and then base on the testcase to figure out what structure
it belongs to.
*/
#include <stdio.h>
#include <stdbool.h>

void insert(int in);
void pop(int out);

int queue[1100]; // do as a ring
	int head, tail;
int pqueue[1100];
	int qtail; // just pop out the largest num
int stack[1100];
	int stail;

bool isQueue, isPqueue, isStack;

int main() {
	int cmd_count;
	while(scanf("%d", &cmd_count) != EOF) {
		//initialize
		int i;
		for (i = 0; i < 1200; i++) {
			queue[i] = 0;
			pqueue[i] = 0;
			stack[i] = 0;
		}
		isStack = true;
		isPqueue = true;
		isQueue = true;
		head = tail = stail = qtail = -1;
		
		// check point
		//printf("HAHA %d\n", cmd_count);

		//start main operations
		while(cmd_count--) {
			int cmd, input;
			scanf("%d%d", &cmd, &input);
			
			// check point
			//printf("cmd: %d %d\n", cmd, input);
			
			if(cmd == 1) insert(input);
			else pop(input);
		}
		//which structure
		//print result
		if(isQueue == true && isPqueue == false && isStack == false)
			puts("queue");
		else if(isPqueue == true && isQueue == false && isStack == false)
			puts("priority queue");
		else if(isStack == true && isPqueue == false && isQueue == false)
			puts("stack");
		else if(isQueue == false && isPqueue == false && isStack == false)
			puts("impossible");
		else puts("not sure");
		//puts("");

	}
	return 0;
}

void insert(int in) {
	// queue
	tail++;
	queue[tail] = in;

	// stack
	stail++;
	stack[stail] = in;
	
	// pqueue
	int i;
	if(qtail == -1) {
		qtail++;
		pqueue[qtail] = in;
	}
	else {
		bool shift = false;
		for(i = 0; i <= qtail; i++)
			if(pqueue[i] > in) {
				shift = true;
				int j;
				for(j = qtail; j >= i; j--) {
					pqueue[j+1] = pqueue[j];
				}
				pqueue[i] = in;
				qtail++;
				break;
			}
		if(!shift) {
			qtail++;
			pqueue[qtail] = in;
		}
	}

	// check point
	/*
	int k;
	printf("queue: ");
	for (k = head+1; k <= tail; k++)
		printf("%d ", queue[k]);
	puts("");
	printf("pqueue: ");
	for (k = 0; k <= qtail; k++)
		printf("%d ", pqueue[k]);
	puts("");
	printf("stack: ");
	for (k = 0; k <= stail; k++)
		printf("%d ", stack[k]);
	puts("");
	*/
}

void pop(int out) {

	head++;
	int queue_o = queue[head];

	int pqueue_o = pqueue[qtail];
	qtail--;

	int stack_o = stack[stail];
	stail--;

	if(isQueue)
		if(queue_o != out) isQueue = false;

	if(isPqueue)
		if(pqueue_o != out) isPqueue = false;

	if(isStack)
		if(stack_o != out) isStack = false;

	// check point
	/*
	printf("queue_o: %d\t", queue_o);
	printf("pqueue_o: %d\t", pqueue_o);
	printf("stack_o: %d\n", stack_o);

	printf("queue_o: %d\t", isQueue);
	printf("pqueue_o: %d\t", isPqueue);
	printf("stack_o: %d\n", isStack);
	*/
}