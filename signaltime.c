#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void signal_rc(int n)
{
}
unsigned int mysleep(unsigned int i)
{   
	//信号屏蔽
	unsigned int revel;
	sigset_t  net,oet;
	sigemptyset(&net);
	sigaddset(&net,SIGALRM);
	sigprocmask(SIG_SETMASK,&net,&oet);

    //信号捕捉
	struct sigaction nod,ood;
	nod.sa_handler=signal_rc;
    nod.sa_flags=0;
	sigemptyset(&nod.sa_mask);
	sigaction(SIGALRM,&nod,&ood);
	revel=alarm(i);
    sigsuspend(&nod.sa_mask);
	return  revel; 
	
}
int main()
{

    while(1)
	{
	   printf("yeyeye\n");
       mysleep(2);

	}
	return 0;
}
