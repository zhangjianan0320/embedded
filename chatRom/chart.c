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

void broadcast(int c,void *msg,int n)
{
	write(STDOUT_FILENO,msg,n);
	pthread_mutex_lock(&m);
	for(int i=0;i<MAX;i++)
	{
		if(cs[i].s!=0&&cs[i].s!=c)
			write(cs[i].s,msg,n);
	}
	pthread_mutex_unlock(&m);
}

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

	char *info = msg+iplen;
	
	printf("func\n");

	for(;;)
	{
		int len = read(c,info,sizeof(msg)-iplen);
		if(len<=0)
			break;
		if(info[0]=='q'&&info[1])
		{
			break;
		}
		else
		{
			broadcast(c,msg,len+iplen);
		}
	}
	pthread_mutex_lock(&m);
	q->s=0;
	pthread_mutex_unlock(&m);
	close(c);
	n=sprintf(msg,"%s quit!\n",ip);
	broadcast(0,msg,n);
}

int main(int argc,char **argv)
{
	int s = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in si;
	si.sin_family=AF_INET;
	si.sin_addr.s_addr=INADDR_ANY;
	si.sin_port=htons(8891);
	if(bind(s,(sa)&si,sizeof(si))<0)
	{
		perror("bind");
		exit(0);
	}

	listen(s,10);

	for(;;)
	{

		socklen_t len=sizeof(si);
		printf("accepting\n");
		int c=accept(s,(sa)&si,&len);
		printf("accept ok\n");
		if(c<0)
		{
			printf("accept 0\n");
			continue;
		}
		
		{
			int i;
			pthread_mutex_lock(&m);
			for(i=0;i<MAX;i++)
			{
				if(i==MAX)
				{
					printf("full\n");
					write(c,"full\n",5);
					close(c);
				}
				else
				{
					if(cs[i].s==0)
						continue;
					cs[i].s=c;
					inet_ntop(AF_INET,&si.sin_addr,cs[i].ip,16);
					pthread_t id;
					if(pthread_create(&id,NULL,func,&cs[i]) <= 0)
					{
						perror("pthread");
					}
				}
			}
			pthread_mutex_unlock(&m);
		}

	}
}
