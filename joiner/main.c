/*************************************************************************
    > File Name: main.c
    > Author: zjn
    > Mail:zjn 
    > Created Time: 2019年11月27日 星期三 14时04分12秒
 ************************************************************************/

#include<stdio.h>
// #操作符用于预处理，将宏参数转化为字符串，只有在宏定义中使用
#define STRING(x) #x

//打印函数名称
#define CALL(f,p)	(printf("call function %s\n",#f),f(p))

int seqare(int n)
{
	return n * n;
}

int func(int n)
{
	return n;
}
// ##用于处理预处理阶段，将粘连两个标识符，只有宏定义中使用
#define NAME(n)	name##n

#define STRUCT(type) typedef struct _tag_##type type;\
						struct _tag_##type

STRUCT(Student)
{
	char *name;
	int id;
};

#define FUNC(id) FUNC_##id

int FUNC(1)(int a)
{
	printf("FUNC1\n");
	return 1;
}

int FUNC(2)(int a)
{
	printf("FUNC2\n");
	return 1;
}

int FUNC(3)(int a)
{
	printf("FUNC3\n");
	return 1;
}

int main()
{
	int result = 0;
	int NAME(1);
	int NAME(2);
	//#运算符使用方法
	printf("%s\n",STRING(Hellow World));
	printf("%s\n",STRING(100));
	printf("%s\n",STRING(while));

	//打印任意函数名的方法
	result = CALL(seqare,4);
	printf("result = %d\n",result);
	result = CALL(func,10);
	printf("result = %d\n",result);

	//##运算符使用方法
	NAME(1) = 1;
	NAME(2) = 2;

	printf("%d\n",NAME(1));
	printf("%d\n",NAME(2));

	//##定义结构体特殊用法
	
	Student s1,s2;
	s1.name = "Lilei";
	s1.id = 0;
	s2.name = "HanMeimei";
	s2.id = 1;

	printf("s1.name = %s  s1.id = %d\n",s1.name,s1.id);
	printf("s2.name = %s  s2.id = %d\n",s2.name,s2.id);

	FUNC(1)(1);
	FUNC(2)(2);
	FUNC(3)(3);

	return 0;
}
