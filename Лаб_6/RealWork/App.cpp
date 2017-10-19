#include <windows.h>
#include "resource.h"

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
#define ID_MYBUTTON1 1    /* ������������� ��� �������� ������ �������� ���� */
#define ID_MyButton2 2

LPCWSTR buf = L"Message"; /* ������ ��� ���������� ���� � ������� */
HINSTANCE h;      /* ���������� ���������� ��������� */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss) {
	h = hInst;
	/* ������� � ������������ ����� �������� ���� */
	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = MainWinProc;
	wc.cbClsExtra = wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Example 4 MainWnd Class";
	if (!RegisterClass(&wc)) return FALSE;

	/* ������� ������� ���� � ���������� ��� */
	HWND hMainWnd = CreateWindow(L"Example 4 MainWnd Class", L"EXAMPLE 4", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hMainWnd) return FALSE;
	ShowWindow(hMainWnd, ss);
	UpdateWindow(hMainWnd);

	MSG msg; /* ���� ��������� ������� */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/* ��������� ��������� ��������� ��� �������� ���� */
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:
		/* ��� �������� ���� �������� � ���� �������� */
		CreateWindow(L"button", L"Desytroy", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			5, 5, 100, 20, hw, (HMENU)ID_MYBUTTON1, NULL, NULL);
		CreateWindow(L"button", L"Dialog", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		110, 5, 100, 20, hw, (HMENU)ID_MyButton2, NULL, NULL);
		/* ����� WS_CHILD ��������, ��� ��� �������� ���� � ��� ����
		������ ����������� ���� ����� ������� ������������� �������������,
		������� ����� �������������� �������� ����� ��� ����������
		������������� ���� ����� WM_COMMAND */
		return 0;
	case WM_COMMAND:
		/* ������ ���� ��������? */
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON1))
			PostQuitMessage(0);
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MyButton2))
			//DialogBox(h, L"Ex4_Dlg", hw, DlgProc);
		DialogBox(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
		return 0;
	case WM_DESTROY:
		/* ������������ ������ ����, ��������� ����� ����������� */
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}
BOOL CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_INITDIALOG: /* ��������� � �������� ������� */
		SetDlgItemText(hw, 1, buf);
		return TRUE;
	case WM_COMMAND:    /* ��������� �� ����������� ��������� */
		if (LOWORD(wp) == 2) EndDialog(hw, 0);
	}
	return FALSE;
}