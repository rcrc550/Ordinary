#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *job(void *a)
{
    sleep(1);
	int aa=*(int*)a;
	printf("this %d \n",aa);
	pthread_exit(NULL);
}
int main()
{
	int flag;
   for(flag=1;flag>0;flag--)
   {
	   int c=3;
	   pthread_t tid;
       void *cc=(void*)&c;
	   pthread_create(&tid,NULL,job,cc);
	   c=4;
       
   }
   printf("now go\n");
   sleep(3);
   return 0;
}
