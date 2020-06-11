//################################################################################################
//
// Program     : Single Linked list library implementation
// Source file : single_linked_list_lib.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include "single_linked_list_lib.h"

// Linked List functions
//+++++++++++++++++++++++
linkedlist *createList(void *new_data)
{
	struct node *new_node;

	linkedlist *new_list;
	new_list = (linkedlist *)malloc(sizeof (linkedlist));
    *new_list = (struct node *)malloc(sizeof (struct node));

    new_node = *new_list;
    new_node->data = new_data;
    new_node->next = NULL;

    printf("Single Linked List created.\n");

    return new_list;
}


void destroyList(linkedlist *list)
{
	struct node *n = *list;
	struct node *tmpn = NULL;
	while(n!=NULL)
	{
		tmpn=n;
		n=n->next;
		free(tmpn);
	}
	free(list);

	printf("Single Linked List destroyed.\n");
}


int nodeCount(linkedlist *list)
{
	struct node *n = *list;
	int count=0;
	while(n!=NULL)
	{
		count++;
		n=n->next;
	}
	return count;
}


void printList(linkedlist *list, void (*print)(void *))
{
    struct node *n = *list;
    while (n != NULL) 
    {
        print(n->data);
        printf(" ");
        n = n->next;
    }
    printf("\n");
}


void insertHead(linkedlist *list, void *data)
{
	struct node *head;
	struct node *new_node;

	if (list == NULL || *list == NULL) 
	{
    	printf("Linked list is empty\n");
    }

    head=*list;

    // Head is empty node
    if (head->data == NULL)
        head->data = data;

    // Head is not empty hence adding new node to head
    else 
    {
        new_node = (struct node *)malloc(sizeof (struct node));
        new_node->data = data;
        new_node->next = head;
        *list = new_node;
    }
}



void insertEnd(linkedlist *list, void *data)
{
	struct node *head;
	head=*list;

	if(head == NULL)
	{
		printf("Linked List is empty.\n");
		return;
	}

	struct node *new_node=NULL;
	new_node = (struct node *)malloc(sizeof(struct node));


	struct node *n = head;
	struct node *pren = NULL;

	while(n != NULL)
	{
		pren=n;
		n=n->next;
	}
	pren->next=new_node;
	new_node->next=NULL;
	new_node->data=data;
}



void insertAfter(linkedlist *list, void *data, int afterNode)
{
	if(afterNode>nodeCount(list))
	{
		printf("Invalid node number.\nCurrently %d nodes are present in Linked List.\n", nodeCount(list));
		return;
	}

	struct node *n = *list;
	struct node *prev_node = NULL;
	
	int count=0;
	while(count<afterNode)
	{
		count++;
		prev_node=n;
		n=n->next;
	}


	if(prev_node==NULL)
	{
		printf("New Node can not be NULL.\n");
		return;
	}

	struct node *new_node=NULL;
	new_node=(struct node *)malloc(sizeof(struct node));

	new_node->next=prev_node->next;
	new_node->data=data;
	prev_node->next=new_node;
}



void deleteAt(linkedlist *list, int pos)
{
	if(*list==NULL)
	{
		printf("Linked List is empty.\n");
		return;
	}
	if(nodeCount(list)<pos)
	{
		printf("Invalid node number(%d) provided for deletion.\nCurrently %d nodes are present in Linked List.\n", pos, nodeCount(list));
		return;
	}
	struct node *n=*list;
	struct node *pren=NULL;

	if(pos==1)
	{
		pren=*list;
		*list=n->next;
		free(pren);
		return;
	}

	int count=1;
	while(count<pos)
	{
		count++;
		pren=n;
		n=n->next;
	}
	pren->next=n->next;
	free(n);
}



void rotateLeftBy(linkedlist *list, int mvnodes)
{
	if(*list==NULL)
	{
		printf("Linked List is empty.\n");
		return;
	}
	
	mvnodes=mvnodes%nodeCount(list);

	struct node *orghead=*list;
	struct node *orgtail=NULL;
	struct node *newhead=NULL;
	struct node *newtail=NULL;

	struct node *n=orghead;
	struct node *pren=NULL;
	int count=1;

	while(n != NULL)
	{
		pren=n;
		n=n->next;
		if(count==mvnodes)
		{
			newtail=pren;
			newhead=n;
		}
		count++;
	}
	orgtail=pren;

	*list=newhead;
	orgtail->next=orghead;
	newtail->next=NULL;
}



void rotateRightBy(linkedlist *list, int mvnodes)
{
	if(*list==NULL)
	{
		printf("Linked List is empty.\n");
		return;
	}
	
	mvnodes=mvnodes%nodeCount(list);

	struct node *orghead=*list;
	struct node *orgtail=NULL;
	struct node *newhead=NULL;
	struct node *newtail=NULL;

	struct node *n=orghead;
	struct node *pren=NULL;
	int count=1;

	while(n != NULL)
	{
		pren=n;
		n=n->next;
		if(count==(nodeCount(list)-mvnodes))
		{
			newtail=pren;
			newhead=n;
		}
		count++;
	}
	orgtail=pren;

	*list=newhead;
	orgtail->next=orghead;
	newtail->next=NULL;
}