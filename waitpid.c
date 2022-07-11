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
		
		pid_t pidright;
       printf("my son is %d\n",pid1);
	   printf("i am %d\n",getpid());
	   while((pidright=waitpid(-1,NULL,WNOHANG))!=-1)
	   {
		 if(pidright>0)
		 {
	      printf("my son %d is died\n",pidright);
		  break;
		 }
		 else
		 {
			 printf("no return \n");
			 sleep(1);
		 }
			 

	   }
	   while(1)
		   sleep(1);
	}
	else if(pid1==0)
	{
	   
       printf("dad i miss you\n");
	   sleep(4);
	   exit(0);
	   
	}
	else
	perror("create son failed");	
	return 0;
}
