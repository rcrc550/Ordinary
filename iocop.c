#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
	if(argc<4)
	{
		printf("few arguments\n");
		return -1;
	}
	int c=atoi(argv[3]);
		if(c<=0||c>100)
		{
			printf("process too many\n");
			return -1;
		}
	int fd=0;
	fd=open(argv[1],O_RDONLY);
	if(fd<0)
	{
		printf("open file failed\n");
		return -1;
	}
	pid_t pid;
	int q;
	for(int i=0;i<c;i++)
	{
		q=i;
		pid=fork();
		if(pid<=0)break;
		
	}
	int p=lseek(fd,0,SEEK_END);
	int g=p/c;
	if(pid==0)
	{
		int cs=q*g;
		char agk1[20];
		sprintf(agk1,"%d",cs);
		char agk2[20];
		sprintf(agk2,"%d",g);
		execl("/home/colin/0714/process/copy","copy",argv[1],argv[2],agk1,agk2,NULL);
		exit(0);
	}
	else if(pid>0)
	{
		pid_t i;
		while((i=waitpid(-1,NULL,WNOHANG))!=-1)
		{
			if(i>0)
				printf("pid %d my son is died\n",i);


		}
	}
	else
	{
		printf("create process failed\n");
		return -1;
	}

	return 0;
}
