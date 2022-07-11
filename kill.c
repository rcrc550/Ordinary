#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid1;
	pid1=fork();
	
	if(pid1>0)
	{
		exit(0);
	}
	else if(pid1==0)
	{
		sleep(1);
	   while(1)
	   {
		   sleep(1);
        printf("dad i miss you\n");
	   }
	   exit(0);
	   
	}
	else
	perror("create son failed");	
	return 0;
}
