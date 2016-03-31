

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

	void InvertBinaryTree(TreeNode *node);

	TreeNode * BuildTree();

	int TreeHeight(TreeNode *root);

};

