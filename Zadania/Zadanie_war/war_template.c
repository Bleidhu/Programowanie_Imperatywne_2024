#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_COLORS 4

int random_from_interval(int a, int b) {
	return (rand()%(b - a + 1) + a);
}

void swap (int array[], int i, int k) {
	int tmp = array[i];
	array[i] = array[k];
	array[k] = tmp;
}
void shuffle(int t[], int size) {
	for(int i = 0; i < size; ++i)
	{
		t[i] = i;
	}
	for(int i = 0; i < n-1; ++i)
	{
		int k = rand_from_interval(i, size);
		swap(t, i, k);
	}
}
#define CBUFF_SIZE 10



int cbuff_push(int tab[], int cli_nr, char player) { // client with number cli_nr enters the queue
	if(len == CBUFF_SIZE)
	{
		return OVERFLOW;
	} else
	{
		tab[(out + len)%CBUFF_SIZE] = cli_nr;
		len += 1;
		return OK;
	}
}

int cbuff_pop(int tab[], char player) { // longest waiting client leaves the queue
	if(len == 0)
	{
		return UNDERFLOW;
	} else{
		len -= 1;
		int elem = tab[out];
		out = (out + 1)%CBUFF_SIZE;
		return elem;
	}
}

int cbuff_state(void) {
	return len;
}

void cbuff_print(int tab[], char player) {
	for(int i = 0; i < len; ++i)
	{
		printf("%d ", tab[(out + i)%CBUFF_SIZE]);
	}
}

void game(int n, int player_A[], int player_B[], int max_conflicts, int simplified_mode) {

}
void first_takes_cards(int number_of_cards_on_table, int player_1[], int *pout_1, int *p_cards_1,
		const int player_2[], int *pout_2, int *p_cards_2, int size) {

}
void both_take_cards(int player_1[], int *pout_1, const int *p_cards_1,
		int player_2[], int *pout_2, const int *p_cards_2, int size) {
}

int main(void) {
	int player_A[NUMBER_OF_CARDS], player_B[NUMBER_OF_CARDS];
	int deck[NUMBER_OF_CARDS];
	int max_conflicts;
	int simplified_mode;
	int seed;
	scanf("%d", &seed);
	scanf("%d", &simplified_mode);
	scanf("%d", &max_conflicts);

	for(int i = 0; i < NUMBER_OF_CARDS; i++) deck[i] = i;
	srand((unsigned) seed);
	shuffle(deck, NUMBER_OF_CARDS);
	for(int i = 0; i < NUMBER_OF_CARDS / 2; i++) {
		player_A[i] = deck[i];
		player_B[i] = deck[i + NUMBER_OF_CARDS / 2];
	}
	game(NUMBER_OF_CARDS, player_A, player_B, max_conflicts, simplified_mode);
	return 0;
}

