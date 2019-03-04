#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>


struct Param
{
	int fc;
	char ip[16];
};
struct Param param[10];


void *func(void *p)
{
	struct Param* r=p;
	while(1)
	{
		char msg[1000];
		int n=read(r->fc,msg,sizeof(msg)-1);
		msg[n]='\0';
		if(msg[0]=='q')
			break;
		if(n <= 0)
			break;
		for(int i=0;i<10;i++)
		{
			if(param[i].fc!=0&&param[i].fc!=r->fc)
			{
				write(param[i].fc,param[i].ip,sizeof(param[i].ip));
				write(param[i].fc,":",1);
				write(param[i].fc,msg,n);
			}
		}
		printf("%s : %s\n",r->ip,msg);
		memset(msg,0,n);
	}
	close(r->fc);
	r->fc=0xff;
	printf("%s:quit\n",r->ip);
}


int main(void)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	memset(param,0,sizeof(param));
	if(fd < 0)
	{
		perror("socket");
		exit(-1);
	}

	int val=1;
	int ret=setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,(void *)&val,sizeof(int));
	if	(ret < 0)
	{
		perror("opt");
		exit(-1);
	}
	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr=htons(INADDR_ANY);
	si.sin_port=htons(8890);

	if(bind(fd,(struct sockaddr*)&si,sizeof(si)) < 0)
	{
		perror("bind");
		close(fd);
		exit(0);
	}

	listen(fd,10);
	while(1)
	{
		struct sockaddr_in c;
		socklen_t len=sizeof(c);

		int fc = accept(fd,(struct sockaddr *)&c,&len);
		if(fc<0)
		{
			perror("accept");
		}
		else
		{
			char ip[16];
			char msg[1000];
			pthread_t pid;
			for(int i=0;i<10;i++)
			{
				if(param[i].fc==0)
				{
					inet_ntop(AF_INET,&c.sin_addr,ip,sizeof(ip));
					printf("%s online\n",ip);
					sprintf(msg,"Your IP:%s,fc:%dwelcom to server\n",ip,fc);
					write(fc,msg,strlen(msg));
					param[i].fc = fc;
					strcpy(param[i].ip,ip);
					pthread_create(&pid,NULL,func,param+i);
					break;
				}
			}
/*
			struct Param* p=malloc(sizeof(struct Param));
			p->fc = fc;
			strcpy(p->ip,ip);
			pthread_create(&pid,NULL,func,p);
*/
		}
	}

	return 0;



}
