//################################################################################################
//
// Program     : Stack library implementation
// Source file : stack_lib.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include "stack_lib.h"

// Stack functions
//+++++++++++++++++++++++
void createStack(stack *new_stack, int max_stack_size)
{
    new_stack->max_stack_size = max_stack_size;
    new_stack->cur_stack_size = 0;
    new_stack->start = 0;
    new_stack->count = 0;
    new_stack->node = malloc(sizeof(new_stack->node)*max_stack_size);
    new_stack->nodesize=(int **)malloc(max_stack_size * sizeof(int *));

    printf("Stack created.\n");
}


void stack_utilization(stack *new_stack)
{
    float util=(((float)(new_stack->cur_stack_size))/((float)(new_stack->max_stack_size)))*100.0;
    printf("%d bytes out of %d bytes used. ", new_stack->cur_stack_size, new_stack->max_stack_size);
    printf("Current stack utilization : %.2f% \n", util);
}


int is_stack_empty(stack *new_stack)
{
    if (new_stack->cur_stack_size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int is_stack_accepting(stack *new_stack, long unsigned int new_data_size)
{
    if ((new_stack->cur_stack_size + (int)new_data_size) <= new_stack->max_stack_size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void push(stack *new_stack, void *data, long unsigned int new_data_size)
{
    if (!(is_stack_accepting(new_stack,new_data_size)))
    {
        printf("Stack Overflow due to new data.\n");
    }
    else
    {
        int tracker = new_stack->start + new_stack->count++;
        new_stack->cur_stack_size += new_data_size;
        new_stack->node[tracker] = data;
        *(new_stack->nodesize+tracker)=(int *)malloc(sizeof(int));
        *(*(new_stack->nodesize+tracker))=new_data_size;
    }
}


void *pop(stack *new_stack)
{
    if (is_stack_empty(new_stack))
    {
        printf("Stack Empty\n");
        return 0;
    }
    else
    {
        void *node;
        int tracker = new_stack->start + new_stack->count - 1;
        new_stack->count--;
        new_stack->cur_stack_size-=*(new_stack->nodesize[tracker]);

        return new_stack->node[tracker];
    }
}