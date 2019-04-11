#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int fd = shm_open("/sz02-shm", O_CREAT|O_RDWR|O_EXCL, 0777);
	if(fd < 0)
	{
		printf("jizz\n");
		return 0;
	}
	else
	{
		ftruncate(fd, 1024);
	}
	close(fd);
	
	if(fork() == 0)
	{

	    int fe = shm_open("/sz02-shm", O_RDWR, 0777);
	    if(fe < 0)
	    {
	        printf("error open shm object\n");
	        return 0;
	    }
	    //printf("WTF");
	    int n;
	    int index = 0;
	    char str[8192];
	    scanf("%d",&n);
	    while(1)
	    {
	    	index += sprintf(&str[index], "%d,", n);
	    	if(n % 2 == 0)
	    	{
	    		n = n/2;
	    	}
	    	else
	    	{
	    		n = 3*n+1;
	    	}
	    	if(n == 1)
	    	{
	    		index += sprintf(&str[index], "%d", n);
	    		break;
	    	}
	    }
	    char* ptr = (char*)mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	    close(fe);
	    strcpy(ptr, str);
		return 0;
	}
	else
	{
		wait(NULL);
		int ff = shm_open("/sz02-shm", O_RDWR, 0777);
	    if(ff < 0)//不存在共享内存对象
	     {
	         printf("error open shm object\n");
	         return 0;
	     }
	    char* ptr = (char*)mmap(NULL, 1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	    close(ff);
	    //getchar();
	    printf("%s\n", ptr);
	    shm_unlink("/sz02-shm");
	    return 0;
	}
}
