#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int n;
	scanf("%d",&n);

	if(fork() == 0)
	{
		while(1)
		{	
			printf("%d,",n);
			if(n % 2 == 0)
			{
				n = n / 2;
			}
			else
			{
				n = 3 * n + 1;
			}

			if(n == 1)
			{
				printf("%d",n);
				break;
			}
		}
	}
	else if(fork < 0)
	{
		printf("error!!!");
		return 1;
	}
	else
	{
		wait(NULL);
		//printf("Children Complete!!!");
	}
}