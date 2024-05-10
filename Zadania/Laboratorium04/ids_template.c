#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char identifiers[MAX_IDS][MAX_ID_LEN];

const char* keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

int find_idents() {
	char tmp1 = getchar();
	char tmp2;
	int last_ident = 0;
	char current_string[MAX_ID_LEN] = { 0 };
	int last_current_idx = 0;
	while ((tmp2 = getchar()) != EOF)
	{
		if (tmp1 == '/' && tmp2 == '*')
		{

			while (!(tmp1 == '*' && tmp2 == '/'))
			{
				tmp1 = tmp2;
				tmp2 = getchar();
			}
			tmp1 = tmp2;
			tmp2 = getchar();
			tmp1 = tmp2;
			tmp2 = getchar();
		}
		if (tmp1 == '/' && tmp2 == '/')
		{
			while (tmp2 != '\n')
			{
				tmp1 = tmp2;
				tmp2 = getchar();

			}
		}
		if (tmp2 == '\'')
		{
			while (!(tmp1 != '\\' && tmp2 == '\''))
			{
				tmp1 = tmp2;
				tmp2 = getchar();
			}
			tmp1 = tmp2;
			tmp2 = getchar();
			tmp1 = tmp2;
			tmp2 = getchar();
		}
		if (tmp2 == '"')
		{
			while (!(tmp1 != '\\' && tmp2 == '"'))
			{
				tmp1 = tmp2;
				tmp2 = getchar();
			}
			tmp1 = tmp2;
			tmp2 = getchar();
			tmp1 = tmp2;
			tmp2 = getchar();

		}

		if (((tmp2 >= '0' && tmp2 <= '9' && last_current_idx != 0) || (tmp2 >= 'A' && tmp2 <= 'Z')
			|| (tmp2 >= 'a' && tmp2 <= 'z') || (tmp2 == '_')))
		{
			current_string[last_current_idx] = tmp2;
			last_current_idx += 1;
		}
		else if (last_current_idx > 0)
		{

			if ((tmp2 == ' ' || tmp2 == '\n'))
			{

				int notInReserved = 1;
				for (int i = 0; i < 31 && notInReserved; ++i)
				{
					notInReserved = strcmp(&current_string, keywords[i]);
				}

				if (notInReserved)
				{
					int unique = 1;
					for (int i = 0; i < last_ident && unique; ++i)
					{
						unique = strcmp(identifiers[last_ident], current_string);
					}
					if (unique)
					{
						last_ident += 1;
						strcpy(identifiers[last_ident], current_string);
					}
				}
			}
			memset(current_string, 0, last_current_idx);
			last_current_idx = 0;
		}
		tmp1 = tmp2;
	}

	return last_ident;
}

int cmp(const void* first_arg, const void* second_arg) {
	char* a = *(char**)first_arg;
	char* b = *(char**)second_arg;
	return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
	int a = *(int*)first_arg;
	int b = *(int*)second_arg;
	return strcmp(identifiers[a], identifiers[b]);
}

int main(void) {
	printf("%d\n", find_idents());
	return 0;
}

