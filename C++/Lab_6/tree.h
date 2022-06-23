#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
	int number;
	Node* left, * right;
	static int num_recursion;
public:
	Node(int);
	void print();
	friend class BinaryTree;
};

class BinaryTree {
	Node* root;
	int max_num;
public:
	BinaryTree() : root(NULL), max_num(0) {}
	void createTree(int value);
	void insertNode(Node* node, int number);
	void printVertical();
	void printHorizontal();
};