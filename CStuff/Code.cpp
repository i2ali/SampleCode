
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int _field;
	Node *next;
	Node() {}
	Node(int field) {_field = field;next=NULL;}
};

typedef struct TreeNode TN;


struct TreeNode {
	int _field;
	TreeNode *left;
	TreeNode *right;
	TreeNode(){}
	TreeNode(int field) {_field=field;left=NULL;right=NULL;}
};


/*
//assume tn is a valid tree node
TN* BuildTree(TN *tn,int) {
	
	if (curdepth == 100) return tn;

	TN tn=new TN(curdepth);
	
	BuildTree(tn->left,curdepth++);
	BuildTree(tn->right,curdepth++);

}
*/


// 10, 3 = 1000 = 10.10.10
long pow(int base, int exponent) {
	long sum = 1;
	for (int i=0;i<exponent;i++){
		sum = sum * base;		
	}
	return sum;
}

//123
// 1, 10+2, 12*10 + 3 = 123
int betteratoi(char num[])
{
	int i,sum;
	// skip trailing space
	for(i=0; num[i]!=' ';i++);

	for (sum=0; num[i] >= '0' && num[i] <= '9';i++)
	{
		sum = 10 * sum + (num[i] - '0'); 		
	}
	return sum;


}



// code up atoi
// 1001
int myatoi(const char *num1) {
	int len = (int)strlen(num1);
	int isum = 0;

	for(int i=len;i>0;i--) {
		isum += (*num1 - '0') * pow(10,i-1);
		num1++;
	}

	return isum;
}


// find factorial of number
int FindFactorial(int number) {
	if (number > 0)
		return number * FindFactorial(number-1);
	else
		return 1;
}


void Traversal(TreeNode *list) {

	if (!list){ return;}
	else
		printf("Node:%i",list->_field);
	
	Traversal(list->right);
	Traversal(list->left);
}



// use some sort of bubble sort
void BubbleSortLinkedList (Node *list) {
		
	Node *head = list;
	Node *first = head;
	Node *second = NULL;
	second = first->next;
	int temp;

	while (second!=NULL) {

		// find a value <= first
		while ((second->_field) >= (first->_field)){
			second=second->next;
			if (!second)
				break;

		}

		//swap values
		if (second !=NULL)
		{
			temp = first->_field;
			first->_field = second ->_field;
			second ->_field = temp;
		}
		else // we have traversed the entire list
		{
			first=first->next;
			second = first->next;
		}
	}

}


/*
 TODO: Need to write a trimming function.  We have strings that
 have leading and trailing characters that need to get stripped
 (eg spaces, commas, periods, slashes)
 How do you want the function prototype to look like?
 Implement it.

*/


// trimlist contains crap you want trimmed
char * Trimmer(const char *string, const char *trimlist) 
{
	

	return NULL;
}


int mystrlen(const char *string) 
{
	int length = 0;

	for(; *string!='\0';length++,string++);

	return length;
}

void ReverseString(char *string) {
	
	char *Begin=string;
	char *End=string + strlen(string)- 1;
	char temp='\0';

	while (End > Begin)
	{
		temp=*Begin;
		*Begin=*End;
		*End=temp;
		Begin++;
		End--;
	}
}


Node * ReverseSinglyLinkedList(Node *head) {
	
	Node *start = head->next;
	Node *cur = head->next;
	Node *prev = head;
	prev->next=NULL;

	while (cur->next != NULL) {
		cur = cur->next;
		start->next = prev;
		prev = start;
		start=cur;
	}

	cur->next = prev;
	// 'start' now points to head of list
	return start;
}

static void PrintList(Node *list) 
{
	if (list==NULL) return;
	Node *head = list;
	for (Node *head = list;head!= NULL;head=head->next) 
	{
		printf("Value:%i\n",head->_field);
	}
}

// Creates a list
Node * CreateList(int *list, int length) {
	
	int listsize = sizeof(*list)/sizeof(int);	

	Node *head = NULL;
	head = new Node(list[0]);
	Node *cur = head;

	for (int i=1;i<length;i++)
	{
		cur->next = new Node(list[i]);
		cur = cur->next;
	}

	return head;

}

// abcdef becomes fedcba
// Reverses string in place
void reversestring(char *str)
{
	char *begin=str;
	char *end=str;
	char temp;

	for(;*end!='\0';end++);
	end--;

	for(;end>=begin;end--,begin++)
	{
		temp=*begin;
		*begin=*end;
		*end=temp;
	}
}

// returns a string with dest + src, dest must be big enough
char * strcat(char *dest,const char *src) {
	// go to end of dest, i.e find '/0'
	int i;
	char *start = dest;
	for (i=0; *start!='\0';start++);
	for (;(*start++=*src++)!='\0';);	
	return dest;
}

/*
void main(int argc, char * argv[]) {

	char dest1[] = "First";
	char src[] = "Second";

	reversestring(dest1);
	printf("String is %s",dest1);

//	printf("String is %s",strcat(dest1,src));
	
	// Test strlen
	char *test="This is a test";
//	printf("Length of string is: %i",mystrlen(test));

//	char *test1="12345";
	char test1[]="12345";
//	printf("String in num format is: %i",myatoi(test1));

	//Test SINGLY LINKED LIST
	Node *newlist = NULL;
	int list[] = {1,2,3,4,5,6,7,8};
	int *plist = list;
	newlist = CreateList(plist, sizeof(list)/sizeof(int));
	PrintList(newlist);
	newlist = ReverseSinglyLinkedList(newlist);	
	PrintList(newlist);

//	int list[] = {8,2,3,2,5,1,100,33};
//	int list[] = {1,2,3,4,5,6,7,8};
	
	//Node *newlist = NULL;
	//int list[] = {8,2,3,2,5,1,100,33};
	//int list1[] = {1,2,3,4,5,6,7,8};
	//int *plist = list;
	//newlist = CreateList(plist, sizeof(list)/sizeof(int));
	//BubbleSortLinkedList(newlist);
	//PrintList(newlist);
	//delete newlist;


	// TEST REVERSE STRING
	//char *string = "Testing";
	//printf("Original string %s",string);
	//ReverseString(string);
	//printf("Reversed string %s",string);

	



}

*/


