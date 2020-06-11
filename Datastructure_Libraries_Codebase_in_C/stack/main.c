//################################################################################################
//
// Program     : Stack library implementation
// Source file : main.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_lib.h"

#define STACK_SIZE 1024

// User defined node data structure & print function for that data
//=================================================================
struct mynodedata1
{
	int var1;
	int var2;
};

struct mynodedata2
{
	double var3;
	int var4;
};

struct mynodedata3
{
	char *str1;
};


//=================================================================

//++++++
// Main
//++++++
int main()
{
	//User defined variables
	stack stack1;

	struct mynodedata1 *ndptr1;
	struct mynodedata2 *ndptr2;
	struct mynodedata3 *ndptr3;


	// Creating stack

	createStack(&stack1, STACK_SIZE);

	printf("\n");
	// Pushing data

	ndptr1=(struct mynodedata1 *)malloc(sizeof(struct mynodedata1));
	ndptr1->var1=11;
	ndptr1->var2=12;
	push(&stack1, ndptr1, sizeof(*ndptr1));
	printf("Pushed data1 on stack\n");

	stack_utilization(&stack1);


	ndptr2=(struct mynodedata2 *)malloc(sizeof(struct mynodedata2));
	ndptr2->var3=21.5;
	ndptr2->var4=22;
	push(&stack1, ndptr2, sizeof(*ndptr2));
	printf("Pushed data2 on stack\n");

	stack_utilization(&stack1);

	ndptr3=(struct mynodedata3 *)malloc(sizeof(struct mynodedata3));
	ndptr3->str1="Hello World";
	push(&stack1, ndptr3, sizeof(*ndptr3));
	printf("Pushed data3 on stack\n");

	stack_utilization(&stack1);

	int i1=100;
	push(&stack1, &i1, sizeof(i1));
	printf("Pushed data4 on stack\n");

	stack_utilization(&stack1);

	char c1='A';
	push(&stack1, &c1, sizeof(c1));
	printf("Pushed data5 on stack\n");

	stack_utilization(&stack1);

	printf("\n");
	// Popping data

	char *c1p=pop(&stack1);
	printf("Popped data5 from stack\n");
	printf("Data5 is : %c\n", *c1p);

	stack_utilization(&stack1);

	int *i1p=pop(&stack1);
	printf("Popped data4 from stack\n");
	printf("Data4 is : %d\n", *i1p);

	stack_utilization(&stack1);

	return 0;
}