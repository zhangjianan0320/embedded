#include "list.h"

/*
int List_Insert(Node *head,void *data)
{
	Node *node=head;
	while(node->next==NULL)
	{
		node=node->next;
	}
	Node *node_data=malloc(sizeof(Node));
	if(node==NULL)
	{
		return -1;
	}
	node->data->data=data;
	node->data->prev=node;
	node->next=node;
	
	return 0;
}
*/
//创建节点
Node* create_node(void *data)
{
	Node *node = malloc(sizeof(sizeof(Node)));
	node->data = data;
	node->next = NULL;

	return node;
}

//创建链表
ListManage* create_list(void)
{
	ListManage *list=malloc(sizeof(ListManage));
	list->head = NULL;
	list->size = 0;

	return list;
}

void destory_list(ListManage *list)
{
	while(del_head_list(list))
	;
	free(list);
}

void add_head_list(ListManage *list,void *data)
{
	Node *node = create_node(data);
	node->next = list->head;
	list->head = node;
	list->size++;
}

void add_tail_list(ListManage *list,void *data)
{
	if(!list->size)
	{
		add_head_list(list,data);
	}
	else
	{
		Node *tail = list->head;
		while(NULL != tail->next)
			tail = tail->next;
		Node *node = create_node(data);
		tail->next = node;
		list->size++;
	}
}

bool del_head_list(ListManage* list)
{
	if(0 == list->size)
		return false;
	Node *node = list->head;
	if(1 == list->size)
	{
		list->head = NULL;
	}
	else
	{
		list->head = list->head->next;
	}
	free(node);
	list->size--;

	return true;
}

bool del_tail_list(ListManage *list)
{
	if(0 == list->size)
	{
		return false;
	}
	else
	{
		Node *node = list->head;
		while(NULL != node->next->next)
		{
			node = node->next;
		}
		free(node->next);
		node->next = NULL;
	}
	list->size--;
	return true;
}

bool insert_list(ListManage *list,int index,void* data)
{
	if(index<0 || index > list->size)
	{return false;}
	if(0 == list->size)
	{
		add_head_list(list,data);
	}
	else
	{
		Node* node = create_node(data);
		Node* p = list->head;
		for(int i=0;i<index-1;i++)
		{
			p = p->next;
		}
		node->next = p->next;
		p->next = node;
		list->size ++;
	}

	return true;
}

void *access_list(ListManage *list,int index)
{
	if((index < 0) || (index >= list->size))
		return NULL;
	Node *node = list->head;
	for(int i=0;i<index;i++)
	{
		node = node->next;
	}

	return node->data;
}

bool del_index_list(ListManage* list,int index)
{
	if((index < 0) || (index >= list->size))
		return NULL;
	if(0 == index)
		del_head_list(list);
	else if(list->size-1 == index)
	{
		del_tail_list(list);
	}
	else
	{
		Node* node = list->head;
		for(int i=0;i<index-1;i++)
		{
			node = node->next;
		}
		Node* temp = node->next;
		node->next = temp->next;
		free(temp);
		list->size--;
	}
	
	return true;
}

void show(void *data)
{
	int *p = data;
	printf("%d ",*p);
}

void show_list(ListManage* list,void (*show)(void *data))
{
	for(Node *i=list->head;NULL!=i;i=i->next)
	{
		show(i->data);
	}
	printf("\n");
}

int main(void)
{
	ListManage *list = create_list();
	int arr[] = {1,2,3,4,5,6,7,8,9};

	for(int i=0;i<9;i++)
	{
		add_tail_list(list,arr+i);
		//add_head_list(list,arr+i);
		printf("size:%d\n",list->size);
	}

	show_list(list,show);

	return 0;
}

