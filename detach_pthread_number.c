#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
void *this_hs(void *agc)
{
	while(1)
		sleep(1);
     pthread_exit((void *)0);

}
int main(void)
{
	pthread_attr_t mattr;
	pthread_t pid;
	size_t i=0x100000;
	int err;
	void *arr;
	int p=1;
	while(1)
	{
		pthread_attr_init(&mattr);
		if((arr=malloc(i))==NULL)
		{
			printf("没有多余的地址\n");
			exit(0);
			pthread_attr_destroy(&mattr);
		}
		pthread_attr_setstack(&mattr,arr,i);
		if((err=pthread_create(&pid,&mattr,this_hs,NULL))>0)
		{

			printf("创建失败%s\n",strerror(err));
			exit(0);
			pthread_attr_destroy(&mattr);
		}
		p++;
		printf("this is number %d\n",p);
	}
			pthread_attr_destroy(&mattr);
	return 0;
}
