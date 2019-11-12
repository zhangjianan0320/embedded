#ifdef __cplusplus
extern "c"
{
#endif

#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node
{
//	struct _Node *prev;
	struct _Node *next;
	void *data;
}Node;

typedef struct _ListManage
{
	Node *head;
	unsigned int size;
}ListManage;


Node* create_node(void *data);
ListManage* create_list(void);
void destory_list(ListManage *list);
void add_head_list(ListManage *list,void *data);
void add_tail_list(ListManage *list,void *data);
bool del_head_list(ListManage* list);
bool del_tail_list(ListManage *list);
bool insert_list(ListManage *list,int index,void* data);
void *access_list(ListManage *list,int index);
bool del_index_list(ListManage* list,int index);
void show(void *data);
void show_list(ListManage* list,void (*show)(void *data));
#endif	//_LIST_H_

#ifdef __cplusplus
}
#endif
