// LinkedList.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "DataTypes.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace std;

void List::PrintList(){
	PrintList(this->head);
}

void List::PrintList(Node *root){
	for (Node *temp = root; temp != NULL; temp = temp->next)
	{
		printf("Node: %i\n", temp->_data);
	}
}

// find node matching node and delete it if found
// true - if found and deleted successfully
// false - if not found or not deleted successfully

Node * FindNthLastNode(Node *list, int num) {

	if (list == NULL)
		return NULL;

	Node *n1 = list;
	Node *n2 = list;

	// move n2 to num forward nodes
	for ( int i = 0; (i < num) && (n2 != NULL); ++i ) {		
		n2 = n2->next;		
	}

	if (n2 == NULL) return NULL;

	// now move both nodes at the same rate until we hit the end of the list
	for (; n2 != NULL; n1 = n1->next, n2 = n2->next) {
	}

	return n1;
}


// detect first node that forms a list
Node *DetectCircularLoop(Node *list) {
	return NULL;
}


Node *ReserveSinglyLinkedList(Node *list) {

	if (list == NULL) return NULL;

	Node *prev = list;
	Node *curr = list;
	Node *fwd = list;

	curr = prev->next;
	fwd = curr->next;
	prev->next = NULL;

	while (fwd != NULL) {
		curr->next = prev;
		prev = curr;
		curr = fwd;
		fwd = fwd->next;
	}

	curr->next = prev;
	
	return curr;

}


// use two pointers, one slow, another twice as first
bool DetectCycle(Node *head) {
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{


	vector<int>vec = { 1, 2, 3, 4, 5 };

	for (auto i = vec.begin(); i != vec.end(); i++) {
		//cout << *i << endl;
	}

	int size = vec.size();

	for (int i = 0; i < size; i++) {
		//cout << vec[i] << endl;	
	}

	for (int i = 0; i < size; i++) {
		//cout << vec.at(i) << endl;
	}

	for (int i = 0; i < size; i++) {
		vec.push_back(i);
	}

	List *mylist = new List(10);

	mylist->PrintList();

	Node* newhead = ReserveSinglyLinkedList(mylist->getHeadList());

	mylist->PrintList(newhead);

	/*
	List *list = new List(10);

	
	list->PrintList();

	Node* nthlast = FindNthLastNode(mylist->getHeadList(), 10);

	if (nthlast != NULL)
		cout << "Nth Last Node is:" << nthlast->_data << endl;
	else
		cout << "Could not find Nth Last Node" << endl;
	*/

	/*
	if (list->DeleteNode(list->getHeadList(), 5))
		printf("Deleted node successfully\n");
	else
		printf("Could not delete node \n");

	list->PrintList();

	delete nthlast;
	delete list;
	
	List *l = new List();

	Node *head = new Node(1);
	head->next = new Node(2);
	head->next->next = new Node(3);
	head->next->next->next = new Node(4);
	head->next->next->next->next = new Node(5);

	//l->PrintList(head);
		
	head->next->next->next->next->next = head->next->next;

//	Node *tmp = DetectCircularLoop(head);

	bool temp = DetectCycle(head);

	if (temp)
		cout << "Loop found" << endl;
	else 
		cout << "Not found." << endl;


	*/


	return 0;
}

