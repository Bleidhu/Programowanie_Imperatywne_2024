#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int day;
	int month;
	int year;
} Date;

// 1 bsearch2

#define NAME_MAX  20   // max. length of name + 1
#define FOOD_MAX  30   // max. number of goods
#define RECORD_MAX 64  // max. line length

typedef struct {
	char name[NAME_MAX];
	float price;
	int amount;
	Date valid_date;
} Food;

typedef int (*ComparFp)(const void*, const void*);

//0 - wrong order 1-right order 2-same
int cmp_date(const void* d1, const void* d2) {
	Date a = *((Date*)d1);
	Date b = *((Date*)d2);

	if (a.year != b.year)
	{
		return a.year < b.year;
	}
	else if (a.month != b.month)
	{
		return a.month < b.month;
	}
	else if (a.day != b.day)
	{
		return a.day < b.day;
	}
	else
	{
		return 2;
	}

}

int cmp(const void* a, const void* b) {
	Food _a = *((Food*)a);
	Food _b = *((Food*)b);

	return compare_date(&_a.valid_date, &_b.valid_date);

}

void* bsearch2(const void* key, const void* base, const size_t nmemb,
	const size_t size, const ComparFp compar, char* result) {
	int i = 0;

	int last_cmp = 1;
	while (i < size && last_cmp == 1)
	{
		last_cmp = *ComparFp(key)
			i += 1;
	}

}

void print_art(Food* p, const int n, const char* art) {
}

Food* add_record(const Food* tab, int* np, const ComparFp compar, const Food* new) {
}

int read_goods(Food* tab, const int no, FILE* stream, const int sorted) {
}

int cmp_qs(const void* a, const void* b) {
	const Food* fa = (Food*)a, * fb = (Food*)b;
	return cmp_date(&fa->valid_date, &fb->valid_date);
}

int cmp_bs(const void* a, const void* b) {
	const Date* pd = (Date*)a;
	const Food* fb = (Food*)b;
	return cmp_date(pd, &fb->valid_date);
}

float value(Food* food_tab, const size_t n, const Date curr_date, const int days) {
}

/////////////////////////////////////////////////////////////////
// 3 Succession

#define CHILD_MAX 20

enum Sex { F, M };
enum BOOL { no, yes };

struct Bit_data {
	enum Sex sex :1;
	enum BOOL in_line :1;
};

typedef struct {
	char* name;
	struct Bit_data bits;
	Date born;
	char* parent;
} Person;

typedef struct {
	char* par_name;
	int index;
} Parent;

const Date primo_date = { 28, 10, 2011 }; // new succession act

int cmp_primo(const Person* person1, const Person* person2) {
	if (person1->bits.sex == person2->bits.sex) return 0;
	if (person1->bits.sex == F && cmp_date(&person1->born, &primo_date) > 0) return 0;
	if (person2->bits.sex == F && cmp_date(&person2->born, &primo_date) > 0) return 0;
	return person2->bits.sex - person1->bits.sex;
}

int cmp_person(const void* a, const void* b) {
}

int cmp_parent(const void* a, const void* b) {
}

int fill_indices_tab(Parent* idx_tab, const Person* pers_tab, const int size) {
}

void persons_shifts(Person* person_tab, const int size, Parent* idx_tab, const int no_parents) {
}

int cleaning(Person* person_tab, int n) {
}

void print_person(const Person* p) {
	printf("%s\n", p->name);
}

int create_list(Person* person_tab, int n) {
}

int main(void) {
	Person person_tab[] = {
		{"Charles III", {M, no}, {14, 11, 1948},"Elizabeth II"},
		{"Anne", {F,yes}, {15, 8, 1950},"Elizabeth II"},
		{"Andrew", {M,yes}, {19, 2, 1960},"Elizabeth II"},
		{"Edward", {M,yes}, {10, 3, 1964} ,"Elizabeth II"},
		{"David", {M,yes}, {3, 11, 1961} ,"Margaret"},
		{"Sarah", {F,yes}, {1, 5, 1964}, "Margaret"},
		{"William", {M,yes}, {21, 6, 1982}, "Charles III"},
		{"Henry", {M,yes}, {15, 9, 1984}, "Charles III"},
		{"Peter", {M,yes}, {15, 11, 1977}, "Anne"},
		{"Zara", {F,yes}, {15, 5, 1981}, "Anne"},
		{"Beatrice", {F,yes}, {8, 8, 1988}, "Andrew"},
		{"Eugenie", {F,yes}, {23, 3, 1990}, "Andrew"},
		{"James", {M,yes}, {17, 12, 2007}, "Edward"},
		{"Louise", {F,yes}, {8, 11, 2003}, "Edward"},
		{"Charles", {M,yes}, {1, 7, 1999}, "David"},
		{"Margarita", {F,yes}, {14, 5, 2002}, "David"},
		{"Samuel", {M,yes}, {28, 7, 1996}, "Sarah"},
		{"Arthur", {M,yes}, {6, 5, 2019}, "Sarah"},
		{"George", {M,yes}, {22, 7, 2013}, "William"},
		{"George VI", {M,no}, {14, 12, 1895}, NULL},
		{"Charlotte", {F,yes}, {2, 5, 2015}, "William"},
		{"Louis", {M,yes}, {23, 4, 2018}, "William"},
		{"Archie", {M,yes}, {6, 5, 2019}, "Henry"},
		{"Lilibet", {F,yes}, {4, 6, 2021}, "Henry"},
		{"Savannah", {F,yes}, {29, 12, 2010}, "Peter"},
		{"Isla", {F,yes}, {29, 3, 2012}, "Peter"},
		{"Mia", {F,yes}, {17, 1, 2014}, "Zara"},
		{"Lena", {F,yes}, {18, 6, 2018}, "Zara"},
		{"Elizabeth II", {F,no}, {21, 4, 1926}, "George VI"},
		{"Margaret", {F,no}, {21, 8, 1930}, "George VI"},
		{"Lucas", {M,yes}, {21, 3, 2021}, "Zara"},
		{"Sienna", {F,yes}, {18, 9, 2021}, "Beatrice"},
		{"August", {M,yes}, {9, 2, 2021}, "Eugenie"},
		{"Ernest", {M,yes}, {30, 5, 2023}, "Eugenie"}
	};

	int to_do, no;
	int n;
	Food food_tab[FOOD_MAX];
	char buff[RECORD_MAX];
	fgets(buff, RECORD_MAX, stdin);
	sscanf(buff, "%d", &to_do);

	switch (to_do) {
	case 1:  // bsearch2
		fgets(buff, RECORD_MAX, stdin);
		sscanf(buff, "%d", &no);
		n = read_goods(food_tab, no, stdin, 1);
		scanf("%s", buff);
		print_art(food_tab, n, buff);
		break;
	case 2: // qsort
		fgets(buff, RECORD_MAX, stdin);
		sscanf(buff, "%d", &no);
		n = read_goods(food_tab, no, stdin, 0);
		Date curr_date;
		int days;
		scanf("%d %d %d", &curr_date.day, &curr_date.month, &curr_date.year);
		scanf("%d", &days);
		printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
		break;
	case 3: // succession
		scanf("%d", &no);
		const int no_persons = sizeof(person_tab) / sizeof(Person);
		create_list(person_tab, no_persons);
		print_person(person_tab + no - 1);
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}

