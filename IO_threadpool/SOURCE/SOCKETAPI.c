#include<SOCKETAPI.h>

int SOCKET(int a,int b,int c)
{
    int reval;
	if((reval=socket(a,b,c))==-1)
	{
         perror("socket call failed");
         exit(-1);
	}
   return reval;

}
int BIND(int a,const struct sockaddr* b,socklen_t c)
{
	int reval;
	if((reval=bind(a,b,c))==-1)
	{
		perror("bind call failed");
		exit(-1);
	}
	return reval;
}
int ACCEPT(int a,struct sockaddr* b,socklen_t *c)
{

	int reval;
	if((reval=accept(a,b,c))==-1)
	{
		perror("accept call failed");
		exit(-1);
	}
	return reval;
}
int LISTEN(int a,int b)
{
	int reval;
	if((reval=listen(a,b))==-1)
	{

		perror("listen call failed");
		exit(-1);
	}
	return reval;
}
int CONNECT(int a,const struct sockaddr *b,socklen_t c)
{
    int reval;
	if((reval=connect(a,b,c))==-1)
	{
		perror("connect call failed");
		exit(-1);

	}
   return reval;
}
ssize_t RECV(int a,void *b,size_t c,int d)
{

	ssize_t reval;
	if((reval=recv(a,b,c,d))==-1)
	{
		perror("recv call failed");
		exit(-1);
	}
	return reval;
}
ssize_t SEND(int a,const void*b,size_t c,int d)
{

  ssize_t reval;
  if((reval=send(a,b,c,d))==-1)
  {
	  perror("send vall failed");
	  exit(-1);
  }

   return reval;
 

}
