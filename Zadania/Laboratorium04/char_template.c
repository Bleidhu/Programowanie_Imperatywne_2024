#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_BIGRAMS ((LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR))

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

int count[MAX_BIGRAMS] = { 0 };

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	if (count[va] == count[vb]) return va - vb;	return count[vb] - count[va];
}

// sort indices according to their respective counts.
// sort alphabetically if counts equal
int cmp_di (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	// sort according to second char if counts and the first char equal
	if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
	// sort according to first char if counts equal
	if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
	return count[vb] - count[va];
}

// count lines, words & chars in a given text file
void wc(int *nl, int *nw, int *nc) {
	*nl=*nw=*nc=0;
	int spaces=0;
	char tmp;

	while((tmp=getchar())  != EOF)
	{
		*nc += 1;
		//printf("%c", tmp);
		if(isspace(tmp))
		{
			if(tmp == '\n')
			{
				*nl += 1;
			}
			if(spaces == 0) 
			{
				*nw += 1;
			}
			spaces = 1;
		} else
		{
			spaces = 0;
		}

		//scanf("%c", &tmp);
	}


}

void char_count(int char_no, int *n_char, int *cnt) {
	char tmp;
	while((tmp=getchar()) != EOF)
	{
		
		if(tmp >= FIRST_CHAR && tmp < LAST_CHAR)
		{
			count[tmp - FIRST_CHAR] += 1;
		}
	}

	int indexes[MAX_CHARS + 1];
	for(int i = 0; i < MAX_CHARS + 1; ++i)
	{
		indexes[i] = i;
	}


	qsort(indexes, MAX_CHARS, sizeof(int), cmp);
	*n_char = FIRST_CHAR + indexes[char_no - 1];
	*cnt = count[*n_char - FIRST_CHAR];
}

void bigram_count(int bigram_no, int bigram[]) {
	int indexes[MAX_BIGRAMS];
	for(int i = 0; i < MAX_BIGRAMS; ++i)
	{
		indexes[i] = i;
	}

	
	char tmp1 = getchar();
	char tmp2;
	while((tmp2=getchar()) != EOF)
	{
		
		if(tmp1 >= FIRST_CHAR && tmp1 < LAST_CHAR && tmp2 >= FIRST_CHAR && tmp2 < LAST_CHAR)
		{
			count[(tmp1 - FIRST_CHAR)*MAX_CHARS + tmp2 - FIRST_CHAR] += 1;
		}
		tmp1 = tmp2;
	}

	

	qsort(indexes, MAX_BIGRAMS, sizeof(int), cmp_di);
	bigram[0]=indexes[bigram_no-1]/MAX_CHARS + FIRST_CHAR;
	bigram[1]=indexes[bigram_no-1]%MAX_CHARS + FIRST_CHAR;
	bigram[2] = count[(bigram[0] - FIRST_CHAR) *MAX_CHARS + bigram[1] - FIRST_CHAR];
}

void find_comments(int *line_comment_counter, int *block_comment_counter) {
	*line_comment_counter=*block_comment_counter=0;
	int active_multilines = 0;
	int active_single_lines = 0;

	char tmp1 = getchar();
	char tmp2;
	while((tmp2=getchar()) != EOF)
	{
		
		
		if(tmp1=='/')
		{
			if (tmp2=='/')
			{
				while(getchar()!='\n');
				*line_comment_counter+=1;
			} else if(tmp2=='*')
			{
				tmp1 = tmp2;
				tmp2=getchar();
				if(tmp2=='/')
				{
					tmp1=tmp2;
					tmp2=getchar();
				}
				while (!(tmp1=='*' && tmp2=='/'))
				{
					tmp1=tmp2;
					tmp2=getchar();
				}
				*block_comment_counter+=1;
			}
		}

		tmp1=tmp2;
	}

}

#define MAX_LINE 128

int read_int() {
	char line[MAX_LINE];
	fgets(line, MAX_LINE, stdin); // to get the whole line
	return (int)strtol(line, NULL, 10);
}

int main(void) {
	int to_do;
	int nl, nw, nc, char_no, n_char, cnt;
	int line_comment_counter, block_comment_counter;
	int bigram[3];

	to_do = read_int();
	switch (to_do) {
		case 1: // wc()
			wc (&nl, &nw, &nc);
			printf("%d %d %d\n", nl, nw, nc);
			break;
		case 2: // char_count()
			char_no = read_int();
			char_count(char_no, &n_char, &cnt);
			printf("%c %d\n", n_char, cnt);
			break;
		case 3: // bigram_count()
			char_no = read_int();
			bigram_count(char_no, bigram);
			printf("%c%c %d\n", bigram[0], bigram[1], bigram[2]);
			break;
		case 4:
			find_comments(&line_comment_counter, &block_comment_counter);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

