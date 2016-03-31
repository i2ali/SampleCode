
#pragma once

#include <stdlib.h>

class TreeNode {
public:
	int _data;
	TreeNode *left;
	TreeNode *right;
	bool visited;
	TreeNode() { left = NULL; right = NULL; visited = false; }
	TreeNode(int data) : TreeNode() { _data = data; }
	TreeNode* getLeft() { return this->left;}
	TreeNode* getRight() { return this->right;}
};
  
//represents a list
class Tree {

private:
	TreeNode *root;

private:
    void visitNode(TreeNode *node);

public:
	enum Traversal {PreOrder, InOrder, PostOrder};

public:
	Tree() {
		root = NULL;
	}

	Tree(int numitems) {

	}

	~Tree() { delete root; }
	TreeNode* getrootTree(){ return root; }

	void PrintTree(const TreeNode *root, Traversal order);

	TreeNode* BuildTree();

	int TreeHeight(TreeNode *root);

    void DepthFirstTraversal(TreeNode *root);
};

int FindDiameterofBinaryTreeRec(TreeNode *tn, int *height);
int FindDiameterofBinaryTree_Optimized(TreeNode *tn);
int GetHeightTree(TreeNode *tn);
int FindDiameterofBinaryTree_General(TreeNode *tn);
int CountInversions(int a[], int length);
bool DetermineifSumExistsinPath(TreeNode *tn, int sum);
int DistanceFromNearestLeaf(TreeNode *tn, int key);
int FindDistanceinSameBranch(TreeNode *tn);
int FindAncestors(TreeNode *root, int index, TreeNode *ancestors[], int value);
int getMin(int x, int y);



