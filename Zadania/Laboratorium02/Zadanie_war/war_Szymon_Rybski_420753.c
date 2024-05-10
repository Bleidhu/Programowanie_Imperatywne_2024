#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_CARDS 52
#define NUMBER_OF_COLORS 4

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

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
	for(int i = 0; i < size-1; ++i)
	{
		int k = random_from_interval(i, size - 1);
		swap(t, i, k);
	}
}


int cbuff_push(int tab[], int card_nr, int n, int *len, int *out) {
	if(*len == n)
	{
		return OVERFLOW;
	} else
	{
		tab[(*out + *len)%n] = card_nr;
		*len += 1;
		return OK;
	}
}

int cbuff_pop(int tab[], int *len, int *out, int n) {
	if(len == 0)
	{
		return UNDERFLOW;
	} else{
		*len -= 1;
		int elem = tab[*out];
		*out = (*out + 1)%n;
		return elem;
	}
}

int cbuff_state(int len) {
	return len;
}

void cbuff_print(int tab[], int *len, int *out, int n) {
	for(int i = 0; i < *len; ++i)
	{
		printf("%d ", tab[(*out + i)%n]);
	}
}
void first_takes_cards(int number_of_cards_on_table, int player_1[], int *pout_1, int *p_cards_1,
		const int player_2[], int *pout_2, int *p_cards_2, int size) {
		for(int i = 0; i < number_of_cards_on_table; ++i)
		{
			int card = cbuff_pop(player_1, p_cards_1, pout_1, size);
			cbuff_push(player_1, card, size, p_cards_1, pout_1);
		}
		for(int i = 0; i < number_of_cards_on_table; ++i)
		{
			int card = cbuff_pop(player_2, p_cards_2,pout_2, size);
			cbuff_push(player_1, card, size, p_cards_1, pout_1);
		}

}
void both_take_cards(int player_1[], int *pout_1, const int *p_cards_1,
		int player_2[], int *pout_2, const int *p_cards_2, int size) {
		cbuff_push(player_1, cbuff_pop(player_1, p_cards_1, pout_1, size), size, p_cards_1, pout_1);
		cbuff_push(player_2, cbuff_pop(player_2, p_cards_2, pout_2, size), size, p_cards_2, pout_2);
}
void game(int n, int player_A[], int player_B[], int max_conflicts, int simplified_mode) {
	int curr_conflicts = 0;
	int a_out = 0, b_out = 0;
	int a_len = n/2, b_len = n/2;
	int war_cards = 1;
	while(curr_conflicts <= max_conflicts && a_len-war_cards >= 0 && b_len-war_cards >= 0)
	{
		int a_card = player_A[(a_out + war_cards - 1 + n)%n];
		int b_card = player_B[(b_out + war_cards - 1 + n)%n];
		

		/* cbuff_print(player_A, &a_len, &a_out, n);
			printf("\n");
		cbuff_print(player_B, &b_len, &b_out, n);
			printf("\n");
		printf("%d %d %d\n", curr_conflicts, a_len, b_len); */
		
		if(a_card/NUMBER_OF_COLORS < b_card/NUMBER_OF_COLORS)
		{
			first_takes_cards(war_cards, player_B, &b_out, &b_len, player_A, &a_out, &a_len, n);
			war_cards = 1;
			curr_conflicts += 1;
		} else if(a_card/NUMBER_OF_COLORS > b_card/NUMBER_OF_COLORS)
		{
			first_takes_cards(war_cards, player_A, &a_out, &a_len, player_B, &b_out, &b_len, n);
			war_cards = 1;
			curr_conflicts += 1;
		} else{
			if(simplified_mode == 1)
			{
				both_take_cards(player_B, &b_out, &b_len, player_A, &a_out, &a_len, n);
			} else{
				war_cards += 2;
			}
			curr_conflicts += 1;

		}
	}

	if(a_len > 0 && b_len > 0 && curr_conflicts>max_conflicts)
	{
		printf("%i %i %i", 0, a_len, b_len);
	} else if((a_len-war_cards < 0 || b_len - war_cards < 0) && war_cards > 1){
		printf("%i %i %i", 1, a_len, b_len);
	} else if(a_len > 0)
	{
		printf("%i  %i", 2, curr_conflicts);
	} else{
		printf("%i \n", 3);
		cbuff_print(player_B, &b_len, &b_out, n);
	}
}


int main(void) {
	int player_A[NUMBER_OF_CARDS], player_B[NUMBER_OF_CARDS];
	int player_A_table[NUMBER_OF_CARDS], player_B_table[NUMBER_OF_CARDS];
	int deck[NUMBER_OF_CARDS];

	int a_out = 0;
	int b_out = 0;

	
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

