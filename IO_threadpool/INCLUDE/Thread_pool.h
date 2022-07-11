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
