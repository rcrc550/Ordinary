#include<stdio.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<ctype.h>
int SOCKET(int ,int ,int);
int BIND(int,const struct sockaddr*,socklen_t);
int LISTEN(int,int);
int ACCEPT(int, struct sockaddr*,socklen_t*);
int CONNECT(int,const struct sockaddr*,socklen_t);
ssize_t RECV(int,void*,size_t,int);
ssize_t SEND(int, const void*,size_t,int);
