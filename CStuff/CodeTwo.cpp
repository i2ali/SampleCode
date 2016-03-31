
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class MyArray {

public:
	MyArray(){}
	static void RemDuplicates(char *arr1[], char *arr2[]);

};


// compares two array and removes duplicates
void MyArray::RemDuplicates(char *arr1[], char *arr2[]) {

	// find length of the arrays
	int arr1size = sizeof(*arr1);
	int arr2size = sizeof(arr2);

	char *temp = "";

	for (int i=0;i<4;i++) {
		temp=arr1[i];
		
		for (int j=0;j<4;j++) {
			if (strcmp(temp,arr2[j])==0){
				arr2[j]="";
			}
		}
	}	

}

void main1(int argc, char * argv[]) {

	MyArray *myarray = new MyArray();

	char *arr1[]= {"test","test1","test2","test3"};
	char *arr2[]= {"test","test1","test2","test4"};

	MyArray::RemDuplicates(arr1,arr2);	

}
