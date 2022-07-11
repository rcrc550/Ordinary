#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
   if(argc<5)
   {
	   printf("so few arguments\n");
	   return 0;
   }
   umask(0000);
   int c=atoi(argv[3]);
   
   int fd1=open(argv[1],O_RDONLY);
   
   int fd2=open(argv[2],O_WRONLY|O_CREAT,0664);
   
   
   if(fd1==-1||fd2==-1)
   {
	   printf("read craete file failed\n");
	   return 0;
   }
   int a=4;
   lseek(fd1,c,SEEK_SET);
   int n;
   lseek(fd2,c,SEEK_SET);
   
   int py=atoi(argv[4]);
   char szbuf[4096];
   int now=read(fd1,szbuf,py);
   
   if(now<py)
   printf("can't copy all,there is no enough\n");

   write(fd2,szbuf,py);
   close(fd1);
   close(fd2);
   return 0;
}
