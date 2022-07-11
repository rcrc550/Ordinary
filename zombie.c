#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid1;
	pid_t pid3;
	pid1=fork();
    pid3=fork();	
	if(pid1>0&&pid3>0)
	{
		pid_t pid2;
       printf("my son is %d\n",pid1);
	   printf("i am %d\n",getpid());
	   while((pid2=wait(NULL))!=-1)
	   {
	    printf("my son %d is died\n",pid2);
	   }
	   while(1)
		   sleep(1);
	}
	else if(pid1==0)
	{
	   wait(NULL);
       printf("dad i miss you\n");
	   sleep(1);
	   exit(0);
	   
	}
	else if(pid3==0)
	{
      exit(0);
	}
	else
	perror("create son failed");	
	return 0;
}
