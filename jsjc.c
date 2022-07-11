#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(void)
{
   
   pid_t pid;
   pid=fork();
   if(pid>0)
   {
     pid_t mpid;
     printf("1\n");
     printf("i pid is%d \n",getpid());
     mpid=wait(NULL);
     printf("this pid is %d\n",mpid);
     while(1)
     sleep(1);
   }
   else if(pid==0)
   {
     printf("2\n");
     sleep(5);
     exit(0);
   }
   else 
   {  
     printf("3");
     exit(0);
   }
  return 0;
}
