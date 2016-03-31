// LinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataTypes.h"
#include <iostream>
#include <vector>

using namespace std;
/*
Given singly linked list, reverse the list and return the new head
*/

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
bool List::DeleteNode(Node *list,int field) {
	
	if (list == NULL)
		return NULL;

	// find matching field
	Node *temp = list;
	bool found = false;

	// if at head of node
	if (list->_data == field) {
		list = list->next;
		delete temp;
	}

	while (temp->next != NULL) {
		if ((temp->next)->_data == field) {
			found = true;
			Node *t1 = temp->next;
			temp->next = (temp->next)->next;
			// delete node
			delete t1;
			break;
		}
		temp = temp->next;
	}

	return found;
}


Node * FindNthLastNode(Node *list, int num) {

	if (list == NULL)
		return NULL;

	Node *start = list;
	Node *end = list;

	//move end to n nodes ahead

	for (int i = 0; i < num && end!=NULL; i++) {
		end = end->next;
	}
	if (end == NULL) return NULL;

	while (end != NULL) {
		start = start->next;
		end = end->next;
	}

	return start;

}


// detect first node that forms a list
Node *DetectCircularLoop(Node *list) {
	// use two pointers, both travelling at the same rate
	// compare pointer addresses to see if one is less than the other

	if (list == NULL)
		return NULL;

	Node *t1 = list;
	Node *t2 = list;

	// have t2 go twice as fast as t1

	while ((t2!=NULL) && (t2->next!=NULL)) {

		t1 = t1->next;
		t2 = t2->next->next;

		if (t2 == t1)
			break;
	}

	if ((t2 == NULL) || (t2->next == NULL))
		return NULL;

	t1 = list;
	while (t1 != t2) {
		t1 = t1->next;
		t2 = t2->next;
	}

	return t2;

	// no loop detected, return NULL
	return NULL;
}


Node *ReserveSinglyLinkedList(Node *list) {

	if (list == NULL)
		return NULL;

	Node *curr = list;
	Node *prev = NULL;
	Node *next = NULL;

	while (curr!= NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}






// use two pointers, one slow, another twice as first
bool DetectCycle(Node *head) {
	
	if (head == NULL) {
		return false;
	}

	Node *slow = head;
	Node *fast = head;
	
	// if they meet at some point, then we have a cycle

	while (fast && slow && fast->next) {

		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) {
			// hit a cycle
			return true;
		}

	}

	// we hit the end of the list and no cycle detected
	return false;
}

/*
int _tmain(int argc, _TCHAR* argv[])
{


	vector<int>vec = { 1, 2, 3, 4, 5 };

	for (auto i = vec.begin(); i != vec.end(); i++) {
		cout << *i << endl;
	}

	int size = vec.size();

	for (int i = 0; i < size; i++) {
		cout << vec[i] << endl;	
	}

	for (int i = 0; i < size; i++) {
		cout << vec.at(i) << endl;
	}

	for (int i = 0; i < size; i++) {
		vec.push_back(i);
	}



	/*
	List *mylist = new List(3);

	mylist->PrintList();

	Node* newhead = ReserveSinglyLinkedList(mylist->getHeadList());

	mylist->PrintList(newhead);

	delete mylist;
	delete newhead;

	List *list = new List(10);

	list->PrintList();

	Node* nthlast = FindNthLastNode(list->getHeadList(), 3);

	printf("Nth Last Node is: %i\n", nthlast->_data);

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
/*
	return 0;
}
*/
