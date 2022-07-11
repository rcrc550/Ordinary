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
	BIND(servefd,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
	LISTEN(servefd,BLACKLOG);
	struct pollfd listen_set[1024];
	struct pollfd serve;
	serve.fd=servefd;
	serve.events=POLLIN;
	serve.revents=0;
	listen_set[0]=serve;
	for(int i=1;i<1024;i++)
	{
		listen_set[i].fd=-1;
		listen_set[i].events=POLLIN;
		listen_set[i].revents=0;
	}
	int flag=0;
	int buffer[1024];
	bzero(buffer,sizeof(buffer));
	printf("set serevefd listen %d ok\n",servefd);
	int readycode,readysize;
	socklen_t slient;

	while(ALWAYS)
	{
	     int	this=0;     
		readycode=poll(listen_set,1024,-1);
		while(readycode&&this<1024)
		{
			if(listen_set[this].fd!=-1&&listen_set[this].revents==POLLIN)
			{
				if(listen_set[this].fd==servefd)
				{  
					slient=sizeof(clientaddr);
					int clientfd=ACCEPT(servefd,(struct sockaddr*)&clientaddr,&slient);
					
					
					for(int i=0;i<1024;i++)
					{
						if(listen_set[i].fd==-1)
						{
							listen_set[this].fd=clientfd;
							break;
						}
					}
					listen_set[this].revents=0;
				}
				else
				{
				
				readysize=RECV(listen_set[this].fd,buffer,sizeof(buffer),0);
							if(readysize==0)
							{
							printf("clientfd%d out of connect",listen_set[this].fd);
								//FD_CLR(listen_set[this].fd,&listen_set);
								close(listen_set[this].fd);
								listen_set[this].fd=-1;
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

								int sendsize=SEND(listen_set[this].fd,buffer,sizeof(buffer),0);
								printf("send size is %d\n",sendsize);
								bzero(buffer,sizeof(buffer));
							}
							listen_set[this].revents=0;
						}
						readycode--;
					}
					this++;

				

				
			}
		
		
}

		return 0;
	}
