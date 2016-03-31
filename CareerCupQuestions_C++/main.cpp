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
    
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    root->right->left->right = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    cout << "FindDistanceinSameBranch: " << FindDistanceinSameBranch(root) << endl;

    cout << "DistanceFromNearestLeaf: " << DistanceFromNearestLeaf(root, 1) << endl;

	return 0;
}

