#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void job(int n)
{
	printf("time is out\n");
	   
}
int mysleep(int k)
{

    sigset_t newset;
	sigemptyset(&newset);
	sigaddset(&newset,SIGALRM);
	struct sigaction newoct,oldoct;
	newoct.sa_handler=&job;
	newoct.sa_flags=0;
	sigemptyset(&newoct.sa_mask);
	sigaction(SIGALRM,&newoct,&oldoct);
    int c=alarm(k);
	sigsuspend(&newoct.sa_mask);

    return c;
}
int main()
{

	while(1)
	{
		printf("yes\n");
		mysleep(2);
	}
	return 0;

	

}

