#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

int stack[STACK_SIZE];
int top = 0;

int stack_push(int x) {
	if(top == STACK_SIZE)
	{
		return OVERFLOW;
	} else
	{
		top += 1;
		stack[top - 1] = x;
		return OK;
	}
}

int stack_pop(void) {
	if(top == 0)
	{
		return UNDERFLOW;
	} else
	{
		top -= 1;
		return(stack[top - 1 + 1]);
	}
}

int stack_state(void) {
	return top;
}

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

void queue_print(void) {
	for(int i = 0; i < in; ++i)
	{
		printf("%d ", queue[i]);
	}
}

int queue_push(int in_nr) { // in_nr clients try to enter the queue
	int left_space = QUEUE_SIZE - in;
	int operations = in_nr;
	if(in_nr > left_space)
	{
		operations = left_space;
	}

	for(int i = 0; i < left_space; ++i)
	{
		queue[in + i] = curr_nr + i + 1;
	}

	curr_nr += in_nr;
	in = in + operations;

	if(in_nr > left_space)
	{
		return OVERFLOW;
	} else
	{
		return OK;
	}

}

int queue_pop(int out_nr) { // out_nr clients leaves the queue
	int items_to_remove = out_nr;
	if(out_nr > in){
		items_to_remove = in;
	}

	in -= items_to_remove;

	for(int i = 0; i < items_to_remove; ++i)
	{
		for(int j = 0; j < QUEUE_SIZE - 1; ++j)
		{
			queue[j] = queue[j + 1];
		}
	}

	if(out_nr > items_to_remove)
	{
		return UNDERFLOW;
	} else{
		return in;
	}
}

int queue_state(void) {
	return in;
}



// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out = 0, len = 0;


int cbuff_push(int cli_nr) { // client with number cli_nr enters the queue
	if(len == CBUFF_SIZE)
	{
		return OVERFLOW;
	} else
	{
		cbuff[(out + len)%CBUFF_SIZE] = cli_nr;
		len += 1;
		return OK;
	}
}

int cbuff_pop(void) { // longest waiting client leaves the queue
	if(len == 0)
	{
		return UNDERFLOW;
	} else{
		len -= 1;
		int elem = cbuff[out];
		out = (out + 1)%CBUFF_SIZE;
		return elem;
	}
}

int cbuff_state(void) {
	return len;
}

void cbuff_print(void) {
	for(int i = 0; i < len; ++i)
	{
		printf("%d ", cbuff[(out + i)%CBUFF_SIZE]);
	}
}

int main(void) {
	int to_do, n, client_no, answer;
	scanf("%d", &to_do);
	switch(to_do) {
		case 1: // stack
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = stack_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", stack_pop());
				} else printf("\n%d\n", stack_state());
			} while(n != 0);
			break;
		case 2: // FIFO queue with shifts
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = queue_push(n)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					if ((answer = queue_pop(-n)) < 0) printf("%d ", answer);
				} else {
					printf("\n%d\n", queue_state());
					queue_print();
				}
			} while(n != 0);
			break;
		case 3: // queue with cyclic buffer
			client_no = 0;
			do {
				scanf("%d", &n);
				if (n > 0) {
					if ((answer = cbuff_push(++client_no)) < 0) printf("%d ", answer);
				} else if (n < 0) {
					printf("%d ", cbuff_pop());
				} else {
					printf("\n%d\n", cbuff_state());
					cbuff_print();
				}
			} while(n != 0);
			break;
		default: 
			printf("NOTHING TO DO!\n");
	}
	return 0;
}
