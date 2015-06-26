/* one2nine.cpp
 * key: [0 1 2 3 4 5 6 7 8 9] --> value: count
 * created by liuh on 20150-06-26
 */

#include <stdio.h>
#include <stdlib.h>

void help()
{
	printf("./exe <limit-number>\n");
	return ;
}

int main(int argc, char **argv)
{
	// counter
	int count[10] = {0};
	// limit, digit
	int limit = 0;
	int digit = 0;

	// check argument
	if(argc != 2)
	{
		help();
		return -1;
	}

	// get limit
	limit = atoi(argv[1]);

	// check limit
	if(limit <=0)
	{
		help();
		return -1;
	}

	// get digits
	int t = limit;
	while(t > 0)
	{
		++ digit;
		t /= 10;
	}

	// get count
	int tmp = 0;
	for(int i = 0; i < limit; i ++)
	{
		t = i;
		tmp = 0;
		while(t > 0)
		{
			++ tmp;
			++ count[t%10];
			t /= 10;
		}

		if(digit > tmp)
		{
			count[0] += digit - tmp - 1;
		}
	}

	for(int i = 0; i < 10; i ++)
	{
		printf("%d ==> %d\n", i, count[i]);
	}

	return 0;
}
