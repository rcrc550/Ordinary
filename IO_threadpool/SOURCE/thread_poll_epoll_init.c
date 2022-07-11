#include<Thread_pool.h>
int thread_pool_epoll_init(int servefd,int max)
{
     struct epoll_event epoll_s;
	 epoll_s.events=EPOLLIN;
	 epoll_s.data.sockfd=servefd;
	 int epfd=epoll_create(max);
	 epoll_ctl(epfd,EPOLL_CTL_ADD,servefd,&epoll_s);
	 return epfd;
}
