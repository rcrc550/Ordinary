#include<SOCKETAPI.h>
#define IP "127.0.0.1" 
#define PORT 8000
#define TIMEOUT 1
#define ALWAYS 1
#define BLACKLOG 128
#define SIZE 1500
int main(void)
{
	struct sockaddr_in serveaddr,clientaddr;
	bzero(&serveaddr,sizeof(serveaddr));
	serveaddr.sin_family=AF_INET;
	serveaddr.sin_port=htons(PORT);
	inet_pton(AF_INET,IP,&serveaddr.sin_addr.s_addr);
    int servefd=SOCKET(AF_INET,SOCK_STREAM,0);
	int maxfd=servefd;
	BIND(servefd,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
	LISTEN(servefd,BLACKLOG);
	fd_set listen_set,ready_set;
    FD_ZERO(&listen_set);
    int flag=0;
	int buffer[1024];
	bzero(&buffer,sizeof(buffer));
	FD_SET(servefd,&listen_set);
	printf("set serevefd listen %d ok\n",servefd);
    int readycode,readysize;
	int client[1024];
	socklen_t slient;
	for(int i=0;i<1024;i++)
	{
		client[i]=-1;
	}
    while(ALWAYS)
    {
	     ready_set=listen_set;
		 readycode=select(maxfd+1,&ready_set,NULL,NULL,NULL);
		 while(readycode)
		 {
			if(FD_ISSET(servefd,&ready_set))
			{  
                slient=sizeof(clientaddr);
				int clientfd=ACCEPT(servefd,(struct sockaddr*)&clientaddr,&slient);
                if(maxfd<clientfd)
				maxfd=clientfd;
				FD_SET(clientfd,&listen_set);
				for(int i=0;i<1024;i++)
				{
					if(client[i]==-1)
					{
                       client[i]=clientfd;
					   break;
					}
				}
			}
			else
			{
				for(int i=0;i<1024;i++)
				{
					if(client[i]!=-1&&FD_ISSET(client[i],&ready_set))
					{
                         readysize=RECV(client[i],buffer,sizeof(buffer),0);
						 if(readysize==0)
						 {
                              printf("clientfd%d out of connect",client[i]);
							  FD_CLR(client[i],&listen_set);
							  close(client[i]);
							  client[i]=-1;
						 }
						 else
						 {
							 flag=0;
							   printf("recv size is %d\n",readysize);
						 while(readysize)
						 {
							   if(flag<readysize)
							   buffer[flag]=toupper(buffer[flag]);
							   flag++;
                               readysize--;

						 }
						 bzero(&buffer,sizeof(buffer));
						 int sendsize=SEND(client[i],buffer,sizeof(buffer),0);
                          printf("send size is %d\n",sendsize);
						 }
					}
				}

			}

            readycode--;
		 }
	}
           return 0;
	}

