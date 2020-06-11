//################################################################################################
//
// Program     : Binary Tree library interface
// Source file : b_tree_lib.h
// Author      : Sarvesh Patil
//
//################################################################################################

#ifndef B_TREE_LIB_H
#define B_TREE_LIB_H


// Binary Tree Node structure
//============================
struct node
{
	double data;
	struct node *left;
	struct node *right;
};

typedef struct node *binarytree;


// Binary Tree functions definitions
//===================================

// Create new Binary Tree
binarytree *createTree();

// Destroy created Binary Tree
void destroyTree(binarytree *btree);

// Count & return number of nodes in Binary Tree
int nodeCount(binarytree *btree);

// Search particular node in Binary Search Tree
int nodeSearchBST(binarytree *btree, double data, void (*print)(double data));

// print Binary Tree nodes by traversing inorder & display data calling user-defined print function
void printInorder(binarytree *btree, void (*print)(double data));

// print Binary Tree nodes by traversing preorder & display data calling user-defined print function
void printPreorder(binarytree *btree, void (*print)(double data));

// print Binary Tree nodes by traversing postorder & display data calling user-defined print function
void printPostorder(binarytree *btree, void (*print)(double data));

// Insert new node in tree in Binary Search Tree structure
void insertNodeBST(binarytree *btree, double data);

// Insert new node in tree in Breadth First structure
void insertNodeBFS(binarytree *btree, double data);

#endif