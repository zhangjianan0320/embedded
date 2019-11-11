#ifdef __cplusplus
extern "c"
{
#endif

#ifndef _LIST_H_
#define _LIST_H_

typedef struct _Node
{
	struct _Node *prev;
	struct _Node *next;
	void *data;
}Node;

typedef struct _ListManage
{
	Node head;
}ListManage;

#endif	//_LIST_H_

#ifdef __cplusplus
}
#endif
