#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
int main()
{
   
	  char szbuf[1024];
	  bzero(szbuf,sizeof(szbuf));
	  char arr[5]="wqe";
      int k=read(3,szbuf,sizeof(szbuf));
	  printf("%d\n",k);
	  
	return 0;
}
