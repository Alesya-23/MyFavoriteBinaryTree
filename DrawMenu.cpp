#define _CRT_SECURE_NO_WARNINGS
#include "DrawMenu.h"
#include "My_Tree.h"
#include <iostream>

extern int x_Element;
extern int x_pos_nach; //начальная позиция x
extern int y_pos_nach; // начальная по у
extern int sizeInSizeX;// протяженность х
extern int sizeInSizeY;// протяженность у
extern int size;// размер листка//
extern int flag; // отрисовка поиска или добавления
extern HBRUSH brush[6];

void DrawMenu::DrawTextOutTree(HDC hdc, struct My_Tree* tree) {
	HFONT hFont = CreateFont(17,
		0, 0, 0, 700, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		"Courier New"
	);
	SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 255, 255));

	if (tree->colorInex == 0) {
		SetBkColor(hdc, RGB(43, 181, 60)); // Green
	}
	if (tree->colorInex == 1) {
		SetBkColor(hdc, RGB(200, 56, 5)); // Red
	}
	if (tree->colorInex == 2)
		SetBkColor(hdc, RGB(209, 8, 192)); //Pink
	if (tree->colorInex == 3)
		SetBkColor(hdc, RGB(242, 141, 0)); //yELLOW
	if (tree->colorInex == 4) {
		SetBkColor(hdc, RGB(204, 182, 18)); // oRANGE
	}


	char sHit[5]; // локальная переменная sHit
	TCHAR  tsHit[5];
	sprintf(sHit, "%d", tree->data); // использование глобальной переменной hit
	OemToChar(sHit, tsHit);

	if (tree->data >= 0 && tree->data < 100) {
		TextOut(hdc, tree->x_Element + size / 5, tree->y_Element + size / 5, tsHit, _tcslen(tsHit));
	}
	else
		TextOut(hdc, tree->x_Element, tree->y_Element, tsHit, _tcslen(tsHit));
}

//отрисовка листка
void DrawMenu::draw_tree(HDC hdc, struct My_Tree* tree, int x, int y) {
	tree->x_Element = x;
	tree->y_Element = y;
	if (tree != NULL) {
		if (tree->colorInex == 0) {
			SelectObject(hdc, brush[0]);
			HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 140, 7));
			SelectObject(hdc, hpen);
			Ellipse(hdc, tree->x_Element, tree->y_Element, tree->x_Element + size, tree->y_Element + size);
			DrawTextOutTree(hdc, tree);
		}
		else if (tree->colorInex == 1) {
			SelectObject(hdc, brush[1]);
			HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 140, 7));
			SelectObject(hdc, hpen);
			Ellipse(hdc, tree->x_Element, tree->y_Element, tree->x_Element + size, tree->y_Element + size);
			DrawTextOutTree(hdc, tree);
		}
		else if (tree->colorInex == 2) {
			SelectObject(hdc, brush[2]);
			HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 140, 7));
			SelectObject(hdc, hpen);
			Ellipse(hdc, tree->x_Element, tree->y_Element, tree->x_Element + size, tree->y_Element + size);
			DrawTextOutTree(hdc, tree);
		}
		else if (tree->colorInex == 3) {
			SelectObject(hdc, brush[3]);
			HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 140, 7));
			SelectObject(hdc, hpen);
			Ellipse(hdc, tree->x_Element, tree->y_Element, tree->x_Element + size, tree->y_Element + size);
			DrawTextOutTree(hdc, tree);
			flag = 1001;
		}
		else if (tree->colorInex == 4) {
			SelectObject(hdc, brush[4]);
			HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 140, 7));
			SelectObject(hdc, hpen);
			Ellipse(hdc, tree->x_Element, tree->y_Element, tree->x_Element + size, tree->y_Element + size);
			DrawTextOutTree(hdc, tree);
		}

	}

}

//отрисовка дерева
void DrawMenu::draw_My_Tree(HDC hdc, struct My_Tree* tree, int x_pos_nach, int y_pos_nach) {
	if (size < 30) {
		return;
	}
	sizeInSizeX /= 2;
	draw_tree(hdc, tree, x_pos_nach, y_pos_nach);
	size -= 5;
	if (tree->left != NULL) {
		int x_pos = x_pos_nach - sizeInSizeX - size / 2;
		int y_pos = y_pos_nach + sizeInSizeY - size / 2;
		MoveToEx(hdc, tree->x_Element + size / 2, tree->y_Element + size + 3, NULL);
		LineTo(hdc, tree->x_Element - sizeInSizeX + size / 2, tree->y_Element + sizeInSizeY + size - 13);
		draw_My_Tree(hdc, tree->left, x_pos, y_pos + size - 13);
	}
	if (tree->right != NULL) {
		int x_pos = x_pos_nach + sizeInSizeX + size / 2;
		int y_pos = y_pos_nach + sizeInSizeY - size / 2;
		MoveToEx(hdc, tree->x_Element + size / 2, tree->y_Element + size + 3, NULL);
		LineTo(hdc, tree->x_Element + sizeInSizeX + size / 2, tree->y_Element + sizeInSizeY);
		draw_My_Tree(hdc, tree->right, x_pos, y_pos);
	}
	sizeInSizeX *= 2;
	size += 5;

}

void DrawMenu::drawMenu(HDC hdc) {
	SelectObject(hdc, brush[5]);
	Rectangle(hdc, 0, 0, 1800, 65);

	SelectObject(hdc, brush[3]);
	Rectangle(hdc, 10, 75, 25, 90);

	SelectObject(hdc, brush[4]);
	Rectangle(hdc, 10, 95, 25, 110);

	SelectObject(hdc, brush[2]);
	Rectangle(hdc, 10, 115, 25, 130);

	SelectObject(hdc, brush[1]);
	Rectangle(hdc, 10, 135, 25, 150);

	HFONT hFont = CreateFont(18,
		0, 0, 0, 700, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		"Arial Black"
	);
	SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(156, 2, 79));

	TCHAR string1[] = _T("Нажимайте кнопку и смотрите как работает бинарное дерево поиска!)");
	TextOut(hdc, 10, 10, string1, _tcslen(string1));

	TCHAR string2[] = _T("Введите элемент для поиска:");
	TextOut(hdc, 10, 40, string2, _tcslen(string2));

	TCHAR string3[] = _T("Такого элемента нет (((");

	TCHAR string4[] = _T("Такой элемент есть!))");


	TCHAR string5[] = _T("Искомый элемент");
	TextOut(hdc, 27, 75, string5, _tcslen(string5));

	TCHAR string6[] = _T("Последний добавленный элемент");
	TextOut(hdc, 27, 115, string6, _tcslen(string6));

	TCHAR string7[] = _T("Путь к искомому элементу");
	TextOut(hdc, 27, 95, string7, _tcslen(string7));

	TCHAR string8[] = _T("Путь к последнему добавленному элементу");
	TextOut(hdc, 27, 135, string8, _tcslen(string8));


	if (flag == -1) {
		TextOut(hdc, 430, 40, string3, _tcslen(string3));
	}
	else if (flag == 1001) {

	}
	else {
		TextOut(hdc, 430, 40, string4, _tcslen(string4));
	}

	HFONT hFont1 = CreateFont(35,
		0, 0, 0, 700, 0, 0, 0,
		DEFAULT_CHARSET,
		0, 0, 0, 0,
		"Arial Black"
	);
	SelectObject(hdc, hFont1);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(156, 2, 79));

	TCHAR string9[] = _T("My Favorite Binary Search Tree");
	TextOut(hdc, 710, 15, string9, _tcslen(string9));
}

//ввод строки - кнопка добавить
int DrawMenu::StrToInt(char* s)
{
	int temp = 0; // число
	int i = 0;
	int sign = 0; // знак числа 0- положительное, 1 - отрицательное
	if (s[i] == '-')
	{
		sign = 1;
		i++;
	}
	while (s[i] >= 0x30 && s[i] <= 0x39)
	{
		temp = temp + (s[i] & 0x0F);
		temp = temp * 10;
		i++;
	}
	temp = temp / 10;
	if (sign == 1)
		temp = -temp;


	return(temp);
}

