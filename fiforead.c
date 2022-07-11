#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
  int fd=open("0416",O_RDWR);
  printf("what the fuck\n");
  if(fd==0)
  {
	  printf("open failed\n");
	  return -1;
  }
  char szbuf[100];
  read(fd,szbuf,sizeof(szbuf));
  printf("%s\n",szbuf);
  read(fd,szbuf,sizeof(szbuf));
  close(fd);
  return 0;
}
