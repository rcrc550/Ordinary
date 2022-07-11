#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
void sig_child(int n)
{
	int i;
	while((i=waitpid(-1,NULL,WNOHANG))>0)
	{
		printf("this pid is %d\n",i); 

	}

}
int main(void )
{
	pid_t pid;
	int i;
	struct sigaction nwd,ond;
	nwd.sa_handler=sig_child;
	nwd.sa_flags=0;
	sigemptyset(&nwd.sa_mask);
	sigaction(SIGCHLD,&nwd,&ond);
	for(i=0;i<10;i++)
	{
		pid=fork();
		if(pid==0)
			break;

	}
	if(pid>0)
	{
		while(1)
			sleep(1);
	}
	else if(pid==0)
	{
		exit(0);
	}
	else
	{
		perror("Create Wrong");
		exit(0);
	}

	return 0;
}

