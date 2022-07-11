#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main()
{
	sigset_t newsig,oldsig;
	sigemptyset(&newsig);
	sigaddset(&newsig,SIGINT);
	sigprocmask(SIG_SETMASK,&newsig,&oldsig);
	while(1)
	{
		for(int i=0;i<32;i++)
        {
            sigset_t sigset;
			sigpending(&sigset);
            int c=sigismember(&sigset,i);
			if(c==1)
			putchar('1');
			else
				putchar('0');
		}
		printf("\n");
		sleep(2);
	}
	
}

