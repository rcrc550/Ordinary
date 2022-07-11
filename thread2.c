#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
void *job(void *a)
{
	int c=4;
	while(c)
	{
		printf("4\n");
		c--;
	}
	return (void*)2;
}
int main()
{
	pthread_attr_t attr,attr2;
	pthread_attr_init(&attr);
	int this;
	pthread_attr_getdetachstate(&attr,&this);
	printf("default detach or join%d\n",this);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_t tid;
	pthread_create(&tid,&attr,job,NULL);
	pthread_attr_destroy(&attr);
	return 0;
}

