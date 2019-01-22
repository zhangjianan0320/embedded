#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 20
typedef struct sockaddr * sa;
typedef struct {
	int s;
	char ip[16];
}client;

client cs[MAX]={0};
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *func(void *p)
{
	client* q=p;
	char ip[16];

	pthread_mutex_lock(&m);
	int c=q->s;
	strcpy(ip,q->ip);
	pthread_mutex_unlock(&m);
	char msg[1000];
	int n = sprintf(msg,"welcom chartRom %s!\n",ip);
	broadcast(0,msg,n);
	int iplen = sprintf(msg,"%s say:",ip);

	for(;;)
	{
	
	}

}

int main(int argc,char **)
{
	int s = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in si;
	si.sin_family=AF_INET;
	si.sin_addr.s_addr=INADDR_ANY;
	si.sin_port=htons(8888);
	if(bind(s,(sa)&si),sizeof(si)<0)
	{
		perror("bind");
	}

	listen(s,10);

	for(;;)
	{

		socklen_t len=sizeof(si);
		int c=accept(s,(sa)&si,&len);
		if(c<0)
		{
			continue;
		}
		else
		{
			int i;
			pthread_mutex_lock(&m);
			for(i=0;i<MAX&&(cs[i]!=0);i++)
			{
				if(i==MAX)
				{
					write(c,"full\n",5);
					close(c);
				}
				else
				{
					cs[i].s=c;
					inet_ntop(AF_INET,&si.sin_addr,cs[i],16);
					pthread_t id;
					pthread_creat(&id,NULL,func,&cs[i]);
				}
			}
			pthread_mutex_unlock(&m);
		}

	}
}
