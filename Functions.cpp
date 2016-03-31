
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C RunTime Header Files
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>


// reverse string
char * ReverseString1 (const char *toreverse) {

	char *buffer = new char[strlen(toreverse)+1];
	buffer = strcpy(buffer, toreverse);

	char *Begin = buffer;
	char *End = buffer + strlen(buffer) - 1;

	char temp = '\0';

	while ( End > Begin ) {
		temp = *Begin;
		*Begin = *End;
		*End = temp;
		Begin++;
		End--;
	}
	return buffer;
}

//reverse string - another implementation
void ReverseString2 (char *toreverse) {

	char *buffer = new char[strlen(toreverse)+1];
	buffer = strcpy(buffer, toreverse);

	char *Begin = buffer;
	char *End = buffer + strlen(buffer) - 1;

	char temp = '\0';

	while ( End > Begin ) {
		temp = *Begin;
		*Begin = *End;
		*End = temp;
		Begin++;
		End--;
	}

	strncpy(toreverse,buffer,strlen(toreverse)+1);
}

/*
Example 2:  Write function to compute Nth fibonacci number: 
Java and C/C++: 
    static long fib(int n) {        return n <= 1 ? n : fib(n-1) + fib(n-2);
*/

long fib(long n) {
	if ( n <= 1 ) 
		return n;
	else
		return (fib (n-1) + fib (n-2));
}

/*
Example 3:  Print out the grade-school multiplication table up to 12x12 
*/

void MultiplicationTable(int factor) {

	for (int i = 1; i <= factor; i++)
	{
		for (int j=1; j <= factor; j++)
		{
			printf ("%4d",i*j);
		}
		printf ("\n");
	}
}


/* Write function to print the odd numbers from 1 to 99. */

void PrintOddNumbers(int odd) {
	for (int i=1; i<= odd; i += 2)
		printf("%4d",i);

	printf ("\n");

}


//Example 6:  Find the largest int value in an int array. 

int FindLargestValue(const int *arr, int size)
{
	int max = 0;

	for (int i = 0; i < size; ++i  ) {
		if (arr[i] > max)
			max = arr[i];
	}

	return max;

}


class A {
public:
	A() {}
	A(int a) {}
};

class B: public A {
	B() {}
	B(int b) {}

};

class C: public A {
	explicit C() {}
	explicit C(int c) {}

};

// Binary tree node : binary tree has one or two more nodes
class BSTNode {
public:
	BSTNode(int field) {
		_info = field;
		_left = nullptr;
		_right = nullptr;
	}
	int _info;
	BSTNode *_left;
	BSTNode *_right;
};




//represents Node
class Node {
public:
	Node(int field) {
		_info = field;
		_next = nullptr;
	}

	int _info;
	Node *_next;
};






class List {

public:

	List() {
		_head = nullptr;
	}

	// cleanup list

	~List(void) {	
		delete _head;
	}

	bool RemoveNodeAtHead() {

/*		Node *newnode = new Node(value);

		Node *temp= _head;	
		_head = newnode;
		newnode->_next = temp;
*/
		return true;
	};

	bool RemoveNode() {

	}

	virtual void Print() {

		Node *temp = nullptr;
		int i = 0;

		for (temp = _head; temp != nullptr; temp = temp->_next) {
			printf("Node %d: With Value: %d\n",++i, temp->_info);
		}
	};

	// assume node has been allocated and we want to add at end of list
	bool AddatFront(int value) {

		Node *newnode = new Node(value);
		Node *temp= _head;	
		_head = newnode;
		newnode->_next = temp;

		return true;
	};

	// returns pointer to end of list
    Node * GotoEnd() {

		Node *temp = nullptr;

		for ( temp = _head; temp != nullptr; temp = temp->_next) {
			if (temp -> _next == nullptr) {
				// we are at the end of the list
				return temp;
			}
		}
		return temp;
	}

	inline bool IsEmpty() {
		if (_head == nullptr) return true;
		else  return false;
	}


	bool AddatBack(int value) {

		Node *newnode = nullptr;
		Node *end = nullptr;

		// we have an empty list
		if (_head==nullptr)
			return AddatFront(value);

		end = GotoEnd();

		if (end == nullptr) return false;
		newnode = new Node(value);

		end->_next = newnode;

		return true;

	}

protected:
	Node *_head; // pointer to the head of the list
};



class Stack: public List {

public:
	Stack():List() {};

	bool Push(int val);

	int Pop();

	virtual void Print();
};


void Stack::Print() {
	printf("Stack\n");
	List::Print();
}

bool Stack::Push(int val) {

	return true;
}

// return head of list
int Stack::Pop() {

	if (this->IsEmpty())
		return -1;
	
	

	return _head->_info;

	return 0;
}

BSTNode * ConstructBSTTree(BSTNode *head, int size) {
	


}

Node * FindNthLastNode(Node *head, int nth) {

	if (head == nullptr)
		return nullptr;
	
	Node *n1 = head;
	Node *n2 = head;

	// go forward n nodes
	
	for (int i = 0; i < nth; i++ ) {
		if (n2 == nullptr)
			return new Node(-1);
		n2 = n2 ->_next;
	}	

	// move both pointers at the same rate

	for (; n2 != nullptr; n2=n2->_next) {
		n1 = n1->_next;
	}	

	return n1;
}


Node * ReverseSinglyLinkedList(Node *head) {

	if (head == nullptr) return nullptr;

	Node *cur = head ->_next;
	Node *prev = head;
	Node *start = head->_next;
	
	prev->_next = nullptr;
	
	while (cur->_next != nullptr) {
		cur = cur ->_next;
		start->_next = prev;
		prev = start;
		start = cur;
	}

	cur->_next = prev;

	return start;

} // void Reverse ...


bool IsPalindrome(const char *str)
{
	if (str == nullptr) return false;

    int len = strlen(str);

    for(int i=0, j=len-1; i<j; i++, j--)
    {
        if(str[i] != str[j])
            return false;
    }
   return true;
}

// reverse a string
void reverse(char str[], int beginIndex, int endIndex)
{
char temp =' ';

while(beginIndex < endIndex) // keep swaping characters as long as
                               // begin index is less than end index
  {
     // swap the characters
     temp = str[beginIndex]; 
     str[beginIndex] = str[endIndex];
     str[endIndex] = temp;

     beginIndex++; //increment the begin index
     endIndex--; //decrememnt the end index
  }
}

void reverse_words(char str[])
{
  int len = strlen(str);
  reverse(str, 0, len-1);
  int currentIndex = 0;
  int wordBeginIndex = 0;
  int wordEndIndex = -1;

  while(str[currentIndex])
  {
     if(str[currentIndex + 1] == ' '  // if we are at the word
        || str[currentIndex + 1] == '\0') // boundary or end of the string
     {
        wordEndIndex = currentIndex;
        reverse(str, wordBeginIndex, wordEndIndex);
        wordBeginIndex = currentIndex + 2;
     }
     currentIndex++;
  }
}



// convert string to int
int myatoi(char *str, int base)
{
	if (str == nullptr) return -1;
	long sum = 0;
	char cur = ' ';
	int index = 0;

	while(str[index] == ' ') index++;

	int len = strlen(str) -1 - index;


	for (int i = index; i< strlen(str); i++) {
		cur = str[i];
		if(cur >= '0' && cur <= '9') {
			sum +=  (pow((double)base,len--) * (str[i] - '0'));	
		}
	}


	return sum;
}


void b(LPVOID clientData) {
	A *a = new A();
	void *temp = clientData;
//	a = (A *)temp;
	void *p = static_cast<void*>(a);



}


// reverses string within a start and end range
void reversestring(char str[], int start, int end) {
	
	char temp = ' ';
	while (end > start) {
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

// reverses string within a start and end range
void reversestring(char str[]) {	
	char temp = ' ';
	int len = strlen(str);

	reversestring(str,0,len+1);

}




void main() {

	char temp[] = "  101111";

//	printf("Palindrome for %s: %s\n", temp,((IsPalindrome(temp))? "true":"false"));

//	printf("Reversed string: Original: %s \n",temp); 	

//	reverse_words(temp);

//	printf("Reversed string: Reversed: %s \n",temp);	

	printf("ATOI of %s: = %d\n",temp,myatoi(temp,10));

/*
//verify singly linked list
	Node *head = nullptr;	
	Node *cur = nullptr;

	Node *temp = new Node(1);
	head = temp;

	for(int i = 2; i < 11; i++) {
		temp->_next = new Node(i);
		temp = temp->_next;
	}	
	
	int i = 1;

	printf ("Original List\n");
	for (Node *t = head; t != nullptr ; t = t->_next) {
		printf("Node %d with value %d\n",i++,t->_info);
	}

	printf ("11th last node has following value: %d\n",FindNthLastNode(head,11)->_info);

	cur = ReverseSinglyLinkedList(head);

	// Print the list
	printf ("Reversed List\n");

	i = 1;
	for (Node *t = cur; t != nullptr ; t = t->_next) {
		printf("Node %d with value %d\n",i++,t->_info);
	}

*/
/*	List *list = new List();

	for (int i=0; i<20;i++) {
		list->AddatFront(i);
		list->AddatBack(i);
	}

	list->Print();

	delete list;
*/
	//MultiplicationTable(12);

	//PrintOddNumbers(99);
	/*
	int arr[] = {1, 10, 3, 4, 5, 6};
	int size = sizeof(arr)/sizeof(int);

	printf("Size: %d\n", size);

	printf("Largest Value: %d", FindLargestValue(arr,size));
	*/

	/*
	for ( int i = 0; i <= 10; i++ ) 
		printf ( "%d, ", fib(i) );               
	*/

	/*
	printf ("Size of char: %d\n", sizeof(char));
	printf ("Size of char *: %d\n", sizeof(char *));
	char temp[] = "AACCASFAFASAAAAAAA";
	printf("Before: %s\n",temp);
	char *test = ReverseString1(temp);
	printf("After : %s\n",test);
	delete test;
	char temp1[] = "CAT";
	printf("Before: %s\n",temp1);
	ReverseString2(temp1);
	printf("After : %s\n",temp1);
	*/



}

