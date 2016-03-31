
#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;


bool DetermineifSumExistsinPath(TreeNode *tn, int sum)
{
	if (tn == nullptr)
		return false;

	int runningsum = sum - tn->_data;

	// check if leaf node
	if ((tn->left == nullptr) && (tn->right == nullptr)) {
		return (runningsum == 0);
	}

	if (DetermineifSumExistsinPath(tn->left, runningsum) || DetermineifSumExistsinPath(tn->right, runningsum))
		return true;
	else
		return false;
}