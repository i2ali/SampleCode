
#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

int FindDiameterofBinaryTreeRec(TreeNode *tn, int *height) {

	if (tn == NULL) {
		*height = 0;
		return 0;
	}

	int lh = 0;
	int rh = 0;
	int dleft = 0;
	int dright = 0;

	dleft = FindDiameterofBinaryTreeRec(tn->left, &lh);
	dright = FindDiameterofBinaryTreeRec(tn->right, &rh);
	*height = std::max(lh, rh) + 1;
	return std::max(std::max(dleft, dright), lh + rh + 1);

}

int FindDiameterofBinaryTree_Optimized(TreeNode *tn) {
	int height = 0;
	return FindDiameterofBinaryTreeRec(tn, &height);
}

int GetHeightTree(TreeNode *tn) {

	if (tn == NULL)
		return 0;

	return 1 + max(GetHeightTree(tn->left), GetHeightTree(tn->right));
}

int FindDiameterofBinaryTree_General(TreeNode *tn) {

	if (tn == NULL)
		return 0;

	int rdiam = FindDiameterofBinaryTree_General(tn->right);
	int ldiam = FindDiameterofBinaryTree_General(tn->left);

	int rheight = GetHeightTree(tn->right);
	int lheight = GetHeightTree(tn->left);

	return max(rheight + lheight + 1, (max(rdiam, ldiam)));

}






