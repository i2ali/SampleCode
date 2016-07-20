#include "CommonDataTypes.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace::std;

int findLowestCommonAncestor(TreeNode *root, int n1, int n2) {

	if (!root)
		return -1;

	vector<int>path1;
	vector<int>path2;

	if ( !findPath(root, path1, n1) || !findPath(root, path2, n2)) {
		return -1;
	}

	int minimum = min(path1.size(), path2.size());
	int lca = 0;

	for (int i = 0; i < minimum; i++) {
		if (path1[i] == path2[i])
			lca = path1[i];
	}
	
	return lca;
}


// traverse down the path until we find target
bool findPath ( TreeNode *root, vector<int> &path, int target ) {

	if (!root)
		return false;

	path.push_back(root->_data);

	if (root->_data == target) 
		return true;

	if (((root->right) && (findPath(root->right, path, target)))
		|| ((root->left) && (findPath(root->left, path, target))))
		return true;

	path.pop_back(); 

	return false;

}











