//################################################################################################
//
// Program     : Ring buffer library implementation
// Source file : ring_buffer_lib.c
// Author      : Sarvesh Patil
//
//################################################################################################


#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer_lib.h"	

// Ring buffer functions
//+++++++++++++++++++++++
void createBuff(ringbuffer *r_buffer, int buff_size)
{
	r_buffer->buff_size = buff_size;
	r_buffer->start = 0;
	r_buffer->count = 0;
	r_buffer->node = malloc(sizeof(r_buffer->node)*buff_size);

	printf("Buffer created.\n");
}


void flushBuff(ringbuffer *r_buffer)
{
	void *node;
	while(r_buffer->count != 0)
	{
		node = pop_stack(r_buffer);
	}

	if(is_buffer_empty)
		printf("Buffer flushed.\n");
}


// void destroyBuff(ringbuffer *r_buffer)
// {
// 	free(r_buffer);

// 	printf("Buffer destroyed.\n");
// }


void printBuff(ringbuffer *r_buffer, void (*print)(void *))
{
	int i=0;
	int tracker=r_buffer->start;
	
    while (i < r_buffer->count) 
    {
        print(r_buffer->node[tracker]);
        printf(" ");
        tracker++;
        if (tracker >= r_buffer->buff_size) 
		{
			tracker = tracker - r_buffer->buff_size;
		}
        i++;
    }
    printf("\n");
}


int is_buffer_empty(ringbuffer *r_buffer) 
{
	if (r_buffer->count == 0) 
	{ 
		return 1;
	} 
	else 
	{
		return 0;
	}
}


int is_buffer_full(ringbuffer *r_buffer) 
{
	if (r_buffer->count == r_buffer->buff_size) 
	{ 
		return 1;
	} 
	else 
	{
		return 0;
	}
}


void push(ringbuffer *r_buffer, void *data) 
{
	if (is_buffer_full(r_buffer)) 
	{
		printf("Buffer Overflow\n");
	} 
	else 
	{
		int tracker = r_buffer->start + r_buffer->count++;
		if (tracker >= r_buffer->buff_size) 
		{
			tracker = tracker - r_buffer->buff_size;
		}
		r_buffer->node[tracker] = data;
	}
}


void *pop_queue(ringbuffer *r_buffer) 
{
	if (is_buffer_empty(r_buffer)) 
	{
		printf("Buffer Empty\n");
		return 0;
	}
	else 
	{
		void *node;
		node = r_buffer->node[r_buffer->start];
		r_buffer->start++;
		r_buffer->count--;
		
		if (r_buffer->start == r_buffer->buff_size) 
		{
			r_buffer->start = 0;
		}
		return node;
	}
}


void *pop_stack(ringbuffer *r_buffer) 
{
	if (is_buffer_empty(r_buffer)) 
	{
		printf("Buffer Empty\n");
		return 0;
	}
	else 
	{
		void *node;
		int tracker = r_buffer->start + r_buffer->count - 1;
		if (tracker >= r_buffer->buff_size) 
		{
           tracker = tracker - r_buffer->buff_size;
        }      
        r_buffer->count--;

        return r_buffer->node[tracker];
	}
}