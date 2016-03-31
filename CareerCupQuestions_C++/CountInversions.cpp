
#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

// O(n^2)
int CountInversions(int a[], int length) {
	
	int inv_count = 0;

	for (int i = 0; i < length; i++)
	{
		int val = a[i]; 

		for (int j = i + 1; j < length; j++)
		{
			if (val > a[j])
			{
				cout << "Inversion found: " << val << ", " << a[j] << endl;
				inv_count++;
			}
		}
	}

	return inv_count;
} // CountInversions

int merge(int input[], int left, int mid, int right, int *scratch)
{
	int i, j, k;
	int inv_count = 0;

	i = left; /* i is index for left subarray*/
	j = mid;  /* i is index for right subarray*/
	k = left; /* i is index for resultant merged subarray*/
	
	while ((i <= mid - 1) && (j <= right))
	{
		if (input[i] <= input[j])
		{
			scratch[k++] = input[i++];
		}
		else
		{
			scratch[k++] = input[j++];

			inv_count = inv_count + (mid - i);
		}
	}

	/* Copy the remaining elements of left subarray
	(if there are any) to temp*/
	while (i <= mid - 1)
		scratch[k++] = input[i++];

	/* Copy the remaining elements of right subarray
	(if there are any) to temp*/
	while (j <= right)
		scratch[k++] = input[j++];

	/*Copy back the merged elements to original array*/
	for (i = left; i <= right; i++)
		input[i] = scratch[i];

	return inv_count;
}

int _mergehelper(int input[], int left, int right, int *scratch)
{
	int mid, inv_count = 0;
	if (right > left)
	{
		/* Divide the array into two parts and call _mergeSortAndCountInv()
		for each of the parts */
		mid = (right + left) / 2;

		/* Inversion count will be sum of inversions in left-part, right-part
		and number of inversions in merging */
		inv_count = _mergehelper(input,left, mid,scratch);
		inv_count += _mergehelper(input, mid + 1, right, scratch);

		/*Merge the two parts*/
		inv_count += merge(input, left, mid + 1, right, scratch);
	}
	return inv_count;
}


int mergesort(int input[], int size) {

	int *scratch = new int[size];

	if (scratch != nullptr)
	{
		_mergehelper(input, 0, size, scratch);
		delete scratch;
		return 1;
	}
	else
	{
		return 0;
	}
}