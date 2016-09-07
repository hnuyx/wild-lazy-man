#include <stdio.h>
#include <unistd.h>

#define DEST_SIZE 1024
#define TIME_SIZE 1024

int main()
{
	char dest[DEST_SIZE];
	char time[TIME_SIZE];

	printf("please input the Destination: ");
	scanf("%s", dest);

	printf("please input the Time: ");
	scanf("%s", time);

	printf("Please wait");
	fflush(stdout);
	for(int i = 0; i < 10; i ++)
	{
		sleep(1);
		printf(".");
		fflush(stdout);
	}
	sleep(1);
	printf("\n");

	printf("Hey, this the Destination and Time:\n");
	printf("%s %s\n", dest, time);

	return 0;
}
