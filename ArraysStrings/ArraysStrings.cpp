// ArraysStrings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>

// Find all pairs of integers within an array which sum to a specified value
void FindAllPairsSum(int a[], int length, int sum) {

	for (int i = 0; i < length - 1; i++) {
		for (int j = i + 1; j <= length; j++) {
			if ((a[i] + a[j]) == sum)
				cout << "Pair summing to: " << sum << " " << a[i] << " " << a[j] << endl;	
		}
	}
}


void FindAllPairsSum1(int a[], int length, int sum) {

	unordered_map<int,int> hashtable;
	for (auto i = 0; i < length; i++) {
		int tempsum = sum - a[i];
		auto j = hashtable.find(tempsum);

		// item was found
		if (j != hashtable.end()) {
			cout << a[i] << tempsum << endl;
		}
		hashtable.insert({a[i],a[i]});
			
	}
}


/* Problem:
// you are given an array of integers (both positive and negative), find contiguous sequence with the largest sum and return the sum
*/





/* Problem:
Write an array class which allows for an initial size, supports Add, Remove and RemoveAt methods, 
and automatically grows when you run out of initial space. 
Explain your overall growth strategy and design.
*/

// Array Wrapper class of data type T
template<typename T>
class Array {

private:
	long m_size;
	long m_count;
	T* m_pMem; //pointer to template 

public:
	Array() {
		m_size = 0;
		m_count = 0;
		m_pMem = NULL;
	}

	T& operator[] (const long index)
	{
		return Get[index];
	}

	T& Get(const long index) {
		return m_pMem[index];
	}

	virtual ~Array() {
		if (m_pMem != NULL)
			delete[] m_pMem;
	}

	void Add(T value) {
		m_pMem[m_count++] = value;
	}

	T Remove() {
		return m_pMem[--m_count];
	}

	long Count()
	{
		return m_count;
	}

	void EnsureSize(unsigned long newSize)
	{
		if (newSize > m_size)
		{
			// Our new buffer will be the greater of 4, newSize or m_size*1.5
			// 4 ensures we don't grow by 1 for the first 3 entries
			// newSize ensures that if we are pre-allocating known space, we get the space we want
			// m_size*1.5 is our growth strategy. 1.5 to avoid wasting too much space in the buffer.
			//   1.5 - good for in place growth (rare) and avoiding wasted memory
			//   2 - good for a general growth characteristic for most problems.
			unsigned long bufferedSize = max(4, max(static_cast<unsigned long>(m_size*1.5), newSize));
			T* pNewMem = new T[bufferedSize];

			// If we previously had entries then copy them over and delete our old memory
			if (m_pMem != nullptr)
			{
				memcpy_s(pNewMem, bufferedSize*sizeof(T), m_pMem, m_size*sizeof(T));
				delete[] m_pMem;
			}

			// Update our memory buffer and size.
			m_pMem = pNewMem;
			m_size = bufferedSize;
		}
	}



};

// for given 
string InsertCharAt(string s, char c, int index) {
	return s.substr(0, index) + c + s.substr(index);
}

vector<string> FindPermutations(string str) {

	if (str.length() == 0) {
		vector<string> temp = { "" };
		return temp;
	}

	// solve everything in str for str -1
	string remainder = str.substr(1);
	// insert first into every position in remainder
	char first = str[0];
	vector<string> words = FindPermutations(remainder);

	// for each permutation, insert character everywhere
	for (auto i = words.begin(); i != words.end(); ++i) {
		string t1 = *i;
		for (int i = 0; i < t1.length(); ++i) {
			words.emplace_back(InsertCharAt(t1, first, i));
		}
	}
	return words;
}

void ReverseString(char *str) {

	char *end = str;

	while (*end != '\0') {
		end+= sizeof(char);
	}

	end -= sizeof(char); 

	char temp;

	while (end > str) {
		temp = *end;
		*end = *str;
		*str = temp;
		end -= sizeof(char);
		str += sizeof(char);
	}
}


//"51"
//"-45"

int converttonum(char *num) {
	// null terminated string

	// get size of string
	int size = 0;
	char *tmp = num;
	bool neg = false;

	// check for sign
	if (*tmp == '-') {
		neg = true;
	}
		
	// size now contains the length of the string	
	int sum = 0;

	for (; *num != '\0'; num++) {
		sum = sum * 10 + (*num - '0');
	}
	return sum;
}



int _tmain(int argc, _TCHAR* argv[])
{
	// allocate string
	char str[] = "Testing";

	ReverseString(str);
	printf("ReversedString: %s\n", str);

	vector<string> ret = FindPermutations("test");

	for (auto i = ret.begin(); i != ret.end(); i++) {
		//		cout << *i << endl;
	}

	char str1[] = "123";

	int sum = converttonum(str1);

	cout << "Sum: " << sum << endl;

	int iarr[] = { 1, 2, 3, 4, 5, 6, 7 };
	
	FindAllPairsSum(iarr, sizeof(iarr)/sizeof(int), 9);
	FindAllPairsSum1(iarr, sizeof(iarr) / sizeof(int), 9);

	return 0;
}

