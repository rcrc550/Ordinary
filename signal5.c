#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void waitfor(int n)
{
	printf("dad is coming\n");
	pid_t job;
	   while((job=waitpid(-1,NULL,WNOHANG))>0)
	   {
         printf("son %d has gone\n",job);
	   }
}
int main(int k)
{

   
	struct sigaction newoct,oldoct;
	newoct.sa_handler=waitfor;
	newoct.sa_flags=0;
	sigemptyset(&newoct.sa_mask);
	sigaction(SIGCHLD,&newoct,&oldoct);
	pid_t c;
    for(int i=0;i<10;i++)
	{
		
		c=fork();
		if(c==0)break;
	}

    if(c>0)
	{
      while(1)
		  sleep(1);
	}
	else if(c==0)
	{
         exit(0);
	}
	else
     {
		 printf("cretae failed\n");
		 return -1;
	 }

		return 0;
}

