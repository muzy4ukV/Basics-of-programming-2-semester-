#include "tree.h"

Node::Node(int number) {
	this->number = number;
	this->left = NULL;
	this->right = NULL;
}

int Node::num_recursion = 0;

void BinaryTree::createTree(int value) {
	root = new Node(1);
	max_num = value;
	if (value > 1)
	{
		insertNode(root, 2);
	}	
}

void BinaryTree::insertNode(Node* node, int num) {
	if (!node->left && !node->right) {
		node->left = new Node(num);
		node->right = new Node(num);
	}
	if (num < max_num)
		insertNode(node->left, num + 1);
	if (num < max_num)
		insertNode(node->right, num + 1);
}

void BinaryTree::printVertical() {
	if (root == NULL)
		return;
	vector<Node*> stack;
	stack.push_back(root);
	int tabs = (pow(2, max_num) - 1) / 2;
	int level = 0;
	while(!stack.empty())
	{
		for (int k = 0; k < pow(2, level); k++)
		{
			for (int i = 0; i < tabs; i++) cout << " ";
			Node* node = stack.front();
			cout << node->number;
			stack.erase(stack.begin());
			for (int i = 0; i < tabs + 1; i++) cout << " ";

			if (node->left)
				stack.push_back(node->left);

			if (node->right)
				stack.push_back(node->right);
		}
		level++;
		tabs /= 2;
		cout << endl << endl;
	}
}

void BinaryTree::printHorizontal() {
	root->print();
}

void Node::print() {
	if (right) {
		num_recursion += 5;
		right->print();
	}
	for (int i = 0; i < num_recursion; i++) cout << " ";
	cout << this->number << endl;
	if (left) {
		num_recursion += 5;
		left->print();
	}
	num_recursion -= 5;
}


