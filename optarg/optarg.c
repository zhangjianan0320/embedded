#include<stdio.h>
#include<unistd.h>

int main(int argc,char **argv)
{
	int ch=0;
	// a:bc::  a: 表示必须有一个参数空格隔开 b表示不需要入参 如果有也会被忽略 c::表示可以跟一个入参也可以不跟，如果跟一个入参，参数必须紧跟在选项后不能以空格隔开
	while((ch = getopt(argc,argv,"a:bc::")) != -1)
	{
		switch(ch)
		{
			case 'a':
				printf("ch	   a:%c\n",	ch);
				printf("optarg a:%s\n",optarg);
				printf("optind a:%d\n",optind);
				printf("opterr a:%d\n",opterr);
				printf("optopt a:%d\n",optopt);
				printf("\n");
				break;
			case 'b':
				printf("ch	   b:%c\n",	ch);
				printf("optarg b:%s\n",optarg);
				printf("optind b:%d\n",optind);
				printf("opterr b:%d\n",opterr);
				printf("optopt b:%d\n",optopt);
				printf("\n");
				break;
			case 'c':
				printf("ch	   c:%c\n",	ch);
				printf("optarg c:%s\n",optarg);
				printf("optind c:%d\n",optind);
				printf("opterr c:%d\n",opterr);
				printf("optopt c:%d\n",optopt);
				printf("\n");
				break;
			default:
				printf("ch	   default:%c\n",	ch);
				printf("optarg default:%s\n",optarg);
				printf("optind default:%d\n",optind);
				printf("opterr default:%d\n",opterr);
				printf("optopt default:%d\n",optopt);
				printf("\n");
				break;

		}
	}

	printf("optarg\n");
	return 0;
}
