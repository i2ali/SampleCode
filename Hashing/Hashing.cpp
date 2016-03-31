// Hashing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>

using namespace::std;

// Key, Value


// basic hashtable of name - phone number
// key = name
// value = phone number

// return a map of pairs
void FindallSums(vector<int> *list, int sum) {

	unordered_map<int, int> hashtable;
	for (auto i = list->begin(); i != list->end(); i++) {
		int tempsum = sum - *i;
		auto j = hashtable.find(tempsum);
		if (j != hashtable.end()) {
			// add the element to the hashtable
//			hashtable.insert({ { *i, *i } });
			cout << *i << tempsum << endl;
		}
	}

}


class Node {

public:
	string _name;
	int _number;
	Node *next;
	Node(string name, int number) {
		_name = name;
		_number = number;
		next = NULL;
	}
	virtual ~Node() {
			
	}
};

class SimpleHash {
private:
	vector<Node *>phonebook;

public:

	SimpleHash() {
	
	}

	~SimpleHash() {

	}

	bool AddItem(string name, int phonenum) {

		// hash name first to see where it goes
		int index = GetHash(name);

		if ((int)phonebook.size() <= index)
			phonebook.resize(index+2);

		Node *ptr = phonebook[index];
		if (ptr == NULL)
			phonebook[index] = new Node(name, phonenum);
		else {  // we have a collision, and need to move to the end of the list

			cout << "Collision: " << name << " Phone number: " << phonenum << endl;
			while (ptr->next != NULL) {
				ptr = ptr->next;
			}
			// post: ptr->next == NULL
			ptr->next = new Node(name, phonenum);
		}
		
		return true;
	}

	bool RemoveItem(string name) {

		return true;
	}

	/* Print out phonebook */
	void PrintTable() {

		for ( auto i = phonebook.begin(); i != phonebook.end(); i++ ) {

			if (*i != NULL) {
				cout << "Name: " << (*i)->_name << " Number: " << (*i)->_number << endl;
				Node *j = (*i)->next;
				while (j) {
					cout << "    " << "Name: " << j->_name << " Number: " << j->_number << endl;
					j = j->next;
				}

			}
		}
	}

	// hash name and return an index
	int GetHash(string name) {
		int len = strlen(name.c_str()) + 1;
		return len;
	}

	int operator[] (const string name) {
		return GetItem(name);
	}

	// Given name, find associated phone number
	int GetItem(string name) {
		int index = GetHash(name);

		if (index > (int)phonebook.size())
			return -1;

		Node *ptr = phonebook[index];
		if (ptr == NULL){
			// item not found
			return -1;
		}
		else
		{
			if (ptr->_name == name) {
				return ptr->_number;
			}
			else {
				while (ptr) {
					if (ptr->_name == name)
						return ptr->_number;
					ptr = ptr->next;
				}
				// post: ptr->next == NULL
				return -1; // item was not found
			}

		}
	}

};

template <class K, class V>
class Hashlist {
public:
	K _key;
	V _value;
	Hashlist *next;
	Hashlist(K key, V value) {
		_key = key;
		_value = value;
		next = NULL;
	}
};

template <class K, class V>
class HashTable {

private:
	int Hash(int value);
	std::vector<Hashlist<K,V>*> table;
	
public:
	HashTable() {
		table.clear();
	}

	V GetItem(K);

	// hash name and return an index
	int GetHash(K key) {
		// figure out some value here
		return 0;
	}

	bool AddItem(K key, V val) {

		// hash name first to see where it goes
		int index = GetHash(key);

		if ((int)table.size() <= index)
			phonebook.resize(index + 2);

		Hashlist *ptr = table[index];
		if (ptr == NULL)
			table[index] = new Node(key, val);
		else {  // we have a collision, and need to move to the end of the list

			cout << "Collision: " << key << " Phone number: " << val << endl;
			while (ptr->next != NULL) {
				ptr = ptr->next;
			}
			// post: ptr->next == NULL
			ptr->next = new Hashlist(key, val);
		}

		return true;
	}


};


int _tmain(int argc, _TCHAR* argv[])
{

	SimpleHash *sh = new SimpleHash();
	sh->AddItem("Adam", 1);
	sh->AddItem("Brain", 2);
	sh->AddItem("Claw", 3);
	sh->AddItem("Duff", 4);
	sh->AddItem("Enough", 5);
	sh->AddItem("Enoughisenough", 5);
	sh->AddItem("Enoughtellme", 111);
	sh->AddItem("abcdefghikklmnop", 444);


	cout << sh->GetItem("Duff") << endl;

	sh->PrintTable();

	// use unordered map
	unordered_map<string, int> phonebook;

	pair<string, int> mypair;
	mypair.first = "Adam";
	mypair.second = 1;

	phonebook.insert(mypair);

	for (auto i = phonebook.begin(); i != phonebook.end(); i++) 
		cout << (*i).first << (*i).second << endl;
	return 0;
}

