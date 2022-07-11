#include<SOCKETAPI.h>
#define   SERVE_IP "127.0.0.1"
#define   SERVE_PORT 8000
void sig_wait(int n)
{
	pid_t wpid;
	while((wpid=waitpid(-1,NULL,WNOHANG))>0)
	{
		printf("clean zombie process pid %d\n",getpid());
	}//回收僵尸进程
}
void *pthread_wait(void *arg)
{ 
	struct sigaction newact,oldact;
	newact.sa_handler=sig_wait;
	newact.sa_flags=0;
	sigempyset(&newact.sa_mask);
	sigaction(SIGCHLD,newact,oldact);
   //继承了了进程主线程的屏蔽，需要取消屏蔽。
   //完成捕捉设定，然后等信号。
    sigpromask(SIG_SETMASK,&newact.sa_mask,NULL);
	printf("wait thread 0x%x\n  waiting",(unsigned int)pthread_self());
	while(1)
		sleep(1);
}
int main(void)
{
   struct sockaddr_in sereveaddr,slientaddr;
   bzero(&sereveaddr,sizeof(sereveaddr));
   sereveaddr.sin_family=AF_INET;
   sereveaddr.sin_port=htons(SERVE_PORT);
   inet_pton(AF_INET,SERVE_IP,&sereveaddr.sin_addr.s_addr);
   int serevefd=SOCKET(AF_INET,SOCK_STREAM,0);
   BIND(serevefd,(struct sockaddr*)&sereveaddr,sizeof(sereveaddr));
   LISTEN(serevefd,128);
   printf("this 1 pid is %d\n",getpid());
   int clientfd;
   socklen_t size=sizeof(clientfd);
   char ip[16];
   pid_t pid;   
   bzero(ip,16);
   //信号屏蔽
   sigset_t newset,oldset;
   sigemptyset(&newset);
   sigaddset(&newset,SIGCHLD);
   sigpromask(SIG_SETMASK,&newset,&oldset);
   pthread_t pid;
   //创建线程来回收僵尸进程
   pthread_create(&pid,NULL,thread_wait,NULL);
   while(1)
   {
   if((clientfd=ACCEPT(serevefd,(struct sockaddr*)&slientaddr,&size))>0)
   {
       printf("parent pid is %d\n",getpid());
	   printf("there is ip %s talking,port is %d\n",inet_ntop(AF_INET,&slientaddr.sin_addr.s_addr,ip,16),ntohs(slientaddr.sin_port));
   }
   pid=fork();
   if(pid>0)
   {
   }
   else if(pid==0)
   {
   char buffer[1024];
   bzero(buffer,sizeof(buffer));
   int rsize,wsize;
   int flag;
   while((rsize=RECV(clientfd,buffer,sizeof(buffer),0))>0)
   {
	 flag=0;  
     printf("sereve child pid is %d, this read size is %d\n",getpid(),rsize);
	 while(flag<rsize)
	 {
		 buffer[flag]=toupper(buffer[flag]);
         flag++;
	  }
     wsize=SEND(clientfd,buffer,rsize,0);
	 printf("sereve child %d wszie is %d\n",getpid(),wsize);
	 bzero(buffer,sizeof(buffer));
   }
   
   
   }
   else 
   {
	  perror("child create failed\n");
	  
	  exit(-1);
   }
   if(rsize==0)
	   exit(0);//一旦客户端退出，该进程也退出,变成了僵尸进程。
   }
   close(clientfd);
   close(serevefd);
   return 0;



}
