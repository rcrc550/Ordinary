#include<SOCKETAPI.h>
#define   SERVE_IP "127.0.0.1"
#define   SERVE_PORT 8000
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
   
   bzero(ip,16);
   if((clientfd=ACCEPT(serevefd,(struct sockaddr*)&slientaddr,&size))>0)
   {
       printf("this pid 2 is %d\n",getpid());
	   printf("there is ip %s talking,port is %d\n",inet_ntop(AF_INET,&slientaddr.sin_addr.s_addr,ip,16),ntohs(slientaddr.sin_port));
   }
   char buffer[1024];
   bzero(buffer,sizeof(buffer));
   int rsize,wsize;
   int flag;
   while((rsize=RECV(clientfd,buffer,sizeof(buffer),0))>0)
   {
	 flag=0;  
     printf("this read size is %d\n",rsize);
	 while(flag<rsize)
	 {
		 buffer[flag]=toupper(buffer[flag]);
         flag++;
	  }
     wsize=SEND(clientfd,buffer,rsize,0);
	 printf("wszie is %d\n",wsize);
	 bzero(buffer,sizeof(buffer));
   }
   close(serevefd);
   close(clientfd);
   return 0;



}
