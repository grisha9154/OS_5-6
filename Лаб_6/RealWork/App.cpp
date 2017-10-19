#include <windows.h>
#include "resource.h"

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
#define ID_MYBUTTON1 1    /* идентификатор для кнопочки внутри главного окна */
#define ID_MyButton2 2

LPCWSTR buf = L"Message"; /* строка для текстового поля в диалоге */
HINSTANCE h;      /* дескриптор экземпляра программы */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss) {
	h = hInst;
	/* создаем и регистрируем класс главного окна */
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

	/* создаем главное окно и отображаем его */
	HWND hMainWnd = CreateWindow(L"Example 4 MainWnd Class", L"EXAMPLE 4", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hMainWnd) return FALSE;
	ShowWindow(hMainWnd, ss);
	UpdateWindow(hMainWnd);

	MSG msg; /* цикл обработки событий */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:
		/* при создании окна внедряем в него кнопочку */
		CreateWindow(L"button", L"Desytroy", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			5, 5, 100, 20, hw, (HMENU)ID_MYBUTTON1, NULL, NULL);
		CreateWindow(L"button", L"Dialog", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
		110, 5, 100, 20, hw, (HMENU)ID_MyButton2, NULL, NULL);
		/* стиль WS_CHILD означает, что это дочернее окно и для него
		вместо дескриптора меню будет передан целочисленный идентификатор,
		который будет использоваться дочерним окном для оповещения
		родительского окна через WM_COMMAND */
		return 0;
	case WM_COMMAND:
		/* нажата наша кнопочка? */
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON1))
			PostQuitMessage(0);
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MyButton2))
			//DialogBox(h, L"Ex4_Dlg", hw, DlgProc);
		DialogBox(h, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
		return 0;
	case WM_DESTROY:
		/* пользователь закрыл окно, программа может завершаться */
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}
BOOL CALLBACK DlgProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_INITDIALOG: /* сообщение о создании диалога */
		SetDlgItemText(hw, 1, buf);
		return TRUE;
	case WM_COMMAND:    /* сообщение от управляющих элементов */
		if (LOWORD(wp) == 2) EndDialog(hw, 0);
	}
	return FALSE;
}