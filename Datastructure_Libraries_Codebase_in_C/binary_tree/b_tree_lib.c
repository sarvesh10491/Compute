//################################################################################################
//
// Program     : Binary Tree library implementation
// Source file : b_tree_lib.c
// Author      : Sarvesh Patil
//
//################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "b_tree_lib.h"
#include "ring_buffer_lib.h"

int buff_nodes = 1024;

ringbuffer fifo_queue_1;

// Binary Tree functions
//+++++++++++++++++++++++
binarytree *createTree()
{
	struct node *root_node;

	binarytree *new_btree;
	new_btree = (binarytree *)malloc(sizeof (binarytree));
    *new_btree = (struct node *)malloc(sizeof (struct node));

    root_node = *new_btree;
    root_node->data = INFINITY;
    root_node->left = NULL;
    root_node->right = NULL;

    printf("\nBinary Tree created.\n");

    createBuff(&fifo_queue_1, buff_nodes);  // FIFO queue used for Binary Tree

    return new_btree;
}


void destroyTree(binarytree *btree)
{
	struct node *leaf = *btree;

    if(leaf == NULL)
    {
    	printf("Binary Tree is empty.\n");
    	return;
    }

    if(leaf->left != NULL)
    {
    	destroyTree(&(leaf->left));
    }

    if(leaf->right != NULL)
    {
    	destroyTree(&(leaf->right));
    }

    free(leaf);
}


int nodeCount(binarytree *btree)
{
	struct node *leaf = *btree;
	int count=0;

	if(leaf == NULL)
    {
    	// printf("Binary Tree is empty.\n");
    	return count;
    }

    count++;

    if(leaf->left != NULL)
    {
    	count += nodeCount(&(leaf->left));
    }

    if(leaf->right != NULL)
    {
    	count += nodeCount(&(leaf->right));
    }
	
	return count;
}


int nodeSearchBST(binarytree *btree, double data, void (*print)(double data))
{
    struct node *leaf = *btree;
    int count=1;

    if((data < leaf->data) && (leaf->left != NULL))            // Search node to left branch in tree
    {
        // printf("Going in left branch of node %lf on Binary Tree.\n", leaf->data);
        count += nodeSearchBST(&(leaf->left), data, print);
    }

    else if((data > leaf->data) && (leaf->right != NULL))      // Search node to right branch in tree
    {
        // printf("Going in right branch of node %lf on Binary Tree.\n", leaf->data);
        count += nodeSearchBST(&(leaf->right), data, print);
    }

    else if(data == leaf->data)     // Node found in tree
    {
        print(leaf->data);
        count--;
    }

    else
    {
        // printf("Node not present in this Binary Tree.\n");
        count = -INFINITY;
    }
    return count;
}


void printInorder(binarytree *btree, void (*print)(double data))
{
    struct node *leaf = *btree;

    if(leaf == NULL)
    {
    	printf("Binary Tree is empty.\n");
    	return;
    }

    if(leaf->left != NULL)
    {
    	printInorder(&(leaf->left), print);
    }

    print(leaf->data);

    if(leaf->right != NULL)
    {
    	printInorder(&(leaf->right), print);
    }
}


void printPreorder(binarytree *btree, void (*print)(double data))
{
    struct node *leaf = *btree;

    if(leaf == NULL)
    {
    	printf("Binary Tree is empty.\n");
    	return;
    }

    print(leaf->data);

    if(leaf->left != NULL)
    {
    	printPreorder(&(leaf->left), print);
    }

    if(leaf->right != NULL)
    {
    	printPreorder(&(leaf->right), print);
    }
}


void printPostorder(binarytree *btree, void (*print)(double data))
{
    struct node *leaf = *btree;

    if(leaf == NULL)
    {
    	printf("Binary Tree is empty.\n");
    	return;
    }

    if(leaf->left != NULL)
    {
    	printPostorder(&(leaf->left), print);
    }

    if(leaf->right != NULL)
    {
    	printPostorder(&(leaf->right), print);
    }

    print(leaf->data);
}


void insertNodeBST(binarytree *btree, double data)
{
    struct node *leaf = *btree;

    if (leaf->data == INFINITY)     // This is root node
    {
        // printf("Binary Tree is empty. %lf will be the root node.\n", data );
        leaf->data = data;
    }
        

    // Root node exists hence adding new node to corresponding branch
    else 
    {
        if(data <= leaf->data)  // Add node to left branch in tree
        {
            // printf("Going in left branch of node %lf on Binary Tree.\n", leaf->data);
            if(leaf->left == NULL)
            {
                struct node *new_node;
                new_node = (struct node *)malloc(sizeof (struct node));

                leaf->left = new_node;
                new_node->data = data;
                new_node->left = NULL;
                new_node->right = NULL;
                // printf("Added new node %lf.\n", data);
            }
            else
            {
                // printf("Already node %lf present on this side on branch.\n", leaf->left->data);
                insertNodeBST(&(leaf->left), data);
            }
        }

        else                    // Add node to right branch in tree
        {
            // printf("Going in right branch of node %lf on Binary Tree.\n", leaf->data);
            if(leaf->right == NULL)
            {
                struct node *new_node;
                new_node = (struct node *)malloc(sizeof (struct node));

                leaf->right = new_node;
                new_node->data = data;
                new_node->left = NULL;
                new_node->right = NULL;
                // printf("Added new node %lf.\n", data);
            }
            else
            {
                // printf("Already node %lf present on this side on branch.\n", leaf->right->data);
                insertNodeBST(&(leaf->right), data);
            }
        }
    }
}



void insertNodeBFS(binarytree *btree, double data)
{
    struct node *leaf = *btree;

    if (leaf->data == INFINITY)     // This is root node
    {
        printf("Binary Tree is empty. %lf will be the root node.\n\n", data );
        leaf->data = data;
    }
        

    // Root node exists hence adding new node to corresponding branch in BFS order
    else 
    {
        if(leaf->left == NULL)
        {
            // printf("Going in left branch of node %lf on Binary Tree.\n", leaf->data);

            struct node *new_node;
            new_node = (struct node *)malloc(sizeof (struct node));

            leaf->left = new_node;
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            printf("Added new node %lf.\n", data);

            flushBuff(&fifo_queue_1);
            printf("\n");
        }

        else if(leaf->right == NULL)
        {
            // printf("Going in right branch of node %lf on Binary Tree.\n", leaf->data);

            struct node *new_node;
            new_node = (struct node *)malloc(sizeof (struct node));

            leaf->right = new_node;
            new_node->data = data;
            new_node->left = NULL;
            new_node->right = NULL;
            printf("Added new node %lf.\n", data);

            flushBuff(&fifo_queue_1);
            printf("\n");
        }

        // Pushing both left & right node into FIFO queue
        else
        {
            // printf("Already nodes %lf & %lf present on left & right sides of node.\n", leaf->left->data, leaf->right->data);
            push(&fifo_queue_1, leaf->left);
            push(&fifo_queue_1, leaf->right);
            // printf("Pushed both above nodes on stack.\n");

            // Popping first node from FIFO queue and checking open slot in node's left & right branches
            leaf=(struct node *)pop_queue(&fifo_queue_1);
            // printf("Popped node %lf \n", leaf->data);
            insertNodeBFS(&leaf, data);
        }
    }
}