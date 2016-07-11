#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

TreeNode* findMaxValue(TreeNode *root) {

	if (root == nullptr)
		return nullptr;

	TreeNode *curr = root;

	while (curr->right) {
		curr = curr->right;
	}
	return curr;
}

TreeNode* findMinValue(TreeNode *root) {
	
	if (root == nullptr)
		return nullptr;

	TreeNode *curr = root;

	while (curr->left) {
		curr = curr->left;
	}
	return curr;
}

// find smallest value larger than start->data
TreeNode *findNextSuccessor(TreeNode *root, TreeNode *start) {
	
	if (start->right != nullptr)
		return findMinValue(start->right);

	// start at the root

	TreeNode *succ = nullptr;
	TreeNode *curr = root;
	int val = start->_data;

	while (curr) {

		if (curr->_data > val) {
			succ = curr;
			curr = curr->left;
		}
		else if (curr->_data < val) {
			curr = curr->right;
		}
		else
			return succ;			
	}
	return nullptr;
}

// find smallest value smaller than start->data
TreeNode *findNextPredecessor(TreeNode *root, TreeNode *start) {

	if (start->left != nullptr)
		return findMaxValue(start->left);

	// start at the root

	TreeNode *pred = nullptr;
	TreeNode *curr = root;
	int val = start->_data;

	while (curr) {

		if (curr->_data < val) {
			pred = curr;
			curr = curr->right;
		}
		else if (curr->_data > val) {
			curr = curr->left;
		}
		else
			return pred;
	}
	return nullptr;
}

// given a value val, return node, otherwise return nullptr
TreeNode * findValue(TreeNode *root, int val) {

	if (root == nullptr)
		return nullptr;

	if (root->_data == val)
		return root;
	else if (root->_data < val)
		return findValue(root->right, val);
	else
		return findValue(root->left, val);

}














