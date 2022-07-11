#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
pthread_mutex_t lock;
pthread_cond_t cond1;
pthread_cond_t cond2;
int k;

void *job1(void *b)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(k%2==0)
            pthread_cond_wait(&cond1,&lock);  
			k++;
			usleep(5000);
			printf("k is %d\n",k);
			if(k==100)
			{
		 
		    pthread_mutex_unlock(&lock);
		     pthread_cond_signal(&cond2);
				break;
			}
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond2);
	}
	return (void*)6;
}

void *job2(void *a)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(k%2==1)
            pthread_cond_wait(&cond2,&lock);
			if(k<100)
			{
			 k++;
			 printf("k is %d\n",k);
			 usleep(5000);
			}
			else
				break;
			
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond1);
	}
	return (void *)5;
}

int main(void)
{
    pthread_mutex_init(&lock,NULL);
	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond2,NULL);
    k=0;
	pthread_t tid1,tid2;
	printf("1\n");
    pthread_create(&tid1,NULL,job1,NULL);
    pthread_create(&tid2,NULL,job2,NULL);
    pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
    printf("2\n");
    pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond1);
    pthread_cond_destroy(&cond2);
return 0;
}
