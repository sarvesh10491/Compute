//################################################################################################
//
// Program     : stack library implementation
// Source file : stack_lib.h
// Author      : Sarvesh Patil
//
//################################################################################################


// Stack structure
//=================
struct stack
{
	int max_stack_size;
	int cur_stack_size;
	int start;
	int count;
	void **node;
	int **nodesize;
};

typedef struct stack stack;


// Stack functions definitions
//===================================

// Create new stack
void createStack(stack *new_stack, int max_stack_size);

// Prints current stack utilization
void stack_utilization(stack *new_stack);

// To check if stack is all empty
int is_stack_empty(stack *new_stack);

// To check if new data can be added to stack
int is_stack_accepting(stack *new_stack, long unsigned int new_data_size);

// Push new data node into stack
void push(stack *new_stack, void *data, long unsigned int new_data_size);

// Pop data from top of stack
void *pop(stack *new_stack);
