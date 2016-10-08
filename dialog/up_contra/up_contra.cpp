// up_contra.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "up_contra.h"
#include <string>
#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
BOOL CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE
	hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int ret = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1),
		NULL, (DLGPROC)About);
	if (ret == 0)
	{
		//Если была нажата кнопка Отмена или крестик
		//MessageBox(NULL, (LPCTSTR)"Отмена", "Inform",
		//MB_OK | MB_ICONINFORMATION);
	}
	else if (ret == 1)
	{
		//Если была нажата кнопка Ок
		//MessageBox(NULL, (LPCTSTR)"Ок", "Inform",
		//MB_OK | MB_ICONINFORMATION);

	}

	return ret;
}

static string edit;
// Message handler for about box.
BOOL CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hListBox;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		hListBox = GetDlgItem(hDlg, IDC_LIST1);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			//InvalidateRect(GetParent(hDlg), NULL, TRUE);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO1)
		{
			char out[20] = "Radio1";
			SendMessage(hListBox, LB_ADDSTRING, 0,
				(LPARAM)out);
		}
		if (LOWORD(wParam) == IDC_RADIO2)
		{
			char out[20] = "Radio2";
			SendMessage(hListBox, LB_ADDSTRING, 0,
				(LPARAM)out);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_CHECK1)
		{
			char out[20] = "Check1";
			SendMessage(hListBox, LB_ADDSTRING, 0,
				(LPARAM)out);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_CHECK2)
		{
			char out[20] = "Check2";
			SendMessage(hListBox, LB_ADDSTRING, 0,
				(LPARAM)out);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_EDIT1)
		{
			SendMessage(GetDlgItem(hDlg, IDC_EDIT1), WM_GETTEXT, 50, (LPARAM)edit.c_str());
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0,
				(LPARAM)edit.c_str());
			return TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

