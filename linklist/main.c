#include <stdio.h>
#include "list.h"

void sum_cb(void *ctx,void *data)
{
	long long  *sum = ctx;
	
	*sum += (long long)data;
}

void max_cb(void *ctx,void *data)
{
	int *max = ctx;

	if(*max < (long long)data)
		*max = (long long)data;
}

void show_int(void *ctx,void *data)
{
	printf("%lld ",(long long)data);
}

void show_float(void *ctx,void *data)
{
//	printf("%f\n",(float)data);
	float a=1.1;
	printf("%f\n",a);
}

int main(int argc,const char *argv[])
{
	ListManage *list=create_list();

	long long arr[] = {0,1,4,6,1,4,6,7,4,9,5,8,2,0};

	for(int i=0;i<10;i++)
	{
		add_tail_list(list,(void*)arr[i]);
	}

	deal_list(list,show_int,NULL);

	long long sum;

	deal_list(list,sum_cb,&sum);
	printf("sum=%lld\n",sum);

	int max=0;
	deal_list(list,max_cb,&max);
	printf("max=%d\n",max);

/*
	ListManage* f_list=create_list();

	float f_arr[]={1.1,2.2,3.3,4.4,5.5,6.6,7.7};

	for(int i=0;i<7;i++)
	{
		add_tail_list(f_list,(void *)f_arr[i]);
	}
	show_list(f_list,show_float);
*/

	return 0;

}
