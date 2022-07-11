#include<stdio.h>
#include<string.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
typedef struct 
{
	int c;
	char arr[15];
}game_pack;
int main()
{
	umask(000);
    int fd=open("lpl",O_RDWR|O_CREAT);
    //int	length=lseek(fd,0,SEEK_END);
	game_pack *str=NULL;
	ftruncate(fd,sizeof(game_pack));
	if((str=mmap(NULL,sizeof(game_pack),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0))==MAP_FAILED)
	{
         perror("mmap failed\n");
		 return -1;
	}
	close(fd);
	str->c=0;
	
     while(1)
    {
		sprintf(str->arr,"cs%d is my son\n",str->c);
		//printf("%d %s\n",str->c,str->arr);
        str->c++;
		sleep(2);
	}



	return 0;
}
