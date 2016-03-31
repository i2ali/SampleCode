

#include "stdafx.h"


class Node {
public:
	int _data;
	Node *next;
	Node() { next = NULL; }
	Node(int data) { _data = data; next = NULL; }
};


//represents a list
class List {

private:
	Node *head;

public:
	List() {
		head = NULL;
	}

	List(int numitems) {		
		head = NULL;
		Node *temp = new Node(0);
		head = temp;
		
		for (int i = 1; i < numitems; i++) {
			temp->next = new Node(i);
			temp = temp->next;
		}

	}

	~List() {delete head; }
	Node * getHeadList(){ return head; }

	void PrintList();
	void PrintList(Node *list);

	bool DeleteNode(Node *list,int field);

	bool AddtoEndofList();
};

