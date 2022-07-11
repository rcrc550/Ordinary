#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(pid>0)
	{
      printf("father id%d\n",getpid());
	  printf("father group%d\n",getpgrp());
	  while(1)
		  sleep(1);
	}
	else if(pid==0)
	{
         
      printf("son id%d\n",getpid());
      printf("son's father id%d\n",getppid());
      printf("son group id%d\n",getpgrp());

      setpgid(getpid(),getpid());
      printf("son id%d\n",getpid());
      printf("son's father id%d\n",getppid());
      printf("son group id%d\n",getpgrp());
	  while(1)
		  sleep(1);
	}
	
}
