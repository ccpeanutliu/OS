#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256
#define READ_END 0
#define WRITE_END 1

int main(int argc, char const *argv[])
{
//	argv[1]
	FILE *fp;
	FILE *fo;
    int r1;
    char buff[255];
    fp = fopen(argv[1], "r");
    fo = fopen(argv[2],"w");

	int fd[2];
	
  	while(!feof(fp))
  	{
  		fgets(buff, 255, (FILE*)fp);
  		char write_msg[BUFFER_SIZE];
  		strcpy(write_msg, buff);
  		char read_msg[BUFFER_SIZE];
		if(pipe(fd) == -1)
		{
			fprintf(stderr, "Pipe failed." );
		}

		if(fork() == 0)
		{
			close(fd[READ_END]);
	    //	printf("parent sending message\n");
		    write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
	    	close(fd[WRITE_END]);
		}
		else if (fork() < 0)
		{
			fprintf(stderr, "Fork failed.");
			return 1;
		}
		else
		{
			close(fd[WRITE_END]);
			read(fd[READ_END], read_msg, BUFFER_SIZE);
			fputs(read_msg,fo);
	    // 	printf("read %s\n", read_msg);
	      	close(fd[READ_END]);
		}
	}
	fclose(fo);
	return 0;
}