
#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

int DistanceFromNearestLeaf(TreeNode *root, int key)
{
	if (root == nullptr)
		return 0;
    TreeNode *ancestors[1000];

    return FindAncestors(root, 0, ancestors, key);

}


int FindAncestors(TreeNode *root, int index, TreeNode *ancestors[], int value)
{
    if (root == nullptr) {
        return INT_MAX;
    }

    if (root->_data == value)
    {
        int res = FindDistanceinSameBranch(root);
   
        // traverse all ancestors and check to see if any of the ancestors have a 
        for (int i = index - 1; i >= 0; i--)
            res = getMin(res, index - i + FindDistanceinSameBranch(ancestors[i]));
        return res;
    }

    // in this case we have not found the key value so update the ancestor and search for the left and right ancestors.
    ancestors[index] = root;

    return getMin(FindAncestors(root->left, index + 1, ancestors, value), FindAncestors(root->right, index + 1, ancestors, value));

}

int getMin(int x, int y)
{
    return (x < y) ? x : y;

}

// find minimum distance between leaf given pointer
int FindDistanceinSameBranch (TreeNode *tn)
{
    if (tn == NULL)
        return INT_MAX;

    if ((tn->left == nullptr) && (tn->right == nullptr))
        return 0;

    return getMin(FindDistanceinSameBranch(tn->left),FindDistanceinSameBranch(tn->right)) + 1;
}


















