// PlainCode.cpp : Defines the entry point for the console application.
//

#pragma once

using namespace::std;

#include "stdafx.h"
#include <string>
#include <math.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <assert.h>
#include <time.h>
#include <queue>

/*
class TreeNode {
public:
	int _data;
	TreeNode *left;
	TreeNode *right;
	bool visited;
	TreeNode() { left = NULL; right = NULL; visited = false; }
	TreeNode(int data) : TreeNode() { _data = data; }
	TreeNode* getLeft() { return this->left; }
	TreeNode* getRight() { return this->right; }
};
*/

class TreeNode {
public:
	TreeNode *left;
	TreeNode *right;
	int _data;
	TreeNode(int data) {
		_data = data;
		left = nullptr;
		right = nullptr;
	}
};


// Determine if there exists a sum in a binary tree
bool CalcSum(TreeNode *root, int sum) {
	if (root == nullptr)
		return true;

	int currsum = sum - root->_data;

	if (currsum < 0) // small optimization
		return false;

	//check if leaf node 
	if ((root->right == nullptr) && (root->left == nullptr))
		return (currsum == 0);

	return (CalcSum(root->left, currsum) || CalcSum(root->right, currsum));
}


int heightbinarytree(TreeNode *root) {
	if (root == nullptr)
		return 0;
	return 1 + max(heightbinarytree(root->left), heightbinarytree(root->right));
}

int max(int a, int b) {
	return (a >= b) ? a : b;
}

// determine if tree is height-balanced, O(n^2)
bool heightbalancedold(TreeNode *root) {
	if (root == nullptr)
		return true;
	if ((abs(heightbinarytree(root->left) - heightbinarytree(root->right)) <= 1) && heightbalancedold(root->left) && heightbalancedold(root->right))
		return true;
	return false;
}


bool heightbalancedrec(TreeNode *root, int *height) {
	if (root == nullptr) {
		*height = 0;
		return true;
	}
	int lh = 0;
	int rh = 0;
	bool l = false;
	bool r = false;
	l = heightbalancedrec(root->left, &lh);
	r = heightbalancedrec(root->right, &rh);
	*height = max(lh, rh) + 1;
	if (abs(lh - rh) >= 2)
		return false;
	return (l && r);
}

// determine if tree is height-balanced, O(n)
bool heightbalanced(TreeNode *root) {
	int height = 0;
	return heightbalancedrec(root, &height);
}

// diameter of binary tree O(n^2)
int diameterbinarytreeold(TreeNode *root) {
	if (root == nullptr)
		return 0;
	int lh = heightbinarytree(root->left);
	int rh = heightbinarytree(root->right);
	int rd = diameterbinarytreeold(root->right);
	int ld = diameterbinarytreeold(root->left);
	return max(lh + rh + 1, max(rd, ld));
}
int diameterbinarytreerec(TreeNode *root, int *height) {
	if (root == nullptr) {
		*height = 0;
		return 0;
	}
	int lh = 0;
	int rh = 0;
	int rd = diameterbinarytreerec(root->right, &rh);
	int ld = diameterbinarytreerec(root->left, &lh);
	*height = max(lh, rh) + 1;
	return max(lh + rh + 1, max(rd, ld));
}

// diameter of binary tree O(n)
int diameterbinarytree(TreeNode *root) {
	int height = 0;
	return diameterbinarytreerec(root, &height);
}


/*
Design a data structure that supports insert, delete, search and getRandom in constant time
Design a data structure that supports following operations in ?(1) time.
insert(x): Inserts an item x to the data structure if not already present.
remove(x): Removes an item x from the data structure if present.
search(x): Searches an item x in the data structure.
getRandom(): Returns a random element from current set of elements

Can use hashmap unordered_map<>
arraylist
*/

/*
class myDS {

private:

	std::unordered_map<int, int> hash;		// key = values in array, value = indexes into array
	vector<int> list; // values

	bool checkifexists(int item) {
		std::unordered_map<int, int>::const_iterator got = hash.find(item);
		return (got != hash.end());
	}

public:

	myDS() {};
	bool insert(int item) {
		if (checkifexists(item))
			return false;

		// store the value and index into array
		int size = list.size();
		hash.insert(item, size);
		list.push_back(item);
		return true;
	}

	bool remove(int item) {
		if (checkifexists(item))
			return false;

		// first get index out of value
		unordered_map<int, int>::const_iterator got = hash.find(item);
		assert(got != hash.end());

		int index = got->second;

		// erase item	
		hash.erase(item);

		//update array as well
		int size = list.size();
		int last = list[size - 1];

//		list.swap(index, size - 1);
		list.erase(list.end());

//		hash.at(last, index);

		return true;
	}

	bool search(int item) {
		std::unordered_map<int, int>::const_iterator got = hash.find(item);
		if (got != hash.end()) return true; 
		return false;
	}

	int getRandom() {
		return 0;
		srand(time(NULL));
		int irand = rand() % list.size() + 1;
		assert((irand > 0) && (irand <list.size() + 1));
		return list[irand];
	}

};

*/

class LinkedListNode {
public:
	int _val;
	LinkedListNode *next;
	LinkedListNode(int val) {
		_val = val;
		next = nullptr;
	}
	LinkedListNode() {
		_val = 0;
		next = nullptr;
	}
};


// reverse a singly linked list
void reverselist(LinkedListNode *head) {

	// empty TreeNode and one TreeNode case
	if (head == nullptr || head->next == nullptr)
		return;

	LinkedListNode *B = head;
	LinkedListNode *A = nullptr, *C = nullptr;

	while (B != nullptr) {
		C = B->next;
		B->next = A;
		A = B;
		B = C;
	}
	return;

}

/*
for (int i = ScrollDelay::Perfect; i <ScrollDelay::NumBuckets; i++) {
	_buckets[i]._bucketHitCount = 0;
	_buckets[i]._sumDelayInMilliseconds = 0;
}

memset(_buckets, 0, sizeof(_buckets[0] * ARRAYSIZE(_buckets));
*/

void reverseoneword(int b, int e, string &s) {

	if (s.empty())
		return;

	int begin = b;
	int end = e;
	char temp;

	while (begin <= end) {
		temp = s[begin];
		s[begin] = s[end];
		s[end] = temp;
		end--;
		begin++;
	}
	return;
}

void reverseWords(string &s) {

	if (s.empty())
		return;

	int len = s.length();

	int beginindex = 0;
	int endindex = 0;

	while (endindex < len) {

		// skip initial ws
		while (s[endindex] == ' ') {
			endindex++;
		}
		if (s[endindex] == ' ')
			beginindex = endindex - 1;
		else
			beginindex = endindex;

		// find endindex
		while ((s[endindex] != ' ') && (endindex < len)) {
			endindex++;
		}
		reverseoneword(beginindex, endindex - 1, s);
	}

	// once all words are reversed, reverse the entire word
	reverseoneword(0, s.length() - 1, s);

	return;
}


// implement a queue using a circular array
// circular ring buffer (queue)

class Queue {
private:
	LinkedListNode *head;
	LinkedListNode *tail;
	int _maxsize;
	int _currsize;

public:
	Queue(int maxsize) {
		_maxsize = maxsize;
		_currsize = 0;

		head = nullptr;
		tail = nullptr;

		/*		Node *curr = head;

		for (int i = 0; i < size; i++) {
		curr->next = new Node();
		curr = curr->next;
		}

		// make this circular
		curr->next = head;
		tail = curr;
		*/
	}

	// remove element from the end of the list
	void dequeue() {
		if (head == nullptr)
			return;
		if (_currsize == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}

		LinkedListNode *curr = head;
		while (curr->next != tail) {
			curr = curr->next;
		}

		delete curr->next;
		curr->next = head;
		tail = curr;
		_currsize--;

		return;
	}

	// add element to beginning of list
	bool enqueue(int val) {
		// check if list is empty
		if (head == nullptr) {
			head = new LinkedListNode(val);
			_currsize++;
			tail = head;
			return true;
		}

		LinkedListNode *temp = new LinkedListNode(val);
		tail->next = temp;
		temp->next = head;
		head = temp;

		// if we reach maxsize
		if (_currsize == _maxsize)
			dequeue();

		_currsize++;

		return true;
	}

};

// find the first non-repeated character in a string

char findfirstnonrepeatedchar(const string &s) {

	enum Number { First = 1, Many };
	if (s.empty()) {
		return ' ';
	}

	int len = s.length();

	if (len == 1) {
		return s[0];
	}

	// put everything first into a hashtable
	std::unordered_map<char, Number> table;
	std::unordered_map<char, Number>::const_iterator got;

	for (int i = 0; i < len; i++) {
		got = table.find(s[i]);
		if (got == table.end()) // entry not found
			table.insert({ s[i], First });
		else // entry found {
			if (got->second == First) {
				table.at(got->second) = Many;
				//got->second = Many;
			}
	}

// post: table now has all the frequencies

for (int i = 0; i<len; i++) {
	got = table.find(s[i]);
	if (got->second == First)
		return s[i];
}

// no non-repeating char was found
return ' ';
}


// Given an array of integers, find max subarray sum (for contigous elements) 
// use Kadane's algorithm
int longestsubarray(int test[], int size) {

	int max_so_far = 0;
	int max_ending_here = 0;

	if (size < 1)
		return 0;

	for (int i = 0; i<size; i++) {

		max_ending_here = max_ending_here + test[i];

		if (max_ending_here < 0)
			max_ending_here = 0;
		else if (max_so_far < max_ending_here) // compare only when max_ending 
											   // is > 0
			max_so_far = max_ending_here;

	}

	return max_so_far;

}

//Given a binary tree, print out the tree in level order.
// http://www.geeksforgeeks.org/level-order-tree-traversal/"

enum Order { Pre, Post, Inorder };

void visit(TreeNode *root) {
	if (root != nullptr)
		cout << "TreeNode :" << root->_data << endl;
}

void Traversals(TreeNode *root, Order order) {

	if (root == nullptr)
		return;
	switch (order) {
	case Pre:
		visit(root);
		Traversals(root->left, Pre);
		Traversals(root->right, Pre);
		break;
	case Post:
		Traversals(root->left, Post);
		Traversals(root->right, Post);
		visit(root);
		break;
	case Inorder:
		Traversals(root->left, Inorder);
		visit(root);
		Traversals(root->right, Inorder);
		break;
	}


}


// do level order traversal which is a BFS
// for each TreeNode in queue, visit the TreeNode and enqueue their left and right TreeNodes


void LevelOrderTraversal(TreeNode *root) {

	if (root == nullptr)
		return;

	// use a queue to store the TreeNodes
	std::queue<TreeNode*> myqueue;
	myqueue.push(root);

	while (!myqueue.empty()) {

		int size = myqueue.size(); // only process TreeNodes from last run

		for (int i = 0; i<size; i++) {
			TreeNode *node = myqueue.front();
			visit(node);
			if (node->left != nullptr)
				myqueue.push(node->left);
			if (node->right != nullptr)
				myqueue.push(node->right);
			myqueue.pop();
		} // for
	}

}



/*
Given input file with 4 billion non-negative ints
algorithm to generate integer not contained in file
Assume 1GB of memory available for task
What if you only had 10Mb of memory? Assume all values are distinct and now
have no more than 1 billion non-negative integers.

one int = 4 bytes

1 Gb memory = 1 billion bytes
4 Gb memory needed to represent 4 billion bytes

hash the numbers - define boundaries
*/
/*
Use Bitarray to store data, loop through and find next largest

For smaller memory, store as much possible in one bitarray, and tighten the range to find the number


*/
/*
Minimum number of squares whose sum equals to given number n
A number can always be represented as a sum of squares of other numbers. Note
that 1 is a square and we can always break a number as (1*1 + 1*1 + 1*1 + …).
Given a number n, find the minimum number of squares that sum to X.
*/


int squarenum(int num) {
	return num * num;
}


//for n>=3, getMinSquares(n) = min{1+(n-x*x)} for x>=1 and x*x <=n

// Returns count of minimum squares that sum to n
int getMinSquares(int n)
{
	// base cases
	if (n <= 3)
		return n;

	// getMinSquares rest of the table using recursive
	// formula
	int res = n; // Maximum squares required is n (1*1 + 1*1 + ..)

				 // Go through all smaller numbers
				 // to recursively find minimum
	for (int x = 1; x <= n; x++)
	{
		int temp = x*x;
		if (temp > n)
			break;
		else
			res = min(res, 1 + getMinSquares(n - temp));
	}
	return res;
}


/*
Flood fill Algorithm – how to implement fill() in paint?
In MS-Paint, when we take the brush to a pixel and click, the color of the
region of that pixel is replaced with a new selected color. Following is the
problem statement to do this task.
Given a 2D screen, location of a pixel in the screen and a color, replace
color of the given pixel and all adjacent same colored pixels with the given
color.

Example:

Input:
screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 0, 0},
{1, 0, 0, 1, 1, 0, 1, 1},
{1, 2, 2, 2, 2, 0, 1, 0},
{1, 1, 1, 2, 2, 0, 1, 0},
{1, 1, 1, 2, 2, 2, 2, 0},
{1, 1, 1, 1, 1, 2, 1, 1},
{1, 1, 1, 1, 1, 2, 2, 1},
};
x = 4, y = 4, newColor = 3
The values in the given 2D screen indicate colors of the pixels.
x and y are coordinates of the brush, newColor is the color that
should replace the previous color on screen[x][y] and all surrounding
pixels with same color.

Output:
Screen should be changed to following.
screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 1, 1, 1, 0, 0},
{1, 0, 0, 1, 1, 0, 1, 1},
{1, 3, 3, 3, 3, 0, 1, 0},
{1, 1, 1, 3, 3, 0, 1, 0},
{1, 1, 1, 3, 3, 3, 3, 0},
{1, 1, 1, 1, 1, 3, 1, 1},
{1, 1, 1, 1, 1, 3, 3, 1},
};
Flood Fill Algorithm:
The idea is simple, we first replace the color of current pixel, then recur
for 4 surrounding points. The following is detailed algorithm.
*/
const int M = 8;
const int N = 8;

void floodfillutil(int x, int y, int prevColor, int newColor, int screen[][N]) {

	if (x<0 || x >= M || y<0 || y >= N) {
		return;
	}

	if (screen[x][y] == prevColor)
		screen[x][y] = newColor;
	else
		return;

	floodfillutil(x + 1, y, prevColor, newColor, screen);
	floodfillutil(x - 1, y, prevColor, newColor, screen);
	floodfillutil(x, y + 1, prevColor, newColor, screen);
	floodfillutil(x, y - 1, prevColor, newColor, screen);
}

void floodfill(int x, int y, int newColor, int screen[][N]) {
	if ((x<0 || (x >= M)) || (y<0 || (y >= N))) {
		return;
	}

	// if newColor is the same as the current color we don't do anything
	if (screen[x][y] == newColor)
		return;

	floodfillutil(x, y, screen[x][y], newColor, screen);

}

// given BST, return min data value found in the tree
TreeNode * minvalue(TreeNode *root) {
	if (root == nullptr)
		return nullptr;

	TreeNode *current = root;

	while (current->left != nullptr) {
		current = current->left;
	}

	return current;
}

/*
given node in BST (with value), find next inorder successor
inorder successor is smallest key greater than given key
*/

TreeNode * FindNextSuccessor(TreeNode *root, TreeNode *start) {
	if (root == nullptr)
		return nullptr;

	if (start->right != nullptr)
		return minvalue(start->right);

	TreeNode *succ = nullptr;
	
	while (root != nullptr) {
		//start at root
		if (root->_data > start->_data) {
			succ = root;
			root = root->left;
		}
		else if (root->_data < start->_data) {
			root = root->right;
		}
		else   // probably found the match, break out
			break;
	}	
	return succ;
}


// given BST, return max data value found in the tree
TreeNode * maxvalue(TreeNode *root) {
	if (root == nullptr)
		return nullptr;

	TreeNode *current = root;

	while (current->right != nullptr) {
		current = current->right;
	}

	return current;
}

/*
given node in BST (with value), find next inorder predecessor
inorder predecessor is smallest key less than given key
*/

TreeNode * FindPredecessor(TreeNode *root, TreeNode *start) {
	if (root == nullptr) {
		return nullptr;
	}

	if (start->left != nullptr)
		return maxvalue(start->left);

	TreeNode *pred = nullptr;

	while (root != nullptr) {
		//start at root
		if (root->_data > start->_data) {
			root = root->left;
		}
		else if (root->_data < start->_data) {
			pred = root;
			root = root->right;
		}
		else   // probably found the match, break out
			break;
	}
	return pred;
}

//Return if true/false flag found in a binary tree with child and next pointers
//
class NodeSpecial {
public:
	bool flag;
	NodeSpecial *next;
	NodeSpecial *child;
	int value;
	NodeSpecial() { 
		flag = false; 
		next = nullptr;
		child = nullptr;
	}
	NodeSpecial(int val) {
		flag = false;
		next = nullptr;
		child = nullptr;
		value = val;
	}
};

NodeSpecial * TraverseBinarySpecial(NodeSpecial *root) {
	
	if (root == nullptr)
		return nullptr;

	if (root->flag) return root; 

	// use a queue to store the TreeNodes
	std::queue<NodeSpecial *> myqueue;
	myqueue.push(root);

	while (!myqueue.empty()) {

		int size = myqueue.size(); // only process TreeNodes from last run
		NodeSpecial *node;

		for (int i = 0; i<size; i++) {
			node = myqueue.front();
			while (node) {
				if (node->flag)
					return node;
				if (node->child)
					myqueue.push(node->child);
				node = node->next;
			}
			myqueue.pop();
		} // for
	}

}

// is sub a substring of word?
// uses string C++ class
bool substr(string sub, string word) {


	int wlen = word.length();
	int slen = sub.length();

	if (slen > wlen || sub.empty() || word.empty())
		return false;

	int subcount = 0;

	for (int i = 0; i < wlen; i++) {

		while (word[i] == sub[subcount]) {
			i++;
			subcount++;
			if (subcount >= slen || i >= wlen) break;
		}

		// fully matched
		if (subcount == slen)
			return true;
		else
			subcount = 0;
	}
	return false;
}

// determine if a string is a substring of another string
// assume each is \0 delimited
// this implementation is a little more complicated than substr
bool substr1(char *sub, char *word) {
	if ((sub == nullptr) || (word == nullptr)) {
		return false;
	}

	int match_counter = 0;
	int length_sub = strlen(sub);
	// begin points to sub
	char *pword = word;
	char *psub = sub;

	while (*pword != '\0') {
		// start matching if the first letters match
		if (*pword == *psub) {
			match_counter = 0;
			while (*pword == *psub) {
				match_counter++;
				pword++;
				psub++;
				if ((*pword == '\0') && (*psub == '\0')) {
					return true;
				}
				else if (*pword == '\0')
					return false;
			}
			if (match_counter == length_sub)
				return true;
			if (*pword == '\0') return false;
			psub = sub;  //reset sub pointer
		} // if
		pword++;
	} // while 
	return false;

}

// walking through linked list (singly), remove duplicates

void RemoveDuplicates(LinkedListNode *head) {

	if (head == nullptr)
		return;

	// map value in linked list 
	std::unordered_map<int, bool> hash;
	hash[head->_val] = true;

	LinkedListNode *curr = head;

	while (curr->next != nullptr)
	{
		if (hash.find(curr->next->_val) != hash.end()) // duplicate found
		{
			// duplicate
			LinkedListNode *tmp = curr->next;
			curr->next = curr->next->next;
			tmp->next = nullptr;
			delete tmp;
		}
		else //duplicate not found, add val to hash table
		{
			hash[curr->next->_val] = true;
			curr = curr->next;
		}

	} // while
}

/*
Check if a given tree contains a linked list.
*/

/*
Calculate all permutations for an array of integers.

For example : Given{ 3, 5, 8 } -Output should be : { 3, 5, 8 }, { 3, 8, 5 }, { 5, 3, 8 }, { 5, 8, 3 }, { 8, 5, 3 }, { 8, 3, 5 }
*/

/*
Given a collection of words, find which of the words exist in a matrix of letters.

Example:

Given the matrix bellow, find the words “ALL” and “LOAN”

*/


//FindMthNodeinBST
// use an inorder traversal
void FindMthNodeinBST(TreeNode *root, int target, int *curr) {

	if (root == nullptr)
		return;

	FindMthNodeinBST(root->left, target, curr);

	(*curr)++;
	if (*curr == target)
		cout << "Node: " << root->_data << " is Node number: " << target << endl;

	FindMthNodeinBST(root->right, target, curr);
}

// assume a null terminated string
// declare string as char str[] = "foobar";
void reverse(char *str) {

	if (str == nullptr || *str == '\0')
		return;

	// reverse string in place using two pointers.
	char *end = str;

	while (*end)
		end++;

	end--;

	char tmp;

	while (str < end) {
		tmp = *str;
		*str = *end;
		*end = tmp;
		end--;
		str++;
	}

}



int main()
{
// Test Code for RemoveDuplicates
/*	LinkedListNode *head = new LinkedListNode(1);
	LinkedListNode *curr = head;

	curr->next = new LinkedListNode(2);
	curr->next->next = new LinkedListNode(1);
	curr->next->next->next = new LinkedListNode(3);
	curr->next->next->next->next = nullptr;
	
	RemoveDuplicates(head);

	// print out list

	while (curr != nullptr) {
		cout << "Linked List Node: " << curr->_val << endl;
		curr = curr->next;
	}
*/

// Test Code for substr
/*	char *word = "ABABAB";
	char *sub = "AC";

	cout << "Is this: " << sub << " a substring of: " << word << " ?" << endl;
	cout << "Answer: " << substr(sub, word) << endl;
*/

// Test code for TraverseBinarySpecial(NodeSpecial *root) {

/*
	NodeSpecial *ns = new NodeSpecial(1);
	ns->flag = false;
	ns->child = new NodeSpecial(5);
	ns->child->flag = true;
	ns->child->next = new NodeSpecial(6);
	ns->child->next->flag = true;
	ns->next = new NodeSpecial(2);
	ns->next->flag = false;
	ns->next->next = new NodeSpecial(3);
	ns->next->next->flag = false;
	ns->next->next->next = new NodeSpecial(4);
	ns->next->next->next->flag = false;

	NodeSpecial *node = TraverseBinarySpecial(ns);

	cout << "Node with: " << node->value << " has true flag" << endl;
*/

//	Test code for FindMthNodeinBST
/*
			   15
		   8            20
		 6   9      17      22  
        4 7   10  16  18  21  23

Inorder visit order:
		Visit Node: 4
		Visit Node: 6
		Visit Node: 7
		Visit Node: 8
		Visit Node: 9
		Visit Node: 10
		Visit Node: 15
		Visit Node: 16
		Visit Node: 17
		Visit Node: 18
		Visit Node: 20
		Visit Node: 21
		Visit Node: 22
		Visit Node: 23

	TreeNode *root = new TreeNode(15);
	root->left = new TreeNode(8);
	root->left->right = new TreeNode(9);
	root->left->right->right = new TreeNode(10);
	root->left->left = new TreeNode(6);
	root->left->left->left = new TreeNode(4);
	root->left->left->right = new TreeNode(7);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(17);
	root->right->left->left = new TreeNode(16);
	root->right->left->right = new TreeNode(18);
	root->right->right = new TreeNode(22);
	root->right->right->right = new TreeNode(23);
	root->right->right->left = new TreeNode(21);

	int curr = 0;
	FindMthNodeinBST(root, 2, &curr);
	curr = 0;
	FindMthNodeinBST(root, 9, &curr);
*/

	// Test code for reversestring()

	char str[] = "ABD";
	reverse(str);
	cout << "Reversed word: " << str << endl;

    return 0;
}

