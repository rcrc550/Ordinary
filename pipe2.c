#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
   int arr[2];
   pipe(arr);
   pid_t pid;
   pid=fork();
   close(arr[1]);
   if(pid>0)
   {
	   
	   
	 
   
   }
   else if(pid==0)
   {
	   //fork();
      
	  
	  char szbuf[20];
	  //bzero(szbuf,sizeof(szbuf));
	  
	//int fd2=open("pipe.c",O_RDONLY);
	//while(1)
//	{
       int k=read(arr[0],szbuf,sizeof(szbuf));
       printf("%d\n",k);
	//   printf("%s\n",szbuf);
  //  } // int i=read(arr[0],szbuf,sizeof(szbuf));
	  //sleep(1);
      //int o=read(arr[0],szbuf,sizeof(szbuf));
	// printf("%d %s\n",k,szbuf);
	  
	 //printf("%d %s\n",i,szbuf);
   }
   else 
   {
	   printf("create process failed\n");
	   return -1;
   }
	return 0;
}
