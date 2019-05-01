#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define SEED 35791246

int count;
int niter;
//void *getn();
void *getcount();

main(int argc, char* argv)
{
	niter = atoi(argv[1]);
   	double pi;
   	pthread_t tid;
   	pthread_attr_t attr;


   	//pthread_attr_init(&attr);
   	pthread_attr_init(&attr);

	/* create the thread */
   	//pthread_create(&tid,&attr,getn);
	pthread_create(&tid,&attr,getcount);
	/* now wait for the thread to exit */
	//pthread_join(tid,NULL);
	pthread_join(tid,NULL);

	pi=(double)count/niter*4;
	printf("# of trials= %d , estimate of pi is %g \n",niter,pi);
}

void *getcount()
{
   //niter = 0;
	double x,y;
	int i;
	count = 0; /* # of points in the 1st quadrant of unit circle */
	double z;

   //printf("Enter the number of iterations used to estimate pi: ");
   //scanf("%d",&niter);

   /* initialize random numbers */
	srand(SEED);
   

//   printf("n = %d\n", niter);
	for (i = 0; i < niter; i++)
	{
    	x = (double)rand()/RAND_MAX;
    	y = (double)rand()/RAND_MAX;
    	z = x*x+y*y;
    	if(z <= 1)
        	count++;
	}
}