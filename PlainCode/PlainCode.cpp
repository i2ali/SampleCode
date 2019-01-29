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
#include <set>

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

/*
PROBLEM: given an upside tree (i.e. DOM), convert it back to HTML stream
*/

// build HTML stream
class HTMLBuilder {
private:
	string htmlstream;
	string default = "<html><head><title></title></head><body><h1></h1><p></p></body></html>";
public:
	void AddtoStream(string stream);
	HTMLBuilder() {};
};

// TO DO: add operator overrides
void HTMLBuilder::AddtoStream(string stream)
{
	htmlstream += stream;
}

class UpsideDownNode {
	UpsideDownNode() { parent = nullptr; }
	UpsideDownNode(string tag) { tagname = tag; }
	UpsideDownNode *parent;
	string tagname;
};

void minDiffInBSTWrapper(TreeNode* root, int &prev, int &min) {

	if (root == nullptr)
		return;

	minDiffInBSTWrapper(root->left, prev, min);

	min = std::min(root->_data - prev, min);
	prev = root->_data;

	minDiffInBSTWrapper(root->right, prev, min);
}

int minDiffInBST(TreeNode* root) {
	int prev = INT_MIN/2;   //TODO: guard against overflow above where we calculating min
	int min = INT_MAX;
	minDiffInBSTWrapper(root,prev,min);
	return min;
}

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


class MyHeap {

private:
	vector <int> arr;
	void BubbleDown(int index);
	void BubbleUp(int index);
	void Heapify();
	void swapvalues(int index1, int index2) {
		int temp = arr[index1];
		arr[index1] = arr[index2];
		arr[index2] = temp;	
	}

public:
	MyHeap(const vector<int>&vector) {
		arr = vector;
		Heapify();
	};
	MyHeap(const int *array, int arrsize) {		
		for (int i = 0; i < arrsize; i++) {
			arr.push_back(array[i]);
		}
		Heapify();
	}
	virtual ~MyHeap() {}
	int getmin() { return arr[0]; }
	void insertElement(int val);
	void DeleteMin();
};

// delete value and swap with last value in array, which you then BubbleDown
void MyHeap::DeleteMin() {

	if (arr.size() == 0) return;
	arr[0] = arr[arr.size() - 1];
	arr.pop_back();

	BubbleDown(0);	

}

// swap with parent vals until meets heap property
void MyHeap::BubbleUp(int index) {

	if (index == 0)
		return;

	int parentindex = (int)((index - 1)/2);

	if (arr[parentindex] > arr[index]) {
		swapvalues(index, parentindex);
		BubbleUp(parentindex);
	}

}

// swap value down heap until it meets min heap property
void MyHeap::BubbleDown(int index) {	
	int leftindex = index * 2 + 1;
	int rightindex = index * 2 + 2;

	// leaf node 
	if (leftindex >= arr.size()) {
		return;
	}

	int minindex = index;

	if (arr[index] > arr[leftindex]) {
		minindex = leftindex;
	}

	if ((rightindex >= arr.size()) && (arr[minindex] > arr[rightindex]))
		minindex = rightindex;

	if (minindex != index) {
		swapvalues(index, minindex);
		BubbleDown(minindex);
	}
}

void MyHeap::insertElement(int val) {
	arr.push_back(val);
	BubbleUp(arr.size());
}

// basically bubble down each value to meet overall heap property
void MyHeap::Heapify() {
	int len = arr.size();

	for (int i = 0; i < len; i++) {
		BubbleDown(i);	
	}

}



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


class Node {
public:
	int val;
	Node *right;
	Node *left;
	Node() { left = nullptr; right = nullptr; }
	explicit Node(int data) { val = data; left = nullptr; right = nullptr; }
	virtual ~Node() {}
};


// given linked list, find midpoint and return pointer to that
LinkedListNode *FindMidpoint(LinkedListNode *head, LinkedListNode *tail) {
	if (head == nullptr) return nullptr;
	if (head == tail) return head;
	LinkedListNode *curr = head;
	int size = 0;
	for (; curr!=tail; ++size) {
		curr = curr->next;
	}
	int mid = size / 2;
	curr = head;
	for (int i = 0; i < mid; ++i) {
		curr = curr->next;
	}
	return curr;
}

Node* ConvertLinkedListtoBSTHelper(LinkedListNode *head,LinkedListNode *tail) {
	if (head == nullptr)
		return nullptr;

	LinkedListNode *mid = FindMidpoint(head,tail);
    //TODO: mid == null?
	Node *root = new Node(mid->_val);
	root->left = ConvertLinkedListtoBSTHelper(head, mid);
	root->right = ConvertLinkedListtoBSTHelper(mid->next,tail);
     
	return root;
}

Node* ConvertLinkedListtoBst(LinkedListNode *head) {
	return ConvertLinkedListtoBSTHelper(head, nullptr);
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

// do a reverse in-order traversal
// example:
/*
      A
   B    C
  D E  F G
Resulting list :  head-> D B E A F C G

G->right = *head                     G = *head 
*head->left = G;
*head = G
C->right = head                  *head -> C = G  
*head->left = C
*head = C
*/
void ConvertBSTtoLinkedList1(Node *root, Node **head) {
	if (root == nullptr)
		return;

	ConvertBSTtoLinkedList1(root->right, head);

	root->right = *head;

	if (*head != nullptr)
	   (*head)->left = root;

	// update new pointer to head
	*head = root;

	ConvertBSTtoLinkedList1(root->left, head);
}

// Binary Search on a BST
bool BinarySearch(Node *root, int target) {
	if (root == nullptr)
		return false;
	if (root->val == target)
		return true;
	else if (target < root->val)
		return BinarySearch(root->left, target);
	else
		return BinarySearch(root->right, target);
}

// Binary Search on a list
bool BinarySearch(vector<int>&list, int begin, int end, int target) {

	if (end >= begin) {
		int midpoint = begin + (end - begin) / 2;

		if (list[midpoint] == target)
			return true;
		else if (list[midpoint] < target)
			return BinarySearch(list, midpoint + 1, end, target);
		else
			return BinarySearch(list, begin, midpoint - 1, target);
	}
	else
		return false;
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

	int len = (int)s.length();

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
	reverseoneword(0, (int)(s.length() - 1), s);

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

	int size = (int)s1.size();
	
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
		if ((got == table.end()) || (table[s2[i]] <= 0))
			return false; 
		else {
			table[s2[i]]--;
		}
	}

	return true;
}



// find the first non-repeated character in a string

char findfirstnonrepeatedchar(const string &s) {

	enum Number { First = 1, Many };
	if (s.empty()) {
		return ' ';
	}

	int len = (int)s.length();

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
// Note if list is sorted, we would simply skip ahead to positive segment and sum everything there
int longestsubarray(int test[], int size) {

	if (size < 1)
		return 0;

	int max_so_far = 0;
	int max_ending_here = 0;

	for (int i = 0; i < size; i++) {

		max_ending_here += test[i];

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
		int size = (int)nums.size();
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
	std::queue<TreeNode*> myqueue = {};
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
that 1 is a square and we can always break a number as (1*1 + 1*1 + 1*1 + ).
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


// GCD(a,b) - Greatest Common Divisor
// the largest number that cleanly divides a and b
int gcd(const int a, const int b) {
	int min = std::min(a, b);
	
	for (int i = min; i > 0; i--) {
		if ((a % i == 0) && (b % i == 0)) {
			return i;
		}
	}
	return min;
}

// Euclid's algorithm
// gcd(a,b) = 
//           a = b * n + (a % b)
//           b = (a % b) * n + (a % b)  (first a%b is from previous step)
//           do above until a%b=0, i.e. until we have no remainder 
int gcdfast(int a, int b) {
	if (b == 0) return a;
	cout << "A: " << a << " B: " << b <<  " A % B : " << a % b << endl;
	return gcdfast(b, a % b);
}


//determine if number is a prime number
/* optimizations: 
	even numbers are not prime, except for 2
    no need to check for numbers beyond square root of the target number. 
	m = sqrt(n) - if n divides a number greater than m, then the result will be less than m, then n will also divide 
	a number <= m. Basically as the denominator increases, we will get numbers < m, which we would have already checked, 
	so this is redundant.  
*/
bool isPrime(int n) {

	if (n <= 1)
		return false;
	if (n == 2)
		return true;
	if (n % 2 == 0) 
		return false;
     
	int m = (int)sqrt(n);

	for (int i = 3; i <= m; i+=2) {

		if (n % i == 0) {
			return false;
		}
	}
	return true;
}


// Count the number of prime numbers less than a non - negative number, n.
// To determine if a number is prime, check if it is not divisible by any number less than n. 
// Lets use the Sieve of Erathosnes
// return a list of primes in the form of a boolean array
// consumer passes in array of bool of size i
bool * returnPrimes(int numprime, size_t &size) {

	bool *primes = new bool[numprime+1];
	for (int i = 0; i <= numprime; i++)
		primes[i] = true;

	primes[0] = false;
	primes[1] = false;

	int m = (int)sqrt(numprime);

	for (int i = 2; i <= m; i++) {
		if (primes[i]){
			for (int k = i*i; k <= numprime; k += i)
				primes[k] = false;
		}
	} // for

	size = numprime+1;
	return primes;
}


// find median of two sorted arrays


/*
Flood fill Algorithm  how to implement fill() in paint?
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

		int size = (int)myqueue.size(); // only process TreeNodes from last run
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

// almost the same as my other implementation, but a little more simpler imo
bool substrTest(string A, string B) {

	int Alen = (int)A.length();
	int Blen = (int)B.length();

	if (Alen > Blen || A.empty() || B.empty())
		return false;
	int ACount = 0;
	int BCount = 0;

	while (BCount < Blen) 
	{
		if (A[ACount] == B[BCount]) {
			ACount++;
			if (ACount == Alen) {
				return true;
			}
		}
		else {
			ACount = 0;
		}
		BCount++;
	} // while
	return false;
}


// is sub a substring of word?
// uses string C++ class
bool substrTest1(string sub, string word) {


	int wlen = (int)word.length();
	int slen = (int)sub.length();

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
	int length_sub = (int)strlen(sub);
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

// given a char and a list of delimiters
bool isdelimiter(const char s, const string &delim) {

	for (int j=0; j < delim.size(); ++j) {
		if (s == delim[j]) {
			return true;
		}
	} // for
	return false;
}

// tokenizes a string delimited by given delimiters
// tok is passed and filled in with tokenized words
void mystrtok(const string &s, const string &delim, vector<string> &tok) {

	int begin = 0;
	bool regseen = false;
	bool delimseen = true;

	for (int i = 0; (i < s.size()); ++i) {
		   if (isdelimiter(s[i], delim) == true) {
			   delimseen = true;
			   if (regseen == true) { // delim seen, last time regular word was seen
				   regseen = false;
				   tok.push_back(s.substr(begin, i - begin));
			   }			   
			}
		   else {  // reg word seen
			   regseen = true;
			   if (delimseen == true) { // reg seen, last time delim was seen
				   delimseen = false;
				   begin = i;
			   }
		   }
	 } // for
    
	// if last character seen was a regchar, complete the word. If delimiter, we don't care
	if (regseen)
		tok.push_back(s.substr(begin, s.size() - begin));

}

// tokenizes a string delimited by given delimiters
// tok is passed and filled in with tokenized words
// This version uses a set instead of calling delimiter
void mystrtok1(const string &s, const set<char>&delim, vector<string> &tok) {

	int begin = 0;
	bool regseen = false;
	bool delimseen = true;
	set<char>::iterator it;

	for (int i = 0; (i < s.size()); ++i) {

		it = delim.find(s[i]);
		if (!(it == delim.end())) {
			delimseen = true;
			if (regseen == true) { // delim seen, last time regular word was seen
				regseen = false;
				tok.push_back(s.substr(begin, i - begin));
			}
		}
		else {  // reg word seen
			regseen = true;
			if (delimseen == true) { // reg seen, last time delim was seen
				delimseen = false;
				begin = i;
			}
		}
	} // for

	  // if last character seen was a regchar, complete the word. If delimiter, we don't care
	if (regseen)
		tok.push_back(s.substr(begin, s.size() - begin));

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

Given the matrix bellow, find the words ALL and LOAN

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

// s t e p
// 0 1 2 3

void reverse(string &s) {
	if (s.empty()) {
		return;
    }

	int size = s.length();

	int begin = 0;
	int end = size - 1;
	char temp = ' ';

	while (begin < end) {	
		temp = s[begin];
		s[begin] = s[end];
		s[end] = temp;
	
		begin++;
		end--;	
	}

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

// various operations on a square matrix
class MatrixOps
{
public:
	MatrixOps() {};
	virtual ~MatrixOps() {};
	void FlipAroundLeftDiagonal(vector<vector<int>> &matrix);
	void FlipAroundRightDiagonal(vector<vector<int>> &matrix);
	void PrintMatrix(vector<vector<int>> &matrix);
};

void MatrixOps::PrintMatrix(vector<vector<int>>& matrix) {
	int n = (int)matrix.size();
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "| ";
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << " |" << endl;
	}
}


void MatrixOps::FlipAroundLeftDiagonal(vector<vector<int>> &matrix) {

	int n = matrix.size();

	for (int i = 0; i < n - 1; i++) {
		int temp = 0;
		for (int j = 1; j < n; j++) {
			temp = matrix[j][i];
			matrix[j][i] = matrix[i][j];
			matrix[i][j] = temp;
		}
	}
}

void MatrixOps::FlipAroundRightDiagonal(vector<vector<int>>&matrix) {

	int size = matrix.size();

	for (int count = size - 1; count > 0; --count) {
		int temp = 0;
		for (int i = 0; i < count; i++) {
			temp = matrix[size - count - 1][i];
			matrix[size - count - 1][i] = matrix[size - i - 1][count];
			matrix[size - i - 1][count] = temp;
		}
	}

}

/*
Rotate Image:
| 1 2 3 |     | 7 4 1 | 
| 4 5 6 |  -> | 8 5 2 |
| 7 8 9 |     | 9 6 3 |

First we rotate across the diagonal:
| 1 2 3 |     | 1 4 7 | 
| 4 5 6 |  -> | 2 5 8 |
| 7 8 9 |     | 3 6 9 | 

Swap across the middle vertical axis:
| 1 4 7 |     | 7 4 1 |
| 2 5 8 |  -> | 8 5 2 | 
| 3 6 9 |     | 9 6 3 |

*/

void PrintMatrix(vector<vector<int>>& matrix) {
	int n = (int)matrix.size();
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "| ";
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << " ";
		}
		cout << " |" << endl;
	}
}

void RotateMatrix(vector<vector<int>>& matrix) {  

	int n = (int)matrix.size();
	// Check to see if this is a NxN matrix
	if (matrix[0].size() != n) {
		return;
	}
	int temp;

	PrintMatrix(matrix);
	// rotate across the diagnonal
/*	0,1 -> 1,0
    0,2 -> 2,0
	1,2 -> 2,1
*/
	for (int i = 0; i < n -1; i++) {
		for (int j = 1; j < n; j++) {
			temp = matrix[j][i];
			matrix[j][i] = matrix[i][j];
			matrix[i][j] = temp;
		}
	}
	
	PrintMatrix(matrix);
	// rotate across vertical
/*	0,0 -> 0,2
	1,0 -> 1,2
	2,0 -> 2,2
*/
	for (int j = 0; j < n/2; j++) {
		for (int i = 0; i < n; i++) {
			temp = matrix[i][n-j-1];
			matrix[i][n-j-1] = matrix[i][j];
			matrix[i][j] = temp;
		}
	}
	PrintMatrix(matrix);
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


TreeNode *TrimBST1(TreeNode *root, int min, int max) {

	if (root == nullptr)
		return nullptr;

	if ((root->_data >= min) && (root->_data <= max)) {
		root->left = TrimBST1(root->left, min, root->_data);
		root->right = TrimBST1(root->right, root->_data, max);
		return root;
	}

	else if (root->_data < min) {

/*		TreeNode *temp = nullptr;
		temp = root->right;
		delete root;
		return temp;
		*/
		return TrimBST1(root->right, min, max);
	}
	else {
/*		TreeNode *temp = nullptr;
		temp = root->left;
		delete root;
		return temp;
		*/
		return TrimBST1(root->left, min, max);
	}

}

/****** 
Examples:
       8
   6      10
 4   5  9    12
min, max = [5,9]
      8
   6     9
     5      
*******/

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

/*
Java solution using pre-order technique

class Solution {
	public TreeNode trimTree(TreeNode node, int min, int max) {
		if (node == null) { return null; }
if (node.val < min) {
	return executeTreeTrim(node.right, min, max);
}
if (node.val > max ) {
	return executeTreeTrim(node.left, min, max);
}
		node.left = executeTreeTrim(node.left, min, max);
		node.right = executeTreeTrim(node.right, min, max);
		return node;
	}
}
*/

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

// Implement data structure Map storing pairs of integers (key, value) and define 
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
	int pathsize = (int)paths.size();
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


/* perform zigzag traversal of a given binary tree
             1
		  2      3
        4   5  6  7
 This will result in 1, 2, 3, 7, 6, 5, 4
 */
void ZigZagTraversal(TreeNode *root) {
	if (root == nullptr)
		return;

	// use two stacks to store data, one for L->R, and another for R->L
	stack<TreeNode *>ltr;
	stack<TreeNode *>rtl;

	rtl.push(root);
      
	while (!ltr.empty() || !rtl.empty()) {

		TreeNode *tn = nullptr;

		while (!rtl.empty())
		{
			tn = rtl.top();
			cout << tn->_data << endl;

			if (tn->right)
				ltr.push(tn->right);
			if (tn->left)
				ltr.push(tn->left);

			rtl.pop();
		}

		while (!ltr.empty()) 
		{
			tn = ltr.top();
			cout << tn->_data << endl;

			if (tn->left)
				rtl.push(tn->left);
			if (tn->right)
				rtl.push(tn->right);

			ltr.pop();
		}

	} // while

}

/* perform zigzag traversal of a given binary tree
1
2      3
4   5  6  7
This will result in 1, 2, 3, 7, 6, 5, 4
*/
vector<vector<int>> ZigZagTraversalLeetCode(TreeNode *root) {

	vector<vector<int>> output;

	if (root == nullptr)
		return output;

	// use two stacks to store data, one for L->R, and another for R->L
	stack<TreeNode *>ltr;
	stack<TreeNode *>rtl;

	ltr.push(root);

	while (!ltr.empty() || !rtl.empty()) {

		TreeNode *tn = nullptr;
		vector<int>line;

		while (!ltr.empty())
		{
			tn = ltr.top();
			line.push_back(tn->_data);

			if (tn->left)
				rtl.push(tn->left);
			if (tn->right)
				rtl.push(tn->right);

			ltr.pop();
		}

		if (!line.empty()) {
			output.push_back(line);
			line.clear();
		}

		while (!rtl.empty())
		{
			tn = rtl.top();
			line.push_back(tn->_data);
			if (tn->right)
				ltr.push(tn->right);
			if (tn->left)
				ltr.push(tn->left);
			rtl.pop();
		}

		if (!line.empty()) {
			output.push_back(line);
			line.clear();
		}

	} // while
	return output;
}


template <typename Key, typename Value> 
class Hashnode {
public:
	Key key;
	Value val;
	Hashnode *next;
	Hashnode() { next = nullptr; }
	Hashnode(const Key &k, const Value &v) { 
		key = k; 
		val = v; 
		next = nullptr;
	}
};

// design hashtable using arrays
template <typename Key, typename Value> 
class Hashtable {

public:
	void put(Key k, Value v);
	Value get(Key k);
	bool isEmpty() { return (this.size() == 0); }

private:
	std::vector <Hashnode<Key,Value> *> table;
	int size() { return table.size(); }
	size_t hash(Key k) { 
		std::hash<Key> hsh;
		return (hsh(k)) % table.size();
	}
};

template <class Key, class Value> void Hashtable<Key, Value>::put(Key k, Value v)
{
	size_t index = hash(k);
	if (index > table.size())
		table.resize(index + 1);
	if (table[index] == nullptr) {
		table[index] = new Hashnode<Key, Value>(k,v);
	}
	else {
		Hashnode<Key,Value> *temp = table[index];
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new Hashnode<Key,Value>(k, v);
	}
}

template <class Key, class Value> Value Hashtable<Key, Value>::get(Key k) 
{
	// check if exists
	int index = hash(k);
    
	if (index > this.size()) {
		return null;
	}

	if (table[index] != nullptr) {
		if (table[index].key == k) {
			return table[index].val;
		}
		else {
			Hashnode *temp = table[index];
			while (temp->next) {
				if (table[index].key == k) {
					return table[index].val;
				}
				temp = temp->next;
			}
			// did not find key
			return null;
		}
	}
	else
		return null;
}


// design hashtable using static arrays


// implement queue using stacks

template <class A_Type> class MyQueue {

public:
	void enqueue(A_Type item); // inserts element at back of queue
	A_Type dequeue(); // retrieve remove element at the front
	int size(); // return size of queue
	bool isEmpty();

private:
	stack<A_Type>input;
	stack<A_Type>output;

};

template <class A_Type> bool MyQueue<A_Type>::isEmpty()
{
	return ((input.empty()) && (output.empty()));
}

template <class A_Type> int MyQueue<A_Type>::size()
{
	return (input.size() + output.size());
}

template <class A_Type> void MyQueue<A_Type>::enqueue(A_Type item)
{
	input.push(item);
}

// FIFO, so first item that came in will be dequeued
template <class A_Type> A_Type MyQueue<A_Type>::dequeue()
{
	A_Type item;
	if (!output.empty()) {
		item = output.top();
		output.pop();
		return item;
	}

	// return an empty object of type A_Type to avoid runtime error
	if (input.empty())
		return A_Type();

	// pop all items from input stack and push 
	while (!input.empty()) {
		item = input.top();
		input.pop();
		output.push(item);
	}

	item = output.top();
	output.pop();
	return item;

}

// first find nth last node, one pointer will be at the end, and the other will be at the nth last node
LinkedListNode* RemoveNthLastNode(LinkedListNode *head, int n) {

	if ((head == nullptr) || (head->next == nullptr))
		return nullptr;
	
	LinkedListNode *prev = head;
	LinkedListNode *curr = head;
	LinkedListNode *last = head;

	// forward the last pointer n steps forward
	for (int i = 1; i < n; i++) {
		last = last->next;
	}

	// n > size of list
	if (last == nullptr)
		return nullptr;

	// n = size of list
	if (last->next == nullptr) {
		curr = curr->next;
		delete prev;
		return curr;
	}

	// move both pointers forward at the same time	
	while (last->next != nullptr) {
		prev = curr; // cache prev to be the pointer to the node before curr
		curr = curr->next;
		last = last->next;	
	}

	prev->next = curr->next;
	delete curr;

	return head;
}

LinkedListNode* mergeTwoLists(LinkedListNode *l1, LinkedListNode *l2) {

	if ((l1 == nullptr) && (l2 == nullptr))
		return nullptr;
	if (l1 == nullptr)
		return l2;
	else if (l2 == nullptr)
		return l1;

	LinkedListNode *head = nullptr;
	LinkedListNode *currl1 = l1;
	LinkedListNode *currl2 = l2;

	//determine head pointer
	if ((l1->_val) <= (l2->_val))
		head = l1;
	if ((l2->_val) < (l1->_val))
		head = l2;
	// duplicate vals?


	while (currl1 && currl2) {
		LinkedListNode *temp = nullptr;

		while (currl1->_val <= currl2->_val)
		{
			if (currl1->next == nullptr) {
				currl1->next = currl2;
				currl1 = nullptr;
				return head;
			}
			if (currl1->next->_val <= currl2->_val) {
				currl1 = currl1->next;
			}
			else {
				temp = currl1->next;
				currl1->next = currl2;
				currl1 = temp;
				break;
			}
		} // while

		while (currl2->_val <= currl1->_val)
		{
			if (currl2->next == nullptr) {
				currl2->next = currl1;
				currl2 = nullptr;
				return head;
			}
			if (currl2->next->_val <= currl1->_val) {
				currl2 = currl2->next;
			}
			else {
				temp = currl2->next;
				currl2->next = currl1;
				currl2 = temp;
				break;
			}
		} // while
	} // while
	return head;
}

/*


*/

// abstract class just for the fun of it 
class GameBoard {
public:
	virtual int TakeTurn() = 0;
};

class Player {
private:
	int playerId;
	vector <Player> friendList;
public:
	// TODO: do not allow users to set 0 as that is reserved
	Player(int i) {
		playerId = i; 
	}
	virtual int GetPlayerId() const {
		return playerId;
	}
	virtual bool isFriend(const Player player) {
		for (auto i = friendList.begin(); i != friendList.end(); i++) {
			if ((*i).GetPlayerId() == player.GetPlayerId()) {
				return true;
			}
		} // for
		return false;
	}
};


/* given a compressed 
3[ab4[xyz]c]4[ab]c
output to a string or to standard
*/
// only works for non recursive cases
void Decompress(const string input, string &output) {

	int len = (int)input.length();
	int count = 0;

	while (count < len) {
		// check to see if number
		if (isdigit(input[count])) {   
			int startingindex = count;
			int intlen = 1;
			while (isdigit(input[count])) {
				intlen++;
				count++;
			}
			int num = atoi((input.substr(startingindex,intlen)).c_str());
			count++;  

			int begin = count;

			// skip to end of ']'
			while (input[count] != ']') {
				count++;
			}
	         
			for (int j = 0; j < num; j++) {
				for (int i = begin; i < count; i++) {
					output += input[i];
				}
			}
			count++;
		}
		else{
			output += input[count];
			count++;
		}
	}
}

// partially working implementation, does not work for deeply nested case
// TODO: fix this
// another method is to use two stacks as per here: (one for integers and another for chars)
// http://www.geeksforgeeks.org/decode-string-recursively-encoded-count-followed-substring/
void DecompressRec( const string input, string &output) {

	int len = (int)input.length();
	int count = 0;

	while (count < len) {
		// check to see if number
		if (isdigit(input[count])) {
			int startingindex = count;
			int intlen = 1;
			while (isdigit(input[count])) {
				intlen++;
				count++;
			}
			int num = atoi((input.substr(startingindex, intlen)).c_str());
			count++;

			int begin = count;
			string buffer;

			// skip to end of ']'
			while (input[count] != ']') {
				if (!isdigit(input[count])) {
					buffer += input[count];
					count++;
			    }
				if (isdigit(input[count])) { 
                    int end = (int) input.find_first_of(']'); 
					// recursively call Decompress. 
					DecompressRec(input.substr(count, end - count + 1),output);
					buffer += output;
					output.clear();
					count = end + 1;
				}
			}

			for (int j = 0; j < num; j++) {
				output += buffer;
			}
			buffer.clear();
			count++;
		}
		else {
			output += input[count];
			count++;
		}
	}
}

class TicTacToeBoard : GameBoard {
private:
	vector<vector<int>>board;
	int dim;
public:
	int TakeTurn() { return 0; }
	bool InitializeBoard(int dimension) {
		dim = dimension;
		// take the perf hit of allocating board up-front with default values
		for (int i = 0; i < dimension; i++) {
			board[i].resize(dimension-1, 0);
		}
		return true;
	}
	//return 0 if no winner - we should probably change to another system later
	int CalculateWinner() {
		// special case is board is only one square
		if (dim == 1)
			return board[0][0];
	
		// O(n^2) solution
		// iterate through rows and columns + diagonals for winner

		bool winner = true;
		int currplayer = 0;

		//check rows
		for (int i = 0; i < dim; i++) {
			currplayer = board[i][0];
			winner = true;
			for (int j = 1; j < dim; j++) {
				if (board[i][j] != currplayer)
					winner = false;
			}
			if (winner) return currplayer;
		}

		//check columns
		for (int j = 0; j < dim; j++) {
			currplayer = board[0][j];
			winner = true;
			for (int i = 1; i < dim; i++) {
				if (board[i][j] != currplayer)
					winner = false;
			}
			if (winner) return currplayer;
		}

		//check diagonals
		currplayer = board[0][0];
		winner = true;
		for (int i = 1; i < dim; i++) {
			if (board[i][i] != currplayer)
				winner = false;
		}
		if (winner) return currplayer;
		
		currplayer = board[0][dim-1];
		winner = true;
		for (int i = 1; i < dim; i++) {
			if (board[i][dim-i-1] != currplayer)
				winner = false;
		}
		if (winner) return currplayer;

		return 0;
	}
};

class TicTacToeGame {
private: 
	TicTacToeBoard *gameboard;
protected:
	
public:
	TicTacToeGame(int boardsize) {
		gameboard = new TicTacToeBoard();
		gameboard->InitializeBoard(boardsize);
	}
	int WhoWon(){
		return gameboard->CalculateWinner();
	}

};

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

/* Test Code for substr

	string word = "ATATAS";
	string sub = "AS";
	cout << "Is this: " << sub << " a substring of: " << word << " ?" << endl;
	cout << "Answer: " << substrTest(sub, word) << endl;
   
*/

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
/*
	MyQueue<int>q;

	q.enqueue(1);
	q.enqueue(2);
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	q.enqueue(3);
	q.enqueue(4);
	cout << q.dequeue() << endl;
	cout << q.dequeue() << endl;
	q.enqueue(5);
	cout << q.dequeue() << endl;
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
//	cout << "Diameter of binary tree: " << DiameterBinTreeDriver(root) << endl;

/*	ZigZagTraversal(root);

	vector< vector<int>>output;
	output = ZigZagTraversalLeetCode(root);

	for (auto it = output.begin(); it != output.end(); ++it) {		
		for (auto itinner = it->begin(); itinner != it->end(); ++itinner) 
			std::cout << ' ' << *itinner;	
	}
	cout << endl;
*/
//	root = deleteNode(root, 5);
//	Traversals(root, Inorder);

/*
	int curr = 0;
	FindMthNodeinBST(root, 2, &curr);
	curr = 0;
	FindMthNodeinBST(root, 9, &curr);
*/
	
	int min = 8;
	int max = 17;
/*	cout << "Min: " << min << "Max: " << max << endl;
	TreeNode *tree = TrimBST1(root, min, max);
	Traversals(tree, Inorder);
	
    min = 1;
	max = 2;
	cout << "Min: " << min << "Max: " << max << endl;
	TreeNode *tree1 = TrimBST1(root, min, max);
	if (tree1 == nullptr)
		cout << "Empty Tree!" << endl;
	Traversals(tree1, Inorder);
	
	min = 5;
	max = 26;
	cout << "Min: " << min << "Max: " << max << endl;
	TreeNode *tree2 = TrimBST1(root, min, max);
	if (tree2 == nullptr)
		cout << "Empty Tree!" << endl;
	Traversals(tree2, Inorder);
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

/*
// test code for isanagram
	bool flag =	isanagram("a", "a");
	(flag ? cout << "Anagram!" << endl : cout << "Not an anagram!" << endl);
*/
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

/*
    LinkedListNode *head = new LinkedListNode(1);
	LinkedListNode *curr = head;

	for (int i = 2; i <= 10; i++) {
		curr->next = new LinkedListNode(i);
		curr = curr->next;
	}

	curr = head;
	while (curr) {
		cout << curr->_val << endl;
		curr = curr->next;
	}
	cout << "========================" << endl;

	curr = RemoveNthLastNode(head, 2);

	// print list

	while (curr) {
		cout << curr->_val << endl;
		curr = curr->next;
	}
*/

/*
	Hashtable<std::string, std::string>ht;

	ht.put("Test", "One");
*/

/*
LinkedListNode *l1 = new LinkedListNode(1);
l1->next = new LinkedListNode(5);
l1->next->next = new LinkedListNode(100);
l1->next->next->next = nullptr;

LinkedListNode *l2 = new LinkedListNode(2);
l2->next = new LinkedListNode(5);
l2->next->next = new LinkedListNode(9);
l1->next->next->next = nullptr;


LinkedListNode *curr = mergeTwoLists(l1,l2);
while (curr) {
	cout << curr->_val << endl;
	curr = curr->next;
}
*/

/*
for (int i = 0; i <= 100; i++) {
	if (isPrime(i)) cout << "Prime number: " << i << endl;
}

bool *primes;
size_t size;
primes = returnPrimes(100, size);
cout << "====================" << endl;

for (int i = 0; i < size; i++) {
	if (primes[i]) cout << "Prime number: " << i << endl;
}
delete [] primes;
*/

/*cout << gcdfast(2336, 1314) << endl; */
/*
vector<vector<int>> mat1 = { {1,2,3},{4,5,6},{7,8,9} };
MatrixOps *m = new MatrixOps();
m->PrintMatrix(mat1);
m->FlipAroundLeftDiagonal(mat1);
m->PrintMatrix(mat1);

vector<vector<int>> mat2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
m->PrintMatrix(mat2);
m->FlipAroundLeftDiagonal(mat2);
m->PrintMatrix(mat2);
*/
//RotateMatrix(mat2);


//TicTacToeGame *tictac = new TicTacToeGame(5);
//cout << tictac->WhoWon() << endl;

//string output;
//DecompressRec("2[2[cd]2[xy]]", output);
//DecompressRec("2[ab2[xy]2[ab]]", output);
//DecompressRec("3[b2[ca]]", output);
//DecompressRec("1[1[x]]", output);
//cout << output << endl;

/*
vector<int>list = { 1,2,100, 101,102 };
bool b = BinarySearch(list, 0, (int)list.size() - 1,122);
if (b)  
   cout << "found" << endl;
else
   cout << "not found" << endl;
*/

/*
vector <string> tokens;
mystrtok("-----This -is a very long stress test Booyah!!---------","- ,", tokens);

for (int i = 0; i < tokens.size(); ++i) {
	cout << tokens[i] << endl;
}

tokens.clear();

set<char>delim = { ' ','-',',' };
mystrtok1("-----This -is a very long stress test Booyah!!---------", delim, tokens);

for (int i = 0; i < tokens.size(); ++i) {
	cout << tokens[i] << endl;
}
*/

TreeNode *root1 = new TreeNode(99);
root1->left = new TreeNode(84);
root1->left->left = new TreeNode(27);
root1->left->left->left = new TreeNode(1);
root1->left->left->right = new TreeNode(53);

cout << minDiffInBST(root1) << endl;

};

