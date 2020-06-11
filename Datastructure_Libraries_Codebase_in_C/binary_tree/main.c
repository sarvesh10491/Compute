//################################################################################################
//
// Program     : Binary Tree library implementation
// Source file : main.c
// Author      : Sarvesh Patil
//
//################################################################################################

#include <stdio.h>
#include <stdlib.h>
#include "b_tree_lib.h"


// User defined node data structure & print function for that data
//=================================================================
void myprint(double arg)
{   
    printf(" %d ->", (int)arg );
}
//=================================================================

//++++++
// Main
//++++++
int main()
{
	//User defined variables
	int depth;

	binarytree *btree1=createTree();
	printf("\n");


	insertNodeBFS(btree1, 20);
	insertNodeBFS(btree1, 10);
	insertNodeBFS(btree1, 30);
	insertNodeBFS(btree1, 15);
	insertNodeBFS(btree1, 25);
	insertNodeBFS(btree1, 35);
	insertNodeBFS(btree1, 5);
	insertNodeBFS(btree1, 12);
	insertNodeBFS(btree1, 40);



	printf("No. of nodes in tree : %d\n", nodeCount(btree1));
	printf("\n");



	// depth = nodeSearchBST(btree1, 15, myprint);
	// if(depth <= -1)
	// 	printf("Node %d not present in this Binary Tree.\n", 15);
	// else
	// 	printf("Node %d present in tree at %d level & traced with above path : \n", 15, depth);
	// printf("\n");

	// depth = nodeSearchBST(btree1, 40, myprint);
	// if(depth <= -1)
	// 	printf("Node %d not present in this Binary Tree.\n", 40);
	// else
	// 	printf("Node %d present in tree at %d level & traced with above path : \n", 40, depth);
	// printf("\n");

	// depth = nodeSearchBST(btree1, 50, myprint);
	// if(depth <= -1)
	// 	printf("Node %d not present in this Binary Tree.\n", 50);
	// else
	// 	printf("Node %d present in tree at %d level & traced with above path : \n", 50, depth);
	// printf("\n");



	printf("Inorder Traversing :");
	printInorder(btree1, myprint);
	printf("\n");

	printf("Preorder Traversing :");
	printPreorder(btree1, myprint);
	printf("\n");

	printf("Postorder Traversing :");
	printPostorder(btree1, myprint);
	printf("\n");



	destroyTree(btree1);
	printf("\n");

	return 0;
}