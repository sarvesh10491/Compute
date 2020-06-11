//################################################################################################
//
// Program     : Double Linked list library implementation
// Source file : main.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include "double_linked_list_lib.h"


// User defined node data structure & print function for that data
//=================================================================
struct mynodedata
{
	int var1;
	int var2;
};

void myprint(void *arg)
{
	struct mynodedata *nodedata = (struct mynodedata *)arg;
    if (nodedata == NULL) 
    	return;
    
    printf(" %2d %2d <->", nodedata->var1, nodedata->var2 );
}
//=================================================================

//++++++
// Main
//++++++
int main()
{
	//User defined variables
	int afterNode;

	linkedlist *list1=createList(NULL);

	printList(list1, myprint);

	struct mynodedata *ndptr;

	
	ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
	ndptr->var1=11;
	ndptr->var2=12;
	insertHead(list1, ndptr);
	printList(list1, myprint);

	ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
	ndptr->var1=51;
	ndptr->var2=52;
	insertEnd(list1, ndptr);
	printList(list1, myprint);

	afterNode=1;
	ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
	ndptr->var1=21;
	ndptr->var2=22;
	insertAfter(list1, ndptr, afterNode);
	printList(list1, myprint);

	afterNode=2;
	ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
	ndptr->var1=31;
	ndptr->var2=32;
	insertAfter(list1, ndptr, afterNode);
	printList(list1, myprint);

	afterNode=3;
	ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
	ndptr->var1=41;
	ndptr->var2=42;
	insertAfter(list1, ndptr, afterNode);
	printList(list1, myprint);

	rotateLeftBy(list1,2);
	printList(list1, myprint);

	rotateRightBy(list1,2);
	printList(list1, myprint);

	deleteAt(list1,3);
	printList(list1, myprint);

	deleteAt(list1,1);
	printList(list1, myprint);

	deleteAt(list1,7);
	printList(list1, myprint);

	destroyList(list1);

	return 0;
}