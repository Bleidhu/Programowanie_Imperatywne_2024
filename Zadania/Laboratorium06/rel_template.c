#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

int is_connected(pair *tab, int n);
int get_domain(pair *tab, int n, int *domain);

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) { 
	for(int i = 0; i < n; ++i)
	{
		if(tab[i].first == new_pair.first && tab[i].second == new_pair.second)
		{
			return n;
		}
	}
	tab[n] = new_pair;

	return n+1;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) { 
	int n;
	scanf("%d", &n);
	int current_element = 0;
	for(int i = 0; i < n;++i)
	{
		pair new_pair;

		scanf("%d %d", &new_pair.first, &new_pair.second);

		current_element = add_relation(relation, current_element, new_pair);
	}
	return current_element;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//------------------------------------------------

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair *tab, int n) { 
	/* int element_ordered[MAX_RANGE] = {0};
	int el_count = 0;
	int reflexed = 0;

	for(int i = 0; i < n; ++i)
	{
		if(element_ordered[tab[i].first] == 0)
		{
			element_ordered[tab[i].first] = 1;

			el_count += 1;
			
		}
		if(element_ordered[tab[i].second] == 0)
		{
			element_ordered[tab[i].second] = 1;
			el_count += 1;
		}

		if(tab[i].first == tab[i].second && element_ordered[tab[i].first] == 1)
		{
			element_ordered[tab[i].first] = 2;
			reflexed += 1;
		}
	}

	return(el_count == reflexed); */

	for(int i = 0; i < n; ++i)
	{
		int check = 0;
		for(int j = 0; j < n; ++j)
		{
			if(tab[j].second == tab[i].first)
			{
				check = 1;
				break;
			}
		}
		if(!check)
		{
			return 0;
		}
	}
	return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair *tab, int n) { 
	/* int element_ordered[MAX_RANGE] = {0};
	int el_count = 0;
	int reflexed = 0;

	for(int i = 0; i < n; ++i)
	{
		if(element_ordered[tab[i].first] == 0)
		{
			element_ordered[tab[i].first] = 1;

			el_count += 1;
			
		}
		if(element_ordered[tab[i].second] == 0)
		{
			element_ordered[tab[i].second] = 1;
			el_count += 1;
		}

		if(tab[i].first == tab[i].second && element_ordered[tab[i].first] == 1)
		{
			element_ordered[tab[i].first] = 2;
			reflexed += 1;
		}
	}

	return(reflexed == 0); */

	return 1-is_reflexive(tab, n);
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair *tab, int n) { 
	/*  int relation_exists[MAX_RANGE][MAX_RANGE] = {0};
	 int counter = 0;
	 int singular = 0;
	 for(int i = 0; i < n; ++i)
	 {
		if(tab[i].second == tab[i].first)
		{
			singular += 1;
		}
		if(tab[i].second != tab[i].first && relation_exists[tab[i].second][tab[i].first]==1 && relation_exists[tab[i].first][tab[i].second]==0)
		{
			relation_exists[tab[i].first][tab[i].second] = 1;
			counter += 1;
		}
		relation_exists[tab[i].first][tab[i].second] = 1;
	 }


	 return((n-singular)/2 == counter); */

	 for(int i = 0; i < n; ++i)
	 {
		int check = 0;
		for(int j = 0; j < n; ++j)
		{
			if(tab[j].first == tab[i].second && tab[j].second == tab[i].first)
			{
				check = 1;
				break;
			}

		}


		if(!check)
		{
			return 0;
		}
	 }

	 return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair *tab, int n) { 
/* 	int relation_exists[MAX_RANGE][MAX_RANGE] = {0};
	 for(int i = 0; i < n; ++i)
	 {
		if(tab[i].second != tab[i].first && relation_exists[tab[i].second][tab[i].first]==1)
		{
			relation_exists[tab[i].first][tab[i].second] = 1;
			return 0;
		}
		relation_exists[tab[i].first][tab[i].second] = 1;
	 }


	 return(1); */
	for(int i = 0; i < n; ++i)
	{
		int check = 1;
		for(int j = 0; j < n; ++j)
		{
			if(tab[j].first == tab[i].second && tab[j].second == tab[i].first)
			{

				if(tab[j].first == tab[j].second)
				{
					check = 1;
				} else 
				{
					check = 0;
				}
				break;
			}
		}
		if(!check) return 0;
	}
	return 1;

}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair *tab, int n) { 
	/* int relation_exists[MAX_RANGE][MAX_RANGE] = {0};
	 for(int i = 0; i < n; ++i)
	 {
		if(relation_exists[tab[i].second][tab[i].first]==1)
		{
			relation_exists[tab[i].first][tab[i].second] = 1;
			return 0;
		}
		relation_exists[tab[i].first][tab[i].second] = 1;
	 }

	for(int i = 0; i < n; ++i)
	 {
		if(relation_exists[tab[i].second][tab[i].first]==1)
		{
			relation_exists[tab[i].first][tab[i].second] = 1;
			return 0;
		}
	 }


	 return(1); */

		return is_antisymmetric(tab, n)*is_irreflexive(tab, n);
	 }

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair *tab, int n) { 
	 int exists;
	 for(int i = 0; i < n; ++i)
	 {
		for(int j = 0; j < n; ++j)
		{
			exists = 1;
			if(tab[i].second == tab[j].first)
			{
				exists = 0;
				for(int z = 0; z < n; ++z)
				{
					if(tab[z].first == tab[i].first && tab[j].second == tab[z].second)
					{
						exists = 1;
						break;
					}
				}
				break;
			}

		}
			if(!exists)
			{
				return 0;
			}

	 }


	 return(1);
}

//------------------------------------------------

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair *tab, int n) { 
	int reflexive = is_reflexive(tab, n);
	int antysymetric = is_antisymmetric(tab, n);
	int transistive = is_transitive(tab, n);


	return reflexive*antysymetric*transistive;

}

// A total order relation is a partial order relation that is connected
int is_total_order(pair *tab, int n) { 
	int reflexive = is_reflexive(tab, n);
	int antysymetric = is_antisymmetric(tab, n);
	int transistive = is_transitive(tab, n);


	return reflexive*antysymetric*transistive*is_connected(tab, n);
}

int find_max_elements(pair *tab, int n, int *max_elements) { // tab - partial order
	int domain[MAX_RANGE];

	int n_domain = get_domain(tab, n, domain);

	int counter = 0;
	for(int i = 0; i < n_domain; ++i)
	{
		int count_lower = 0;

		for(int j = 0; j < n; ++j)
		{
			if(tab[j].first == domain[i] && tab[j].first != tab[j].second)
			{
				count_lower = 1;
				break;
			}
		}

		if(!count_lower)
		{
			max_elements[counter] = domain[i];
			++counter;			
		}
	}

	return counter;
}

int find_min_elements(pair *tab, int n, int *min_elements) { // tab - strong partial order
	int domain[MAX_RANGE];

	int n_domain = get_domain(tab, n, domain);

	int counter = 0;
	for(int i = 0; i < n_domain; ++i)
	{
		int count_greater = 0;

		for(int j = 0; j < n; ++j)
		{
			if(tab[j].second == domain[i] && tab[j].first != tab[j].second)
			{
				count_greater = 1;
				break;
			}
		}

		if(!count_greater)
		{
			min_elements[counter] = domain[i];
			++counter;			
		}
	}

	return counter;
}

int get_domain(pair *tab, int n, int *domain) { 
		int elements[MAX_RANGE] = {0};

	for(int i = 0; i < n; ++i)
	{
		elements[tab[i].first] = 1;
		elements[tab[i].second] = 1;
	}

	int counter = 0;
	for(int i = 0; i < MAX_RANGE; ++i)
	{
		if(elements[i] != 0)
		{
			domain[counter] = i;
			counter += 1;

		}
	}

	return counter;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair *tab, int n) { 
	int elements[MAX_RANGE] = {0};
	int tmp_domain[n];
	int n_domain = get_domain(tab, n, tmp_domain);

	/* for(int i = 0; i < n; ++i)
	{
		elements[tab[i].first] = 1;
		elements[tab[i].second] = 1;
	}

	for(int i = 0; i < MAX_RANGE; ++i)
	{
		if(elements[i] != 0)
		{
			int exists = 0;
			for(int j = 0; j < MAX_RANGE; ++j)
			{
				if(i == j || elements[j] == 1)
				{
					continue;
				}

				for(int z = 0; z < n; ++z)
				{
					if((tab[z].first == i && tab[z].second == j) ||(tab[z].first == j && tab[z].second == i))
					{
						exists = 1;
					}
				}

				if(!exists)
					return 0;
			}
		}
	}

	return 1; */

	for(int i = 0; i < n_domain; ++i)
	{
			int exists = 0;
			for(int j = 0; j < n_domain; ++j)
			{	
				exists = 0;
				for(int z = 0; z < n; ++z)
				{
					if((tab[z].first == tmp_domain[i] && tab[z].second == tmp_domain[j]) ||(tab[z].first == tmp_domain[j] && tab[z].second == tmp_domain[i]))
					{
						exists = 1;
						break;
					}
				}

				if(!exists)
					return 0;
			}
		}

	return 1;


}

//------------------------------------------------

// Case 3:

// x(S o R)z iff exists y: xRy and ySz
int composition (pair *rel_1, int n1, pair *rel_2, int n2, pair *rel_3) { 
	int counter = 0;

	for(int i = 0; i < n1; ++i)
	{
		for(int j = 0; j < n2; ++j)
		{
			if(rel_1[i].second == rel_2[j].first)
			{
				pair new_pair;
				new_pair.first=rel_1[i].first;
				new_pair.second=rel_2[j].second;
				counter = add_relation(rel_3, counter, new_pair);
				
			}
		}
	}

	return counter;

}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	
	return 0;
}

