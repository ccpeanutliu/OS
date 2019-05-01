#include <pthread.h>
#include <stdio.h>

int max;
int avg;
int min;
int n;
void *maxrunner(int param[]);
void *avgrunner(int param[]);
void *minrunner(int param[]);

int main(int argc, char *argv[])
{
	int* arr;
	n = atoi(argv[1]);
	arr = (int*)malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	pthread_t tid, tid1, tid2;
	pthread_attr_t attr, attr1, attr2;
	
	if(argc != 2)
	{
		fprintf(stderr,"usage: a.out <number length>\n");
     	return -1;
	}

	if (atoi(argv[1]) < 0)
	{
    	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
    	return -1;
	}

	/* get the default attributes */
	pthread_attr_init(&attr);
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	/* create the thread */
	pthread_create(&tid,&attr,maxrunner,arr);
	pthread_create(&tid1,&attr1,avgrunner,arr);
	pthread_create(&tid2,&attr2,minrunner,arr);
	/* now wait for the thread to exit */
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	
	printf("max = %d\n",max);
	printf("avg = %d\n",avg);
	printf("min = %d\n",min);
}

void *maxrunner(int param[]) 
{
   max = -100000;

   for(int i = 0; i < n; i++)
   {
   		if(param[i] > max)
   		{
   			max = param[i];
   		}
   }

   pthread_exit(0);
}

void *avgrunner(int param[]) 
{
  	int sum = 0;
	
	for (int i = 0; i < n; i++)
		sum += param[i];
   	avg = sum/n;

   pthread_exit(0);
}

void *minrunner(int param[]) 
{
   min = 1000000;

   for(int i = 0; i < n; i++)
   {
   		if(param[i] < min)
   		{
   			min = param[i];
   		}
   }

   pthread_exit(0);
}
