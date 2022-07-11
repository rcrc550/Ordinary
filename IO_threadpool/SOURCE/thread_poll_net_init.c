#include<Thread_pool.h>
#include<SOCKETAPI.h>
int  thread_poll_net_init(void)
{
     struct sockaddr_in serveaddr;
	 serveaddr.sin_family=AF_INET;
	 serveaddr.sin_port=htons(8000);
	 inet_pton(AF_INET,"127.0.0.1",&serveaddr.sin_addr.s_addr);
	 int socketfd=socket(AF_INET,SOCK_STREAM,0);
	 bind(socketfd,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
	 listen(socketfd,128);
	 return socketfd;
}
