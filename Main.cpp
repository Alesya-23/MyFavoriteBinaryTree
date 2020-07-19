// My_Favorite_TREE_Graphics.cpp : Определяет точку входа для приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "Main.h"
#include "My_Tree.h"
#include "DrawMenu.h"
#include <iostream>
#include < windows.h>
#include <string>


#define MAX_LOADSTRING 100

HBRUSH brush[6] = {
	CreateSolidBrush(RGB(43, 181, 60)),// зеленое дерево
	CreateSolidBrush(RGB(204, 16, 16)),//путь
	CreateSolidBrush(RGB(209, 8, 192)),// искомый элемент
	CreateSolidBrush(RGB(242, 141, 0)),//поиск путь
	CreateSolidBrush(RGB(204, 182, 18)),//последний элемент
	CreateSolidBrush(RGB(156, 2, 79)),// меню

};

int x_pos_nach = 600; //начальная позиция x
int y_pos_nach = 75; // начальная по у
int sizeInSizeX = 560;// протяженность х
int sizeInSizeY = 80;// протяженность у
int size = 50;// размер листка//
int flag = 1001; // отрисовка поиска или добавления

int nTree = 0;

int m = 0;

int mass[31] = {
	60, 40,20,10,30,31,29,50, 90,
	57, 48, 49, 47, 70, 62,96,92,
	80,95,91,98,75,86,2,11,55,63,
	58, 97,99, 61
};

struct My_Tree* root = NULL;
DrawMenu menu;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MYFAVORITETREEGRAPHICS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFAVORITETREEGRAPHICS));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFAVORITETREEGRAPHICS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 10);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MYFAVORITETREEGRAPHICS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1300, 600, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInst;
	PAINTSTRUCT ps;
	static HWND hBtnInsert, hBtnSearch; // дескриптор кнопки
	static HWND hEdtInsert, hEdtSearch; // дескрипторы полей редактирования
	static HWND hStat; // дескриптор статического текста
	TCHAR StrInsert[4], StrSearch[4];
	int insert, search, Len;

	switch (message) {
	case WM_CREATE:
		// сообщение создания окна
		hInst = ((LPCREATESTRUCT)lParam)->hInstance; // дескриптор приложения
		// Создаем и показываем кнопку
		hBtnInsert = CreateWindow(TEXT("button"), TEXT("Добавить"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			550, 10, 70, 20, hWnd, 0, hInst, NULL);
		ShowWindow(hBtnInsert, SW_SHOWNORMAL);
		hEdtSearch = CreateWindow(TEXT("edit"), TEXT(" "),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 260, 40, 70, 20,
			hWnd, 0, hInst, NULL);
		ShowWindow(hEdtSearch, SW_SHOWNORMAL);
		hBtnSearch = CreateWindow(TEXT("button"), TEXT("Искать"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			340, 40, 70, 20, hWnd, 0, hInst, NULL);
		InvalidateRect(hEdtInsert, NULL, TRUE);
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		if (lParam == (LPARAM)hBtnInsert)    // если нажали на кнопку
		{
			if (m < 31) {
				if (root != NULL)
					root->treeGreen(root);
				root = root->addElement(root, mass[m]);
				m++;
			}
			else root->treeGreen(root);
			SetWindowText(hEdtInsert, (LPSTR)NULL);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (lParam == (LPARAM)hBtnSearch)
		{
			Len = GetWindowText(hEdtSearch, StrSearch, 4);
			search = menu.StrToInt(StrSearch); // считываем число из второго поля
			if (root != NULL && search != 0 && m != 0) {
				root->treeGreen(root);
				root->contains(root, search);
				SetWindowText(hEdtSearch, (LPSTR)NULL);
				InvalidateRect(hEdtSearch, NULL, TRUE);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		break;
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		//////ЕСЛИ ИЗНАЧАЛЬНО ДЕРЕВО ПУСТОЕ - так как должно быть
		SelectObject(hdc, brush[3]);
		menu.drawMenu(hdc);
		if (root != NULL) {
			menu.draw_My_Tree(hdc, root, x_pos_nach, y_pos_nach);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}