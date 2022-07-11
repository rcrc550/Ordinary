#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void job(int n)
{
	while(1)
	{
	   printf("this time is 2022\n");
	   sleep(2);
	}
}
int main()
{
	struct sigaction newoct,oldoct;
	newoct.sa_handler=&job;
	newoct.sa_flags=0;
	sigfillset(&newoct.sa_mask);//当该调用函数产生时 所有信号都不能接受了 因为临时屏蔽字全部变成1
	sigaction(2,&newoct,&oldoct);
    while(1);
	return 0;

	
}

