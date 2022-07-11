#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
void *job(void *a)
{
	while(1);
}
int main()
{
	void *l1;
	size_t l2;
	pthread_attr_t attr,attr2;
	pthread_attr_init(&attr);
	int this;
	pthread_attr_getstack(&attr,&l1,&l2);
	printf("default address%p size%d\n",l1,l2);
	
	l2=0x100000;
	int i=0;
	while(1)
	{
		pthread_attr_t attr1;
		pthread_attr_init(&attr1);
	if((l1=malloc(l2))==NULL)
	{
		perror("no place\n");
	pthread_attr_destroy(&attr1);
		return 0;
	}
	pthread_t tid2;
	pthread_attr_setstack(&attr1,l1,l2);
	int err;
	if((err=pthread_create(&tid2,&attr1,job,NULL))>0)
	{
		pthread_attr_destroy(&attr1);
		printf("create failed%s\n",strerror(err));
		exit(0);
	}
	pthread_attr_destroy(&attr1);
	printf("this is%d\n",i);
	i++;
	}
	return 0;
}

