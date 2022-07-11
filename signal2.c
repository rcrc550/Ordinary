#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
void *job(int n)
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
	newoct.sa_handler=SIG_IGN;
	newoct.sa_flags=0;
	sigemptyset(&newoct.sa_mask);
	sigaction(2,&newoct,&oldoct);
    while(1);
	return 0;

	
}

