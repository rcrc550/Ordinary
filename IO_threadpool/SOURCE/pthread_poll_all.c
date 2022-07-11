#include<SOCKETAPI.h>
int epfd;
pthread_mutex_t busines_lock;
typedef struct 
{
	void * (*BUSINES_ADDR)(void *);
	void * BUSINES_ARG;
}busines_t;
typedef struct
{
	int thread_max;
	int thread_min;
	int thread_shutdown;
	int thread_busy;
	int thread_alive;
	int thread_exitcode;
	pthread_t *customs_tids;
	pthread_t managertid;
	busines_t *busines_queue;
	int front;
	int rear;
	int max;
	int cur;
	int servefd;
	pthread_mutex_lock thread_lock;
	pthread_cond_t not_full;
	pthread_cond_t not_empty;
}threadpool_t;
int thread_pool_net_init(void);
int thread_pool_epoll_init(int servefd,int max);
threadpool_t *thread_pool_create(int max,int min,int queuemax);
int thread_destroy(threadpool_t*a);
int thread_pool_epoll_listen(int epfd,threadpool_t *b,int sockfd);
int thread_pool_add_busines();
threadpool_t *threadpool;
void *customer_job;
void *manager_job;
int if_threadalive(pthread_t);
void *BUS_ACCEPT(void *arg);
void *BUS_RESPONSE(void *arg);
void *customer_job(void *arg)
{
	busines_t bs;
	pthread_detach(pthread_self());
	while(threadpool->thread_shutdown)
	{
		pthread_mutex_lock(&threadpool->thread_lock);
        while(threadpool->cur==0)
		{
			pthread_cond_wait(&threadpool->not_empty,&threadpool->thread_lock);
            if(threadpool->thread_shutdown==0)
			{
				//--alive
				pthread_mutex_unlock(&threadpool->thread_lock);
				pthread_exit(NULL);
				
			}
		}
		    
			++threadpool->cur;
			++threadpool->busy;
			pthread_mutex_unlock(&threadpool->thread_lock);
			bs=threadpool->busines_queue[threadpool->rear];
			bs.BUSINES_ADDR(bs.BUSINES_ARG);
	
		pthread_mutex_lock(&threadpool->thread_lock);
		--threadpool->busy;
	     	pthread_mutex_unlock(&threadpool->thread_lock);
			pthread_cond_signal(&threadpool->not_full);
		
	}
	pthread_exit(NULL);
}
threadpool_t *thread_pool_create(int max,int min,int queuemax)
{
    threadpool->thread_shutdown=1;
	threadpool->thread_max=max;
	threadpool->thread_min=min;
	threadpool->thread_busy=0;
	threadpool->thread_alive=0;
	threadpool->thread_exitcode=0;
	threadpool->customer_tids=(pthread *)malloc(sizeof(pthread)*thread_max);
	for(int i=0;i<thread_max;i++)
	{
		threadpool->customer_tids[i]=-1;
	}
	for(int i=0;i<thread_min;i++)
	{
		pthread_create(&threadpool->customer_tids[i],NULL,customer_job,NULL);
    }
	threadpool->busines=(busines_t *)malloc(sizeof(busines_t)*queuemax);
	threadpool->front=0;
	threadpool->thread_exitcode=0;
	threadpool->cur=0;
	threadpool->rear=0;
	threadpool->max=queuemax;
	pthread_mutex_init(&threadpool->thread_lock);
	pthread_cond_init(&threadpool->not_full,NULL);
	pthread_cond_init(&threadpool->not_empty,NULL);
	return NULL;
}
int thread_pool_add_busines(thread_pool_t*t,busines_t bs)
{
    thread_pool *p=threadpool;
    
		pthread_mutex_lock(&p->thread_lock);
        while(p->cur==p->max)
		{
           pthread_cond_wait(&p->not_full,&p->thread_lock);
		   //如果线程退出了做一下处理 shutdown此时为0
		}
        ++p->cur;
		p->busines_queue[p->front].BUSINES_ADDR=bs.BUSINE_ADDR;
		p->busines_queue[p->front].BUSINES_ARG=bs.BUSINE_ARG;
		p->front=(p->front+1)%p->max;
		pthread_mutex_unlock(&p->thread_lock);
		pthread_cond_signal(&p->not_empty);
        return 1;
	
}
int  thread_poll_net_init(void)
{
     struct sockaddr_in serveaddr;
	 serveaddr.sin_family=AF_INET;
	 serveaddr.sin_port=htons(8000);
	 inet_pton(AF_INET,"127.0.0.1",&serveaddr.sin_addr.s_addr);
	 int socketfd=socket(AF_INET,SOCK_STREAM,0);
	 bind(socketfd,(struct sockaddr*)&serveaddr,sizeof(serveaddr));
	 listen(socketfd,128);
	 servefd=socketfd;
	 return socketfd;
}
int thread_pool_epoll_init(int servefd,int max)
{
     struct epoll_event epoll_s;
	 epoll_s.events=EPOLLIN;
	 epoll_s.data.sockfd=servefd;
	 int epfd=epoll_create(max);
	 epoll_ctl(epfd,EPOLL_CTL_ADD,servefd,&epoll_s);
	 return epfd;
}
int thread_pool_epoll_listen(int epd,thread_pool_t *p)
{
      p=threadpool;
	  int flag=0;
	  epd=epfd;
	  busines_t  b;

	  struct epoll_event ready_array[1024]
      while(p->thread_shutdown)
	  {
		  int readycode=epoll_wait(epfd,&ready_array,1024,-1);
          while(readycode)
		  {
              if(ready_array[readycode].data.fd==servefd)
			  {
                 b.BUSINES_ARG=(void*)&readyarray[readycode-1].data.fd;
				 b.BUSINES_ADDR=BUSINES_ACCEPT;
                  thread_pool_add_busines(p,b);
			  }
			  else
			  {
                b.BUSINES_ARG=(void*)&readyarray[readycode-1].data.fd;
				                  b.BUSINES_ADDR=BUSINES_RESPONSE;
				thread_pool_add_busines(p,b);

			  }
           readycode--;
		  }
	  }
	  return 0;
}
int if_thread_alive(pthread_t pid)
{
   int err;
   err=pthread_kill(pid,0);
   if(err==ESRCH)
	   return false;
	   else
		   return true;
}
void *BUSINES_ACCEPT(void *arg)
{
   struct socklen_t size;
   struct sockaddr_in clientaddr;
   size=sizeof(clientaddr);
   struct epoll_event node;
   node.events=EPOLLIN;
   pthread_mutex_lock(&busines_lock);
   int clientfd=ACCEPT(servefd,(struct sockaddr*)&clientaddr,size);
   pthread_mutex_unlock(&busines_lock);
   node.data.fd=clientfd;
   epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&node);
   
 

   return NULL;
   
}
void *BUSINES_RESPONSE(void *arg)
{
	int clientfd=*(int *)arg;
    char buf[1024];
	bzero(buf,sizeof(buf));
	struct sockaddr_in clientaddr;
    int readysize=-1;
	readysize=RECV(clientfd,buffer,sizeof(buffer),0);
	if(readysize>0)
    {
        // while(readysize>0)任务处理
	}
	else if(readysize==0)
	{
         
		 epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,NULL);
		 close(clientfd);
	}

    return NULL;
}
//弄一个管理者线程 先把busy和活着的线程变量取出来 防止业务时间过长影响正常操作 取出来后直接判断是否活着的百分之七十什么的 然后如果是busy的比较少 设置线程池里的exitcode来缩减当然 也要保证这个当前所有活着的线程减去exitcode不能小于等于0 然后开始再条件变量后边加上这一条件，并且退出，而若是busy的太多，这说明线程池可能不太够用，所以要扩容，根据add来缩减 同时也要保证活着的线程加上扩容数量小于最大数 然后开始在线程数组里边开始寻找没有活着的线程或者是-1的线程，将线程创建出来，同时保证下标不可以超过max，用ifalive开始判断是否活着，然后add<增加数的时候增加，每隔多少秒来一次。sleep
