// NewC++Stuff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace::std;
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <string>

/* implement of s stack using a queue
Implement the following operations of a stack using queues.
push(x) --Push element x onto stack.
pop() --Removes the element on top of the stack.
top() --Get the top element.
empty() --Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, peek / pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively.You may simulate a queue by using a list or deque(double - ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid(for example, no pop or top operations will be called on an empty stack).
*/

template <class T> class myQueue;

template <class T>
class myStack {

private:
	myQueue<T> stack;

public:

	myStack() {}

	//insert at the end of the queue, so that it will be the first to be popped like a stack
	void push(T val) {
		stack.push_back(val);	
	}

	void pop() {
		if (!this.empty())
			stack.pop_back();
	}

	T top() {
		if (!this.empty()) 
			return stack.peek_back();
	}

	bool empty(){
		return (stack.size() == 0);
	}	
};


// implementation of a queue
template<class T>
class myQueue {

private:
	std::list<T> Queue;

public:

	myQueue() {
	}

	void push_back(T val) {
		Queue.push_back(val);
	}

	void pop_front() {
		Queue.pop_front();
	}

	void pop_back() {
		Queue.pop_back();
	}

	T peek_front() {
		return Queue.front();
	}

	T peek_back() {
		return Queue.back();
	}

	int size() {
		return Queue.size(); 
	}

};


// Given an array of integers, replace every element with the next greatest element
// (greatest element on the right side) in the array.Since there is no element next 
// to the last element, replace it with - 1. For example, 
// if the array is{ 16, 17, 4, 3, 5, 2 }, 
// then it should be modified to{ 17, 5, 5, 5, 2, -1 }.


#define STACKSIZE 100


class BTNode {

public:
	BTNode *left;
	BTNode *right;
	int _data;
	BTNode() {
		left = NULL;
		right = NULL;
	}
	BTNode(int i) {
		left = NULL;
		right = NULL;
		_data = i;
	}
};

// traversal
class TreeTraversal {

protected:
	virtual void VisitNode(BTNode *node);
public:
	TreeTraversal() {};
	enum Traversal { PreOrder, PostOrder, InOrder };
	virtual void PrintTraversal(BTNode *node, Traversal traversaltype);
};


void TreeTraversal::VisitNode(BTNode *node){
	cout << "Node visited with value: " << node->_data << endl;
}

void TreeTraversal::PrintTraversal(BTNode *node, Traversal traversaltype) {

	if (node != NULL) {

		switch (traversaltype) {
		case Traversal::InOrder:
			PrintTraversal(node->left, traversaltype);
			VisitNode(node);
			PrintTraversal(node->right, traversaltype);
			break;
		case Traversal::PreOrder:
			VisitNode(node);
			PrintTraversal(node->left, traversaltype);
			PrintTraversal(node->right, traversaltype);
			break;
		case Traversal::PostOrder:
			PrintTraversal(node->left, traversaltype);
			PrintTraversal(node->right, traversaltype);
			VisitNode(node);
			break;
		default:
			cout << "Invalid traversal specified" << endl;
		}

	}
}


class Node{
public:
	Node() {
		next = NULL;
		data = 0;
	}
	Node(int i) {
		next = NULL;
		data = i;
	}
	Node *next;
	int data;
};


// given singly linked list, reverse and point to new header
Node *reverselinkedlist(Node *head) {
	if (head == NULL)
		return NULL;

	Node *prev = head;
	Node *curr = head->next;
	prev->next = NULL;
	Node *fwd = curr->next;

	while (fwd != NULL) {
		curr->next = prev;
		prev = curr;
		curr = fwd;
		fwd = fwd->next;
	}

	curr->next = prev;
	// curr is pointing to new head
	return curr;
}



//empty stack = -1
template<class T>
class stack
{
public:
	stack() { 
		top = -1; 
		for (int i = 0; i < STACKSIZE; i++)
			items[i] = 0;
	}

	T top;
	T items[STACKSIZE];

	// initialize stack



	void push(T x) {
		if (top != STACKSIZE - 1)
		{	
			top += 1;
			items[top] = x;
		}
	}

	bool isEmpty(){
		if (top == -1) return true; else return false;
	}

	T pop() {
		if (isEmpty()) return -1;
		T temp = items[top];
		top -= 1;
		return temp;
	}
};


void NGEwithstack(int arr[], int n) {

	stack<int> st;

	// push the first element on the stack

	int first = arr[0];

	st.push(first);

	int next;
	int element;

	for (int i = 1; i < n; i++) {

		next = arr[i];

		if (st.isEmpty() == false) {

			element = st.pop();

			while (element < next) {

				// print the element
				cout << "Element: " << element << " NGE: " << next << endl;

				if (st.isEmpty())
					break;
				element = st.pop();
			} // while 

			if (element > next)
				st.push(element);

		} // while 

		// push the next element
		st.push(next);
	}

	while (st.isEmpty() == false) {
		element = st.pop();
		next = -1;
		cout << " Element: " << element << " Next:" << next << endl;
	}

	}


// arr is integer array
// n is the size of the array
void NGE(int arr[], int n) {

	for (int i = 0; i < n; ++i) {
		
		int max = -1;

		for (int j = i; j < n; ++j) {
			if (arr[j] > arr[i]) {
				max = arr[j];
			}
		}

		cout << max << endl;

	}// for
}


namespace {
	int test = 0;

}


class Directory;

class Entry {
protected:
	void *_crchash;
	string _date;
	string _lastaccessed;
	Directory *_parent;
	string _name;
public:
	Entry(string date, string lastaccessed, Directory *parent, string name);
	virtual int getSize() = 0;
	virtual string getFullPath();
};


// directories contain multiple files and other directories
class Directory : public Entry {
private:
	vector<Entry> entries;
};

Entry::Entry(string date, string lastaccessed, Directory *parent, string name) {
		_parent = parent;
}

string Entry::getFullPath() {
	if (_parent == nullptr)
	{
		return _name;
	}
	else {
		string temp = _parent->getFullPath();
		return (temp + "/" + _name);
	}
}

class File : Entry{
private:
	void *_contents;
	int _size;
public:
	
	File(void *contents, int size, Directory *dir) : Entry("","",dir,""){
		_size = size;
	}
	void * GetContents() { return _contents;}

};


bool odd(int i) { 
	if (i % 2)
		return true;
	else
		return false;
}


template <class T>
class EasyStack {

public:
	vector <T> stack;

	EasyStack() {
	}

	void Push(T item) {
		auto i = stack.begin();
		stack.insert(i,item);
	}

	T Pop() {
		T temp = stack[0];
		stack.erase(stack.begin());
		return temp;
	}

	void Print(){
		for (auto i = stack.begin(); i != stack.end(); i++)
			cout << "Stack: " << *i << endl;
	}

};



template <class T>
class Stack {
	protected:
		T* stack;
		// keep top of stack at stack[0]
		int currentsize; // size of array

		Stack() {
			stack = NULL;
			currentsize = 0;
		}

		T& operator[] (const long index)
		{
			return Get[index];
		}

		T& Get(const long index) {
			return stack[index];
		}

		Stack(int initialsize) {
			stack = new T[initialsize];
			currentsize = initialsize;
		}

		~Stack() {
			if (stack != NULL)
				delete[] stack;
		}

		void Insert(T val) {
			// shift everything to the right by 1
			
			T* newMem = new T[currentsize+1];
			
			if (stack != nullptr)
			{
				memcpy(newMem + sizeof(T), stack, currentsize * sizeof(T));
				delete[] stack;
			}
			
			stack = newMem;
			currentsize += 1;
			stack[0] = val;
		}

		void print() {



		}

	public:
		void Push (T item) {
			// shift everything forward
			Insert(T);
		}

		T Pop() {
			return stack(0);
		}

};


template <typename T>
class templatetype {
	templatetype() {}
};

template <class T> 
class templateclass {
	T values[];
	templateclass() {}
};

template <class T>
class SP {
protected:
	T *ref;
	unsigned *refcount;

public:
	SP(T *ptr) {
		ref = ptr;
		ref_count - (unsigned *)malloc(sizeof(unsigned));
		*ref_count = 1;
	}	

	SP(SP<T>& sptr) {
		ref = sptr.ref;
		ref_count = sptr.refcount;
		++(*ref_count);	
	}

	SP<T> & operator=(SP<T> &sptr) {
		if (this == &sptr) return *this;

		if (*ref_count > 0) {
			remove();
		}
		ref = sptr.ref;
		ref_count = sptr.refcount;
		++(*ref_count);
		return *this;
	}

//	~SP(SP<T>sptr) {}

	SP() { 
		ref = NULL;
		refcount = 0;
	}
	~SP() {
	//	remove();
	}

	T getvalue() {
		return *ref;
	}

	void* operator new(size_t) {
		refcount++;
		return new T[size_t];
	}
	void operator delete(void* del) {
		refcount--;
		delete del;
	}
};

template <>
class templateclass <char> {


};

int _tmain(int argc, _TCHAR* argv[])
{

	TreeTraversal *tt = new TreeTraversal();
	
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

		BTNode *root = new BTNode(6);
		root->left = new BTNode(4);
		root->right = new BTNode(7);
		root->right->right = new BTNode(8);
		root->right->left = new BTNode(9);
		root->left->left = new BTNode(3);
		root->left->right = new BTNode(5);
	
		cout << "InOrder Traversal" << endl;
		tt->PrintTraversal(root, TreeTraversal::InOrder);

		cout << "PreOrder Traversal" << endl;
		tt->PrintTraversal(root, TreeTraversal::PreOrder);

		cout << "PostOrder Traversal" << endl;
		tt->PrintTraversal(root, TreeTraversal::PostOrder);

/*	SP<int*> test;

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	for (auto i = v.begin(); i != v.end(); i++) {
		cout << *i << endl;
	}

	std::map<int, int> phonebook;
	
	string one = "425";
	string two = "123";
	phonebook[1] = 1;
	phonebook[2] = 2;

	for (auto ip = phonebook.begin(); ip != phonebook.end(); ip++) {
		cout << ip-> first << "" << ip->second << endl;
	}

	auto find = phonebook.find(1);
	cout << find->first << " " << find->second << endl;
	find = phonebook.find(3);
//	cout << find->first << " " << find->second << endl;

	cout << phonebook[1] << endl;


	cout << "List!!" << endl;

	std::list<int> myList;

	myList.push_back(1);
	myList.push_front(4);
	myList.push_front(5);
	myList.push_front(6);

	cout << "Contents of list" << endl;
	for (auto ip = myList.begin(); ip != myList.end(); ip++) {
		cout << *ip << endl;
	}

	auto i = find_if(myList.begin(), myList.end(), odd);

	while (i != myList.end())
	{
		std::cout << *i << " ";
		i= find_if(++i, myList.end(), odd);
	}
	
//	cout << *i << endl;

	EasyStack<int>es;

	es.Push(1);
	es.Push(2);
	es.Push(3);

	es.Pop();
	cout << endl;
//	es.Print();

	std::pair<int, int> p1;

	p1.first = 1;
	p1.second = 2;

//	cout << "First: " << p1.first << endl;
//	cout << "Second: " << p1.second << endl;
	
	int arr[] = { 6,5,3,4,2,1};
	int size = sizeof(arr) / sizeof(arr[0]);  
//	NGE(arr, size);
	cout << "================================" << endl;
	NGEwithstack(arr, size);
	
	cout << sizeof(void *) << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(char) << endl;
	cout << sizeof(char *) << endl;
	cout << sizeof(int *) << endl;
	cout << sizeof(string) << endl;
	
	Node *head = new Node(0);
	Node *curr = head;

	for (int i = 1; i < 10; i++) {
		curr->next = new Node(i);
		curr = curr->next;	
	}

	for (Node *t = head; t!=NULL; t=t->next) {
		cout << "Node: " << t->data << endl;
	}

	Node *temp = reverselinkedlist(head);

	while (temp) {
		cout << "Node" << temp->data << endl;
		temp = temp->next;
	}
*/	
	return 0;

}

