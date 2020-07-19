#include "My_Tree.h"
#include <iostream>


extern int flag;
extern int nTree;

struct My_Tree* My_Tree::treeGreen(struct My_Tree* tree) {
	if (tree->data != NULL) {
		tree->colorInex = 0;
		if (tree->left != NULL)
			tree->left = treeGreen(tree->left);
		if (tree->right != NULL)
			tree->right = treeGreen(tree->right);
	}
	return tree;
}

struct My_Tree* My_Tree::addElement(struct My_Tree* tree, int value)
{
	if (nTree < 31) {
		if (tree == NULL) {
			tree = (struct My_Tree*)malloc(
				sizeof(struct My_Tree));
			tree->data = value;
			tree->left = tree->right = NULL;
			tree->colorInex = 2;
			nTree++;
		}
		else if (tree->data == value) {
		}
		else if (value < tree->data) {
			tree->colorInex = 1;
			tree->left = addElement(tree->left, value);
		}
		else  if (value > tree->data) {
			tree->colorInex = 1;
			tree->right = addElement(tree->right, value);
		}
	}
	return tree;
}

struct My_Tree* My_Tree::contains(struct My_Tree* tree, int value)
{
	if (tree == NULL) {
		flag = -1;
		return tree;
	}
	else if (value == tree->data) {
		flag = value;
		tree->colorInex = 3;
		return tree;
	}
	else if (value < tree->data) {
		tree->colorInex = 4;
		contains(tree->left, value);
	}
	else if (value > tree->data) {
		tree->colorInex = 4;
		contains(tree->right, value);
	}
	else tree->colorInex = 0;
}
