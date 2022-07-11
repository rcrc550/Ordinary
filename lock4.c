#include<pthread.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>

int main()
{


	struct flock oldflock;
    int fd=open("lock1.c",O_RDWR);
    fcntl(fd,F_GETLK,&oldflock);
     oldflock.l_type=F_UNLCK;
	 fcntl(fd,F_SETLK,&oldflock);
    fcntl(fd,F_GETLK,&oldflock);
	printf("1\n");
	int i1=(int)oldflock.l_type;
	int i2=(int)F_WRLCK;
	int i3=(int)F_RDLCK;
	int i4=(int)F_UNLCK;
	printf("this%d,wr%d,rd%d,un%d\n",i1,i2,i3,i4);
	if(oldflock.l_type==F_UNLCK)
	{
		printf("3\n");
		   

	}
	printf("2\n");
	close(fd);
    

   return 0;
}
