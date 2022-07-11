#include<SOCKETAPI.h>
#define   SERVE_IP "127.0.0.1"
#define   SERVE_PORT 8000
int main(void)
{
   struct sockaddr_in serveaddr;
   bzero(&serveaddr,sizeof(serveaddr));
   serveaddr.sin_family=AF_INET;
   serveaddr.sin_port=htons(SERVE_PORT);
   inet_pton(AF_INET,SERVE_IP,&serveaddr.sin_addr.s_addr);
   int clientfd=SOCKET(AF_INET,SOCK_STREAM,0);
   printf("this 1 pid is %d\n",getpid());
   
   
   
   if(CONNECT(clientfd,(struct sockaddr*)&serveaddr,sizeof(serveaddr))==0)
   {
       printf("this pid %d is connect successfuly\n",getpid());
   }
   char buffer[1024];
   bzero(buffer,sizeof(buffer));
   int rsize,wsize;
   while(fgets(buffer,sizeof(buffer),stdin)!=NULL)
   {
      wsize=SEND(clientfd,buffer,strlen(buffer),0);
	  printf("this send size is %d\n",wsize);
	  rsize=RECV(clientfd,buffer,sizeof(buffer),0);
	  printf("this read size is %d,buffer is %s\n",rsize,buffer);
      bzero(buffer,sizeof(buffer));
   }
   close(clientfd);
   return 0;



}
