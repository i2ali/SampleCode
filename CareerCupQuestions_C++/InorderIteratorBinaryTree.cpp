
#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

// Implement a class that implements an InOrder Iterator on a Binary Tree
// http://educative.io/pageviewer/5642554087309312/6561696416006144

//Description
// We are given root node of a binary tree and we have to write an iterator that takes in this root and iterates through the nodes of binary tree 
// in an inorder way.The expectation is to write two critical methods of any iterator : hasNext() and getNext().

// Runtime: O(n), Memory: O(h), where h is height


// iterator usage patterns:
// for (auto i = set.begin; i != end; i++) {}

// InOrderIterator *myiterator = new InOrderIterator();
// cout << (myiterator->getNext).
/*
while (myiterator->hasNext)
	TreeNode *tn = myiterator->getNext;
	cout << tn->data << end;
*/

// http://www.careercup.com/question?id=5664061589028864


class InOrderIterator {

private:
	TreeNode *_root;       // cache the current node in the tree
	TreeNode *currentnode; // stores the current node in the iteration

public:
	//ctor
	InOrderIterator(TreeNode *tn) {
		_root = nullptr;
		if (tn != nullptr)
			_root = tn;
	}

	// check if there is another item in the tree
	bool hasNext() {
		

	}

	// continue inorder traversal
	TreeNode * getNext() {
		// visit left
		// visit this
		// visit right
/*		if (this->currentnode == nullptr) {
			return nullptr;
		}
		currentnode->left;
		getNext(currentnode->left);
		

		getNext(currentnode);
		getNext(currentnode->right);
        */
	}
    

};

