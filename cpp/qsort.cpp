/* File Name: qsort.h
 *
 * Description: quick sort
 *
 * Created by henuyx on 2015-05-04
 *
 */

/*******************INCLUDE*******************************/
#include <stdio.h>

/*******************GLOBAL********************************/

// swap value
void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}

void qsort(int a[], int n)
{
	if(n <= 1)
	{
		return ;
	}

	int t = 0;

	int i = 0;
	int j = n - 1;
	while(i < j)
	{
		while(j > i)
		{
			if(a[j] < a[t])
			{
				swap(a[j], a[t]);
				t = j;
				break;
			}
			-- j;
		}

		while(i < j)
		{
			if(a[i] > a[t])
			{
				swap(a[i], a[t]);
				t = i;
				break;
			}
			++ i;
		}
	}

	qsort(a, i);
	qsort(a + i + 1, n - i - 1);
}

// print array
void print_a(int a[], int n)
{
	for(int i = 0; i < n ; i ++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main()
{
	int a[] = {6, 2, 7, 3, 8, 9};
	qsort(a, 6);
	print_a(a, 6);

	int b[] = {20, 10, 5, 12, 31, 24, 15, 18, 19, 25, 14, 13, 8, 26, 6, 7, 4, 23, 30, 27, 11, 22, 2, 1, 32, 17, 33, 21, 9, 3, 29, 28, 16};
	qsort(b, 33);
	print_a(b, 33);

	return 0;
}

/*******************EOF***********************************/
