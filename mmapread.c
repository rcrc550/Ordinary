#include<stdio.h>
#include<string.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
typedef struct 
{
	int c;
	char arr[15];
}game_pack;
int main()
{
    int fd=open("lpl",O_RDWR);
    int	length=lseek(fd,0,SEEK_END);
	game_pack *str=NULL;
	//ftruncate(fd,0x1000);
	if((str=mmap(NULL,sizeof(game_pack),PROT_READ,MAP_SHARED,fd,0))==MAP_FAILED)
	{
         perror("mmap failed\n");
		 return -1;
	}
	close(fd);
	
	
     while(1)
    {
		
		printf("%d %s\n",str->c,str->arr);
        
		sleep(2);
	}



	return 0;
}
