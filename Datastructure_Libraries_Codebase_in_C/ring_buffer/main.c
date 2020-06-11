//################################################################################################
//
// Program     : Ring buffer library implementation
// Source file : main.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer_lib.h"

// User defined node data structure & print function for that data
//=================================================================
struct mynodedata
{
	int var1;
	int var2;
};

void mybuffprint(void *arg)		// Prints complete buffer
{
	struct mynodedata *nodedata = (struct mynodedata *)arg;
    if (nodedata == NULL) 
    	return;
    
    printf(" %2d %2d ->", nodedata->var1, nodedata->var2 );
}

void mynodeprint(void *arg)		// Prints particular node that has been pushed or popped
{
	struct mynodedata *nodedata = (struct mynodedata *)arg;
    if (nodedata == NULL) 
    	return;
    
    printf(" %2d %2d \n", nodedata->var1, nodedata->var2 );
}
//=================================================================

//++++++
// Main
//++++++
int main()
{
	int buff_nodes;	// Sets number of nodes within Ring Buffer

	//User defined variables
	buff_nodes=10;
	ringbuffer buff1;
	struct mynodedata *ndptr;


	// Buffer created
	printf("\n");
	createBuff(&buff1, buff_nodes);
	printf("\n");

	// Pushed some nodes
	for(int i=0; i<12; i++)
	{
		ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
		ndptr->var1=11+10*i;
		ndptr->var2=12+10*i;

		push(&buff1, ndptr);
		printf("Pushing node ");
		mynodeprint(ndptr);
		printf("\n");
	}

	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Popped in FIFO queue order
	ndptr=(struct mynodedata *)pop_queue(&buff1);
	printf("Queue popped node ");
	mynodeprint(ndptr);
	printf("\n");

	printBuff(&buff1, mybuffprint);
	printf("\n");

	ndptr=(struct mynodedata *)pop_queue(&buff1);
	printf("Queue popped node ");
	mynodeprint(ndptr);
	printf("\n");


	ndptr=(struct mynodedata *)pop_queue(&buff1);
	printf("Queue popped node ");
	mynodeprint(ndptr);
	printf("\n");

	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Pushed more nodes
	for(int i=0; i<5; i++)
	{
		ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
		ndptr->var1=15+10*i;
		ndptr->var2=16+10*i;

		push(&buff1, ndptr);
		printf("Pushing node ");
		mynodeprint(ndptr);
		printf("\n");
	}

	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Popped in LIFO queue order
	ndptr=(struct mynodedata *)pop_stack(&buff1);
	printf("Stack popped node ");
	mynodeprint(ndptr);
	printf("\n");

	ndptr=(struct mynodedata *)pop_stack(&buff1);
	printf("Stack popped node ");
	mynodeprint(ndptr);
	printf("\n");

	printf("\n");
	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Flushed buffer nodes
	printf("\n");
	flushBuff(&buff1);
	printf("\n");

	printf("\n");
	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Pushed more nodes
	for(int i=0; i<2; i++)
	{
		ndptr=(struct mynodedata *)malloc(sizeof(struct mynodedata));
		ndptr->var1=12+10*i;
		ndptr->var2=13+10*i;

		push(&buff1, ndptr);
		printf("Pushing node ");
		mynodeprint(ndptr);
		printf("\n");
	}

	printBuff(&buff1, mybuffprint);
	printf("\n");


	// Destroyed buffer
	// printf("\n");
	// destroyBuff(&buff1);
	// printf("\n");

	return 0;
}