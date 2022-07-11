#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
int main()
{
   int arr[2];
   pipe(arr);
   pid_t pid;
   pid=fork();
   if(pid>0)
   {
	   close(arr[0]);
     // close(arr[1]);
	  char szbuf[7]="thisis";
	 write(arr[1],szbuf,sizeof(szbuf));
	 
   }
   else if(pid==0)
   {

//close(arr[1]);
	   pid_t pid2;
	   pid2=fork();
	   if(pid2>0)
	   {
		   close(arr[1]);
		   sleep(1);
	     char szbuf[14]=" ";
	     bzero(szbuf,sizeof(szbuf));
		 int k;
	     while(k!=0)
		 {
          k=read(arr[0],szbuf,sizeof(szbuf));
	     printf("%s\n",szbuf);
	   }
	   }
	   else if(pid2==0)
	   {
           close(arr[0]);
	     char szbuf[7]="thisas";
	     write(arr[1],szbuf,sizeof(szbuf));
		 while(1)
			 sleep(1);
	   }
	   else
	   {
		   printf("create failed\n");
		   return 0;
	   }
   }
   else 
   {
	   printf("create process failed\n");
	   return -1;
   }
	return 0;
}
