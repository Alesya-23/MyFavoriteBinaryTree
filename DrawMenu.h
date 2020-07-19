#pragma once
#include "framework.h"
#include < windows.h>
#include <string>
#include "My_Tree.h"

class DrawMenu

{
public:
	void DrawTextOutTree(HDC hdc, struct My_Tree* tree);
	void draw_tree(HDC hdc, struct My_Tree* tree, int x, int y);
	void draw_My_Tree(HDC hdc, struct My_Tree* tree, int x_pos_nach, int y_pos_nach);
	void drawMenu(HDC hdc);
	int StrToInt(char* s);
};

