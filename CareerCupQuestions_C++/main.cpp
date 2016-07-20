// CareerCupQuestions_C++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "CommonDataTypes.h"

using namespace::std;


int _tmain(int argc, _TCHAR* argv[])
{

	Tree *tree = new Tree();

//	TreeNode *root = tree->BuildTree();

//	tree->PrintTree(root, Tree::InOrder);

/*	cout << "Diameter of Binary Tree: General: " << FindDiameterofBinaryTree_General(root) << endl;

	cout << "Diameter of Binary Tree: Optimized: " << FindDiameterofBinaryTree_Optimized(root) << endl;

	cout << "Does there exists path in tree with sum 14 " << DetermineifSumExistsinPath(root, 14) << endl;

	int a[5] = { 2, 4, 1, 3, 5 };
	int b[5] = { 1, 20, 6, 4, 5 };
 
	cout << "Number of inversions: " << CountInversions(a, 5) << endl;

	cout << "Number of inversions: " << CountInversions(b, 5) << endl;
*/
/*    
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->right->left->right = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    cout << "FindDistanceinSameBranch: " << FindDistanceinSameBranch(root) << endl;

    cout << "DistanceFromNearestLeaf: " << DistanceFromNearestLeaf(root, 1) << endl;
*/

	/*
   	          15
	    8           20
   	  6    9    17    22
	4  7    10 16  18 21 23

    */
	TreeNode *root = new TreeNode(15);
	root->left = new TreeNode(8);
	root->left->right = new TreeNode(9);
	root->left->right->right = new TreeNode(10);
	root->left->left = new TreeNode(6);
	root->left->left->left = new TreeNode(4);
	root->left->left->right = new TreeNode(7);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(17);
	root->right->left->left = new TreeNode(16);
	root->right->left->right = new TreeNode(18);
	root->right->right = new TreeNode(22);
	root->right->right->right = new TreeNode(23);
	root->right->right->left = new TreeNode(21);

/*	TreeNode *minnode = findMinValue(root);
	if (minnode) cout << "Min Value: " << minnode->_data << endl;

	TreeNode *maxnode = findMaxValue(root);
	if (maxnode) cout << "Max Value: " << maxnode->_data << endl;

	TreeNode *succ = findNextSuccessor(root, root->right->right->left);
	if (succ)
		cout << "Next Successor: " << succ->_data << endl;
	else
		cout << "No Successor! " << endl;

	TreeNode *pred = findNextPredecessor(root, root->right->right->left);
	if (pred)
		cout << "Next Predecessor: " << pred->_data << endl;
	else
		cout << "No Predecessor! " << endl;

	TreeNode *bstresult = findValue(root, 23);
	if (bstresult)
		cout << "Found value of: " << bstresult->_data << endl;
	else
		cout << "Not found!" << endl;
*/
	vector<int>path;
	vector<int>path1;

	findPath(root,path,17);

	for (auto i = path.begin(); i != path.end(); i++)
		cout << "Val: " << (*i) << endl;

	findPath(root, path1, 20);

	for (auto i = path1.begin(); i != path1.end(); i++)
		cout << "Val: " << (*i) << endl;

	cout << findLowestCommonAncestor(root, 17, 20) << endl;

	return 0;
}

