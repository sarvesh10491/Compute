//################################################################################################
//
// Program     : Single Linked list library implementation
// Source file : single_linked_list_lib.h
// Author      : Sarvesh Patil
//
//################################################################################################


// Linked List Node structure
//============================
struct node
{
	void *data;
	struct node *next;
};

typedef struct node *linkedlist;


// Linked List functions definitions
//===================================

// Create new single linked list
linkedlist *createList(void *data);

// Destroy new single linked list
void destroyList(linkedlist *list);

// Count & return number of nodes in list
int nodeCount(linkedlist *list);

// print linked list nodes data calling user-defined print function
void printList(linkedlist *list, void (*print)(void *data));

// Insert new node at head of the list
void insertHead(linkedlist *list, void *data);

// Insert new node at end of the list
void insertEnd(linkedlist *list, void *data);

// Insert new node after specified node in the list
void insertAfter(linkedlist *list, void *data, int afterNode);

// Delete specified node in the list
void deleteAt(linkedlist *list, int pos);

// Rotate list to left by specified number of nodes
void rotateLeftBy(linkedlist *list, int mvnodes);

// Rotate list to right by specified number of nodes
void rotateRightBy(linkedlist *list, int mvnodes);