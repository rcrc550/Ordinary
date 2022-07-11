#include<pthread.h>
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
typedef struct
{
	int s;
	pthread_mutex_t lock;
}shared_t;
int main()
{

    int fd=open("lpl",O_RDWR|O_CREAT,0664);
	/*struct flock newflock,oldflock;
	newflock.l_type=F_RDLCK;
	newflock.l_whence=SEEK_SET;
	newflock.l_start=0;
    newflock.l_len=sizeof(ag);*/
	ftruncate(fd,sizeof(shared_t));
	
	shared_t *share=mmap(NULL,sizeof(shared_t),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	share->s=0;
	close(fd);
	pthread_mutexattr_t arr;
	pthread_mutexattr_init(&arr);
	pthread_mutexattr_setpshared(&arr,PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share->lock,&arr);


    pid_t pid;
	pid=fork();
	if(pid>0)
	{
		int p=1;
         while(1)
		 {
			 if(p==0)
			 {
				 wait(NULL);
				 break;
			 }
			 pthread_mutex_lock(&share->lock);
			 printf("pthread ox1,s+=%d\n",share->s++);
			 pthread_mutex_unlock(&share->lock);
			 p--;
		 }
		 
	}
	else if(pid==0)
	{
		int i=1;
        while(1)
		{
			if(i==0)break;
			pthread_mutex_lock(&share->lock);
			printf("pthread ox2,s+=%d\n",share->s++);
			pthread_mutex_unlock(&share->lock);
			i--;
		}
	}
    else 
	{
      exit(0);
	}
	pthread_mutexattr_destroy(&arr);
    pthread_mutex_destroy(&share->lock);
	while(1);
    return 0;
}
