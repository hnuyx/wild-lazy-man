/* File Name: kmp.cpp
 *
 * Description: kmp string match
 *
 * Created by henuyx on 2015-05-04
 *
 */

/*******************INCLUDE*******************************/
#include <stdio.h>
#include <string.h>

/*******************GLOBAL********************************/

// get next array
int get_next(const char *pstr, int *next)
{
	int i = 0;
	int k = -1;
	int plen = strlen(pstr);
	int mlen = plen - 1;

	next[i] = k;
	while(i < mlen)
	{
		if((-1 == k) || (pstr[i] == pstr[k]))
		{
			next[++ i] = ++ k;
		}
		else
		{
			k = next[k];
		}
	}

	return plen;
}

// get next array
int get_next2(const char *pstr, int *next)
{
	int i = 0;
	int k = -1;
	int plen = strlen(pstr);
	int mlen = plen - 1;

	next[i] = k;
	while(i < mlen)
	{
		if(pstr[++ i] != pstr[++ k])
		{
			next[i] = k;
			while((-1 != k) && (pstr[i] != pstr[k]))
			{
				k = next[k];
			}
		}
		else
		{
			next[i] = next[k];
		}
	}

	return plen;
}

// get next array
int get_next3(const char *pstr, int *next)
{
	int i = 0;
	int k = -1;
	int plen = strlen(pstr);
	int mlen = plen - 1;

	next[i] = k;
	while(i < mlen)
	{
		if((-1 == k) || (pstr[i] == pstr[k]))
		{
			next[++ i] = ++ k;
			// here is the modification
			if(pstr[i] == pstr[k])
			{
				next[i] = next[k];
			}
			// end the modification
		}
		else
		{
			k = next[k];
		}
	}

	return plen;
}

void print_int_array(int *a, int n)
{
	for(int i = 0; i < n; i ++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int next[16];

	char p[][32] =
		{
			"abacadd",
			"aaaaaaa",
			"abcdefd",
			"abcdabd",
			"abacab",
			"abcdaabcab",
			"abaabcac",
			"ababac",
			"abacacb",
			"abababab"
		};
	for(int i = 0; i < 10; i ++)
	{
		int len = get_next(p[i], next);
		print_int_array(next, len);
		len = get_next2(p[i], next);
		print_int_array(next, len);
		len = get_next3(p[i], next);
		print_int_array(next, len);
		printf("\n");
	}

	return 0;
}

/*******************EOF***********************************/
