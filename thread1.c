#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
void *thread_job(void *ak)
{
	pthread_detach(pthread_self());
    pthread_exit((void*)6);
}
void *thread_job2(void *ac)
{
	return (void*)11;
//	exit(0);
}
void *thread_job3(void *al)
{
	return (void*)3;
}
void *thread_job4(void *al)
{
	while(1)
	{
		printf("today is 0426\n");
		sleep(1);
	}
}
int main()
{
	void *ar;
	void *ar2;
	void *ar3;
	void *ar4;
	void *ar5;
    pthread_t  tid,tid2,tid3,tid4,tid5;
	printf("my tid is0x%x\n",(unsigned int)pthread_self());
	int err;
	if((err=pthread_create(&tid,NULL,thread_job,NULL))>0)
	{
		printf("create failed %s\n",strerror(err));
		return 0;
	}
	if((err=pthread_create(&tid2,NULL,thread_job2,NULL))>0)
	{
		printf("create failed 2%s\n",strerror(err));
		return 0;
	}
	if((err=pthread_create(&tid3,NULL,thread_job3,NULL))>0)
	{
		printf("create failed 2%s\n",strerror(err));
		return 0;
	}
	if((err=pthread_create(&tid4,NULL,thread_job4,NULL))>0)
	{
		printf("create failed 2%s\n",strerror(err));
		return 0;
	}
	if((err=pthread_create(&tid5,NULL,thread_job4,NULL))>0)
	{
		printf("create failed 2%s\n",strerror(err));
		return 0;
	}
	printf("4\n");
	int errr;
	if((errr=pthread_join(tid,&ar))>0)
	{
		printf("join failed%s\n",strerror(errr));
	}
	//pthread_kill(tid4,2);  二号信号直接给我进程杀了
	pthread_cancel(tid4);
	printf("pthread10x%x,exit code %d\n",(unsigned int)tid,(int)ar);
	printf("5\n");
	pthread_join(tid2,&ar2);
	printf("pthread20x%x,exit code %d\n",(unsigned int)tid2,(int)ar2);
	pthread_join(tid3,&ar3);
	printf("pthread30x%x,exit code %d\n",(unsigned int)tid3,(int)ar3);
	pthread_join(tid4,&ar4);
	printf("pthread40x%x,exit code %d\n",(unsigned int)tid4,(int)ar4);
	pthread_join(tid5,&ar5);
	printf("pthread0x%x,exit code %d\n",(unsigned int)tid5,(int)ar5);
   
   

	return 0;
}
