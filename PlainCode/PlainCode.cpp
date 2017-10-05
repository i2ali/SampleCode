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
#include <stack>

typedef unsigned char BYTE;

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

bool heightbalancedrec(TreeNode *root, int &height) {
	if (root == nullptr) {
		height = 0;
		return true;
	}
	int lh = 0;
	int rh = 0;
	bool l = false;
	bool r = false;
	l = heightbalancedrec(root->left, lh);
	r = heightbalancedrec(root->right, rh);
	height = max(lh, rh) + 1;
	return (l && r && (abs(lh - rh) <= 1));
}

// determine if tree is height-balanced, O(n)
bool heightbalanced(TreeNode *root) {
	int height = 0;
	return heightbalancedrec(root, height);
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


// print all pairs of integers in a array that sum to a particular value
void findpairs(int arr[], int arraysize, int sum) {

	std::unordered_map<int,int> hashtable;

	int tofind = 0;
	std::unordered_map<int, int>::const_iterator got;

	for (int i = 0; i < arraysize; i++) {
		
		tofind = sum - arr[i];
		got = hashtable.find(tofind);

		if (got != hashtable.end())
			cout << "Pair found: " << arr[i] << ", " << tofind << endl;

		hashtable.emplace(arr[i],i);
	}

	// print out the hashtable

	for (auto i = hashtable.begin(); i != hashtable.end(); i++) {
		cout << i->first << ": " << i->second << endl;	
	}

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

class BiNode {
public:
	BiNode() { node1 = nullptr; node2 = nullptr; }
	BiNode(int val) { node1 = nullptr; node2 = nullptr; data = val; }
	BiNode *node1;
	BiNode *node2;
	int data;
};

class NodePair {
public:
	BiNode *head;
	BiNode *tail;

	NodePair(BiNode *head, BiNode *tail) {
		head = head;
		tail = tail;
	}
};


void concat(BiNode *x, BiNode *y) {
	x->node2 = y;
	y->node1 = x;
}

// convert a binary search tree to a doublylinked list
// Algorithm: use an in-order traversal
NodePair* ConvertBSTtoLinkedList(BiNode *root){

	if (root == nullptr)
		return nullptr;

	NodePair *part1 = ConvertBSTtoLinkedList(root->node1);
	NodePair *part2 = ConvertBSTtoLinkedList(root->node2);
	
	if (part1) {
		concat(part1->tail, root);	
	}

	if (part2) {
		concat(root, part2->head);
	}

	return new NodePair(part1 ? part1->head : root, part2 ? part2->tail : root);
}

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


void ConvertBytesToHexString(BYTE* bytes, uint16_t numBytes, char* hexString)
{
	for (int i = 0; i < numBytes; i++)
	{
		int b = (*bytes) >> 4;
		*hexString++ = static_cast<char>((b <= 9) ? b + '0' : (b - 10) + 'A');
		b = *bytes & 0x0F;
		*hexString++ = static_cast<char>((b <= 9) ? b + '0' : (b - 10) + 'A');
		bytes++;
	}
	*hexString++ = '\0';
}

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


// determine if one string is an anagram of another

bool isanagram(const string &s1, const string &s2) {

	if (s1.size() != s2.size()) return false;

	int size = s1.size();
	
	// put everything first into a hashtable
	std::unordered_map<char, int> table;
	std::unordered_map<char, int>::const_iterator got;

	for (int i = 0; i < size; i++) {
		got = table.find(s1[i]);
		if (got == table.end()) // entry not found
			table.insert({ s1[i], 1 });
		else {// entry found {
			table[s1[i]]++; 
	    }
	}

	for (int i = 0; i < size; i++) {
		got = table.find(s2[i]);
		if ((got == table.end()) || (table[s2[i]] == 0))
			return false; 
		else {
			table[s2[i]]--;
			if (table[s2[i]] == 0)
				table.erase(s2[i]);
		}
	}

	// table must be empty now
	return (table.size() == 0);
}



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

/*
You are given an array of positive and negative integers. 
If a number n at an index is positive, then move forward n steps. 
Conversely, if it's negative (-n), move backward n steps. 
Assume the first element of the array is forward next to the last element, 
and the last element is backward next to the first element. 
Determine if there is a loop in this array. A loop starts and ends at a particular index with more than 1 element along the loop. The loop must be "forward" or "backward'.
*/
bool circularArrayLoop(vector<int>& nums) {
		if (nums.empty()) return false;
		int index = 0;
		int size = nums.size();
		int i = 0;
		int val = 0;
		bool direction = true;
		if (nums[0] < 0) direction = false;

		while (i <= size) {
			val = nums[index];
			if ((val > 0 && !direction) || (val < 0 && direction)) return false;
			index = (index + val) % size;
			i++;
			if (index == 0) return true;
		}
		return false;
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
		TreeNode *node = myqueue.front();
		visit(node);
		myqueue.pop();
		if (node->left != nullptr)
			myqueue.push(node->left);
		if (node->right != nullptr)
			myqueue.push(node->right);
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
// exponential run-time
int getMinSquares1(int n)
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
			res = min(res, 1 + getMinSquares1(n - temp));
	}
	return res;
}

// DP version of min squares
int getMinSquares(int n)
{
	int *dp = new int[n + 1];

	// getMinSquares table for base case entries
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 3;

	// fill in values up till n
	for (int i = 4; i <= n; i++)
	{
		// max value is i as i can always be represented
		// as 1*1 + 1*1 + ...
		dp[i] = i;

		for (int x = 1; x <= i; x++) {
			int temp = x*x;
			if (temp > i)
				break;
			else dp[i] = min(dp[i], 1 + dp[i - temp]);
		}
	}

	int res = dp[n];
	delete[] dp;

	return res;
}

// Count the number of prime numbers less than a non - negative number, n.
// To determine if a number is prime, check if it is not divisible by any number less than n. 
// The runtime complexity of isPrime function would be O(n) and hence counting the total prime numbers up to n would be O(n2). 


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
	return nullptr;
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

LinkedListNode * LinkedListDetectCircularLoop(LinkedListNode *start) {

	if (start == nullptr)
		return nullptr;

	LinkedListNode *slowptr = start;
	LinkedListNode *fastptr = start;

	while (fastptr && fastptr->next) {
		slowptr = slowptr->next;
		fastptr = fastptr->next->next;
	
		if (fastptr == slowptr)	// fastptr has overtaken slowptr
		{
			cout << "Loop detected!" << endl;
			break;
		}
	}

	// no loop detected		
	if (fastptr || fastptr->next) {
		cout << "Loop not detected!" << endl;
		return nullptr;
	}

	// move back slowptr to the head of the list
	slowptr = start;

	while (slowptr != fastptr) {
		slowptr = slowptr->next;
		fastptr = fastptr->next;
	}

	return fastptr;

}

// 2 sum question
// given a sorted array, find 2 numbers that sum up to S.
void twosumsorted(int arr[], int size, int target) {

	if (size < 2) {
		cout << "Indeterminate size" << endl;
		return;
	}

	int beginindex = 0;
	int endindex = size - 1;
	int tempsum = 0;

	while (beginindex < endindex) {
		tempsum = arr[beginindex] + arr[endindex];

		if (tempsum == target) {
			cout << "Found match: " << arr[beginindex] << " " << arr[endindex] << endl;
			return;
		}
		else if (tempsum < target)
			beginindex++;
		else
			endindex--;
	}

	cout << "no matches found!" << endl;
	return;
}

// 2 sum question
// given a unsorted array, find 2 numbers that sum up to S.
void twosum(int arr[], int size, int target) {

	if (size < 2) {
		cout << "Indeterminate size" << endl;
		return;
	}

	int find = 0;
	unordered_map<int, int>map;
	std::unordered_map<int, int>::const_iterator got;

	for (int i = 0; i < size; i++) {
		find = target - arr[i];
		got = map.find(find);

		if (got == map.end()) {  // not found
			map.emplace(arr[i], arr[i]);
		}
		else {
			cout << "Found match: " << arr[i] << "," << got->first << endl;
			return;
		}
	}

	cout << "no matches found!" << endl;
	return;
}

// 3 sum question
// Determine if 3 integers in an array sum to a number.
void threesum(int arr[], int size, int target) {

	if (size < 2) {
		cout << "Indeterminate size" << endl;
		return;
	}

	// O(nlogn) sort
	std::sort(arr, arr + size);

	// rest is O(n), based on 2sum with sorted implementation
	for (int i = 0; i < size - 2; i++) {

		int beginindex = i + 1;
		int endindex = size - 1;
		int tempsum = 0;

		while (beginindex < endindex) {
			tempsum = arr[i] + arr[beginindex] + arr[endindex];

			if (tempsum == target) {
				cout << "Found match: " << arr[i] << " " << arr[beginindex] << " " << arr[endindex] << endl;
				return;
			}
			else if (tempsum < target)
				beginindex++;
			else
				endindex--;
		}
	} //for

	cout << "no matches found!" << endl;
	return;

}

// DP practice
// Given n, find the number of different ways to write n as a sum of 1,3,4
int FindNumSum(int n) {

	int *D = new int[n + 1];
	D[0] = D[1] = D[2] = 1;
	D[3] = 2;

	for (int i = 4; i <= n; i++)
		D[i] = D[i - 1] + D[i - 3] + D[i - 4];

	int i = D[n];
	delete[] D;

	return i;

}

// Given a BST and 2 values(min, max) trim the tree such that all values are between min / max and still a valid BST
// Post-order traversal allows you to fix the subtrees, then visit the root
TreeNode *TrimBST(TreeNode *root, int min, int max) {

	if (root == nullptr)
		return nullptr;

	root->left = TrimBST(root->left, min, max);
	root->right = TrimBST(root->right, min, max);

	// if less than min, we care about what is on the right subtree
	if ((root->_data < min) || (root->_data > max)) {

		TreeNode *temp = nullptr;

		if (root->_data < min) {
			temp = root->right;
		}
		else if (root->_data > max) {
			temp = root->left;
		}

		delete root;
		return temp;

	}
	// node is within acceptable range, just return node as is.
	return root;
}

TreeNode *searchNode(int key, TreeNode *root,TreeNode **parent) {

	if (root == nullptr) return nullptr;

	TreeNode *curr = root;
	*parent = root;

	while (curr) {
		if (curr->_data == key) {
				return curr;
		}
		else if (curr->_data > key) {
			*parent = curr;
			curr = curr->left;
		}
		else {
			*parent = curr;
			curr = curr->right;
		}
	}
	// node not found
	*parent = nullptr;
	return nullptr; 
}

void swapValues(TreeNode *first, TreeNode *second) {
	if (!first || !second) return;

	int temp = first->_data;
	first->_data = second->_data;
	second->_data = temp;
}


// better approach, replace value with min value instead 
void swapNodes(TreeNode *root) {
	if (root == nullptr) return;
	TreeNode *curr = root;
	TreeNode *parent = root;	
	// true = right, false = left;
	bool parentfix = true;

	while (curr) {

		if (curr->right) {
			swapValues(curr, curr->right);
		}
		else if (curr->left) {
			swapValues(curr, curr->left);
			}
		else {
			if (parentfix)
				parent->right = nullptr; 
			else 
				parent->left = nullptr;
			curr = nullptr;
			delete curr;
			break;
		}

		parent = curr;
		if (curr->right) {
			curr = curr->right;
			parentfix = true;
		}
		else {
			curr = curr->left;
			parentfix = false;
		}
	}
}

TreeNode* deleteNode(TreeNode* root, int key) {
	if (root == nullptr)
		return nullptr;
	// check if single node
	if (!(root->right) && !(root->left) && (root->_data == key)) {
		delete root;
		return nullptr;
	}

	TreeNode *parent = nullptr;
	TreeNode *sNode = searchNode(key, root, &parent);
	if (sNode == nullptr) return root;

	// if child node, just delete it 
	if ((sNode->right == nullptr) && (sNode->left == nullptr)) {
		if (parent->right) {
			if (parent->right->_data == key)
				parent->right = nullptr;
		}
		if (parent->left) {
			if (parent->left->_data == key)
				parent->left = nullptr;
		}

		delete sNode;
		return root;
	}
	swapNodes(sNode);
	return root;

}


// Implement FizzBuzz test:
// Write a program that prints the numbers from 1 to 100. But for multiples of three print "Fizz" instead of the number and for the multiples of five print "Buzz".For numbers which are multiples of both three and five print "FizzBuzz".
void FizzBuzzTest() {
	for (int i = 1; i <= 100; i++) {
		
		if ((i % 3) == 0) 
			cout << "Fizz";		
		if ((i % 5) == 0)
			cout << "Buzz";

		if (((i % 5) != 0) && ((i % 3) != 0))
			cout << i;

		cout << endl;

	} // for
}

/*
Check if we have a valid BST, traverse the BST in order as they will all be in ascending order as per the properties of a BST.
*/

bool isBSTInOrderHelper(TreeNode *p, int& prev) {
	if (!p) return true;

	if ((isBSTInOrderHelper(p->left, prev)) && (p->_data > prev)) 
		return isBSTInOrderHelper(p->right, p->_data);
	else 
		return false;
}

bool isBSTInOrder(TreeNode *root) {
	int prev = INT_MIN;
	return isBSTInOrderHelper(root, prev);
}


int remDupes(int *a, int size) {
	if (size <= 2) {
		return size;
	}
	int curr = 1;
	int prev = 0;
	int flag = false;

	while (curr < size) {
		
		if (a[curr] == a[prev])
			flag = true;
		else if ((a[curr] != a[prev]) && (flag)) {
			a[prev + 1] = a[curr];
			prev++;
			flag = false;
		}
		else {
			prev++;
		}

		curr++;			
	}

	return prev + 1;
}

// lowest common ancestor in a tree

// Implement data structure “Map” storing pairs of integers (key, value) and define 
// following member functions in O(1) runtime: void insert(key, value), void delete(key), 
// int get(key), int getRandomKey().


// given a list of file paths, determine the most common directory path and return it
// assume every string passed in has a root dir '\' (may not be a valid assertion though)
string commonFilePath(const vector<string> &paths) {
	if (paths.size() == 0)
		return string("");
	if (paths.size() == 1)
		return paths[0];

	int lastcommonpath = 0;
	int pathsize = paths.size();
	bool mismatch = false;
	char begin;
	int index = 0;

	while (!mismatch) {
		begin = paths[0][index];
		
		for (int i = 1; i < pathsize; i++) {
			if ((paths[i].size() <= index) || paths[i][index] != begin) {
				mismatch = true;
				break;
			}
		}

		if ((begin == '/') && (!mismatch)) {
			lastcommonpath = index;
		}
	
		index++;
	
	}
	if (lastcommonpath == 0)
		return "/";
	else
		return paths[0].substr(0, lastcommonpath);
}


int DiameterBinTreeOpt(TreeNode *root, int &height) {
	if (root == nullptr) {
		height = 0;
		return 0;
	}
		
	int lh = 0;
	int rh = 0;

	int ld = DiameterBinTreeOpt(root->left, lh);
	int rd = DiameterBinTreeOpt(root->right, rh);

	height = max(lh, rh) + 1;

	return max((lh + rh + 1),max(ld, rd));
}

int DiameterBinTreeDriver(TreeNode *root) {
	int height = 0;
	return DiameterBinTreeOpt(root, height);
}


// perform zigzag traversal of a given binary tree
void ZigZagTraversal(TreeNode *root) {
	if (root == nullptr)
		return;

	// use two stacks to store data, one for L->R, and another for R->L
	stack<TreeNode *>ltr;
	stack<TreeNode *>rtl;




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
*/
/*	TreeNode *root = new TreeNode(15);
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
*/


//			  15
//		  8        20
//		6   9    19   25
//     5     10     22  26

	TreeNode *root = new TreeNode(15);
	root->left = new TreeNode(8);
	root->left->right = new TreeNode(9);
	root->left->right->right = new TreeNode(10);
	root->left->left = new TreeNode(6);
	root->left->left->left = new TreeNode(5);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(19);
	root->right->right = new TreeNode(25);
	root->right->right->left = new TreeNode(22);
	root->right->right->right = new TreeNode(26);

/*	if (heightbalanced(root))
		cout << "Height balanced!" << endl;
	else 
		cout << "NOT Height balanced!" << endl;
*/
	cout << "Diameter of binary tree: " << DiameterBinTreeDriver(root) << endl;

			

//	root = deleteNode(root, 5);
//	Traversals(root, Inorder);

/*
	int curr = 0;
	FindMthNodeinBST(root, 2, &curr);
	curr = 0;
	FindMthNodeinBST(root, 9, &curr);

	TreeNode *tree = TrimBST(root, 8, 17);
	Traversals(tree, Inorder);
	delete tree;
*/
/* Test code for reversestring()

	char str[] = "ABD";
	reverse(str);
	cout << "Reversed word: " << str << endl;
*/
/*
	// Test Code for DetectCircularLoop
	LinkedListNode *head = new LinkedListNode(1);
	LinkedListNode *curr = head;

	curr->next = new LinkedListNode(2);
	curr->next->next = new LinkedListNode(3);
	curr->next->next->next = new LinkedListNode(4);
	curr->next->next->next->next = curr->next; // loop from 4 to 2

	LinkedListNode *startofloop = LinkedListDetectCircularLoop(curr);

    return 0;

// test code for finding all pairs of integers that sum to a particular value

	int test[] = { 7,1,2,8 };
	findpairs(test, sizeof(test)/sizeof(int), 9);

*/

/*	int test[] = { -1, -1, 0, 4, 100, 14};
	twosumsorted(test, sizeof(test)/sizeof(int), 10);

	threesum(test, sizeof(test) / sizeof(int), 2);
*/

//	cout << FindNumSum(10) << endl;
//	FizzBuzzTest();


// test code for isanagram
//	bool flag =	isanagram("abcdefs", "fedcbaz");
//	(flag ? cout << "Anagram!" << endl : cout << "Not an anagram!" << endl);

/*
	if (isBSTInOrder(root))
		cout << "Valid BST" << endl;
	else
		cout << "Not Valid BST" << endl;
*/
/*	int a[6] = { 1,2,2,4,4,19};

	int arrsize = remDupes(a, sizeof(a)/sizeof(int));

	for (int i = 0; i < arrsize; i++) {
		cout << i << ": " << a[i] << " " << endl;
	}
	cout << endl;
	cout << "Array Size: " << arrsize << endl;

	vector<string>paths = { "/test/a/a","/test/bc/a","/test/a/",""};
	cout << commonFilePath(paths) << endl;
*/

	/*
	BYTE* bytes = nullptr;

	BYTE buff[100];
	BYTE *hexbuff = nullptr;

	//void ConvertBytesToHexString(BYTE* bytes,int numBytes,char* hexString)
	//ConvertBytesToHexString(buff, 100, reinterpret_cast<char *> (hexbuff));

	*/

};

