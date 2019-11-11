#include "list.h"
#include "stdio.h"

Node *List_Init(void *data)
{
	Node *node=malloc(Node);
	
	return Node;
}

int List_Insert(Node *head,void *data)
{
	Node *node=head;
	while(node->next==NULL)
	{
		node=node->next;
	}
	Node *node_data=malloc(Node);
	if(node==NULL)
	{
		return -1;
	}
	node-data->data=data;
	node_data->prev=node;
	node->next=node;
	
	return 0;
}

int List_Delete(Node *)

