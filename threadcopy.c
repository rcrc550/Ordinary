#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>

typedef struct
{
	int size;
	int postion;
}ag;
int all_size;
char *percent;
char *mmap_postion;
float percent_postion;
int fd_target;

void *pthread_copy(void *kc)
{
	//printf("0x%x\n",(unsigned int)pthread_self());
    ag *k=(ag *)kc; 
	printf("i need copy %d\n",(int)k->size);
	int k_size=(int)(k->size);
	//printf("k_size%d\n",k_size);
	char *t=(char*)(mmap_postion+k->postion);
	while(k_size>0)
	{

	   int g=write(fd_target,t,k_size);
	   //printf("this time copy%d\n",g);
	   float gg=(float)g;
	   if(g<0)
	   {
		   perror("write wrong\n");
		   return 0;
	   }
	   k_size-=g;
	   percent_postion=(gg/all_size)*100+percent_postion;
	   int cl=(int)percent_postion;
	   int rate=cl/10;
	   
	   //printf("rate%d\n",rate);
	   int lo=0;
	   while(rate>=lo&&lo<10)
	   {
	    percent[lo]='=';
		lo++;
	   }
	   printf("%s ,百分比%f\n",percent,percent_postion);
	   sleep(1);
	  
	}
	free(k);
	pthread_exit((void*)1);
}

int main(int agrc,char *agrv[])
{
	
   if(agrc<4)
	  {
		  printf("argument tow few\n");
		  return 0;
	  }
   //struct stat buf;
   //int err;
   percent=malloc(sizeof(char)*10);
   //bzero(percent,10);
   for(int i=0;i<10;i++)
	{ 
		percent[i]='-';
    }
   percent_postion=0;
   pthread_t *tid_arr;
   int fd=open(agrv[1],O_RDWR);
   
   fd_target=open(agrv[2],O_RDWR|O_CREAT,0664);
   int size=lseek(fd,0,SEEK_END);
   all_size=size;
   int mmapsize=size;
   if(size<0)
   {
	   perror("open failed\n");
	   return 0;
   }
   int thread_count=atoi(agrv[3]);
   int gg_count=thread_count;
   tid_arr=malloc(sizeof(pthread_t)*thread_count);
   int copy_count=size/thread_count;
   //printf("copy count%d\n",copy_count);
   //sleep(3);
   int pos=0;
   //printf("1\n");
   mmap_postion=mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
   char *map=mmap_postion;
   //printf("2\n");
   //printf("size%d,threadcount%d\n",size,thread_count);
   while(size>0&&thread_count>0)
   {
	   ag *k=(ag*)malloc(sizeof(ag));
	   k->postion=pos*copy_count;
	   pos++;
	   if(size>=copy_count)
	   {
		   //printf("copy_count%d\n",copy_count);
	       k->size=copy_count;
		   //printf("k size%d\n",k->size);
		   size-=copy_count;
	   }
	   else
	   {
		   //printf("k size%d\n",size);
		   k->size=size;
		   size-=size;
	   }
	   pthread_create(&tid_arr[thread_count-1],NULL,pthread_copy,(void*)(k));
	   
	   thread_count--;
   }

   //printf("3\n");
   int c=0;
   
	   //printf("%d\n",thread_count);

   while(c<gg_count)
   {
	   pthread_join(tid_arr[c],NULL);
	   printf("thread0x%x has exit successfully\n",(int)tid_arr[c]);
	   c++;
   }
  // printf("5\n");
   free(tid_arr);
     
   munmap(map,mmapsize);



	return 0;
}
