// Trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CommonDataTypes.h"
#include <algorithm>
#include "stdlib.h"
#include <iostream>

using namespace::std;

// using class TreeNode

// returns a test tree 
// TODO: build a recursive implementation
TreeNode * Tree::BuildTree() {

	/* Constructed binary tree is
	1
	/   \
	2      3
	/  \
	4     5
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	*/

	/* 
	BST 
	        6
		4	   7
      3	  5   9  8
	*/

	TreeNode *root = new TreeNode(6);
	root->left = new TreeNode(4);
	root->right = new TreeNode(7);
	root->right->right = new TreeNode(8);
	root->right->left = new TreeNode(9);
	root->left->left = new TreeNode(3);
	root->left->right = new TreeNode(5);

	return root;
}


int Tree::TreeHeight(TreeNode *root){

	if (root == NULL)
		return 0;
	else {
		return (1 + std::max(TreeHeight(root->left), TreeHeight(root->right)));
	}
	
}

void Tree::PrintTree(const TreeNode *node, Traversal order) {

	if (node != NULL) {
		switch (order){
		case PreOrder:
			printf("Node %i \n", node->_data);
			PrintTree(node->left, order);
			PrintTree(node->right, order);
			break;
		case InOrder:
			PrintTree(node->left, order);
			printf("Node %i \n", node->_data);
			PrintTree(node->right, order);
			break;
		case PostOrder:
			PrintTree(node->left, order);
			PrintTree(node->right, order);
			printf("Node %i \n", node->_data);
			break;
		default:
			printf("Invalid order specified!");
		}
	}
}

void Tree::visitNode(TreeNode *node) {
    printf("Node %i \n", node->_data);
}

// essentially postorder traversal, visit children first, then parent
void Tree::DepthFirstTraversal(TreeNode *root) {

    if (root == NULL) {
        return;
    }

    DepthFirstTraversal(root->left);
    DepthFirstTraversal(root->right);
    visitNode(root);
}



