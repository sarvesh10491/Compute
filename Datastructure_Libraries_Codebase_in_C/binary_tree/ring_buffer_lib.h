//################################################################################################
//
// Program     : Ring buffer library interface
// Source file : ring_buffer_lib.h
// Author      : Sarvesh Patil
//
//################################################################################################


// Linked List Node structure
//============================
struct ring_buff
{
	int buff_size;	
    int start;
    int count;
    void **node;
};

typedef struct ring_buff ringbuffer;


// Linked List functions definitions
//===================================

// Create new Ring buffer
void createBuff(ringbuffer *r_buffer, int buff_size);

// Flush Ring buffer nodes
void flushBuff(ringbuffer *r_buffer);

// Destroy Ring buffer nodes
void destroyBuff(ringbuffer *r_buffer);

// print Ring buffer nodes data calling user-defined print function
void printBuff(ringbuffer *r_buffer, void (*print)(void *data));

// To check if buffer is empty
int is_buffer_empty(ringbuffer *r_buffer);

// To check if buffer is full
int is_buffer_full(ringbuffer *r_buffer);

// Push new data node into ring buffer
void push(ringbuffer *r_buffer, void *data);

// Queue pop (FIFO implementation)
void *pop_queue(ringbuffer *r_buffer);

// Stack pop (LIFO implementation)
void *pop_stack(ringbuffer *r_buffer);