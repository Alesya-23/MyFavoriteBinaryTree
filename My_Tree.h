#pragma once


class My_Tree {

public:
	int data;
	struct My_Tree* left;
	struct My_Tree* right;
	int colorInex = 0;
	int x_Element;
	int y_Element;

	struct My_Tree* treeGreen(struct My_Tree* tree);

	struct My_Tree* addElement(struct My_Tree* tree, int value);

	struct My_Tree* contains(struct My_Tree* tree, int value);
};