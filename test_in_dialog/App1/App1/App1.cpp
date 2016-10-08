// App1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "App1.h"
#include <vector>
#include <string>
#include <fstream>

#define MAX_LOADSTRING 100

// Global Variables:
std::ifstream fin("questions.txt");
std::vector<std::vector<std::string> > questions;
std::vector<int> answers;
std::vector <int> typeQuestion;
int currQuetion = 0;
int currAnswer = 0;
int result = 0;
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	MainDialog(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, MainDialog);
	return 0;
}
/*int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_APP1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APP1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}*/



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_APP1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
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
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.
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

INT_PTR CALLBACK MainDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::vector <std::string> temp;
	std::string str;
	int n, m;
	std::string question, answer1, answer2, answer3;
	int rightAnswer = 0, nTemp;
	static bool mas[10];
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		fin >> n;
		for (int i = 0; i < 10; i++)
			mas[i] = false;
		for (int i = 0; i < n; i++)
		{
			rightAnswer = 0;
			fin >> nTemp;
			typeQuestion.push_back(nTemp);
			nTemp = 0;
			std::getline(fin, question);
			std::getline(fin, question);
			temp.push_back(question);
			fin >> m;
			std::getline(fin, answer1);
			for (int j = 0; j < m; j++)
			{
				std::getline(fin, answer1);
				temp.push_back(answer1);
			}
			while (fin.peek() != '\n' && !fin.eof())
			{
				fin >> nTemp;
				rightAnswer += 1 << nTemp;
			}
			questions.push_back(temp);
			answers.push_back(rightAnswer);
			temp.clear();
		}
		SetDlgItemText(hDlg, IDC_STATIC, questions[currQuetion][0].c_str());
		for (int i = 0; i < 5; i++)
		{
			ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_HIDE);
			ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_HIDE);
			CheckDlgButton(hDlg, IDC_CHECK1 + i, BST_UNCHECKED);
			CheckDlgButton(hDlg, IDC_RADIO1 + i, BST_UNCHECKED);
		}
		switch (typeQuestion[currQuetion])
		{
			case 1: 
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_RADIO1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
			case 2: 
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_CHECK1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
		}
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD (wParam))
		{
		case IDOK:
			if (currAnswer == answers[currQuetion]) mas[currQuetion] = true;
			else mas[currQuetion] = false;
			currQuetion++;
			currAnswer = 0;
			if (currQuetion == questions.size())
			{
				result = 0;
				for (int i = 0; i < 10; i++)
					if (mas[i] == true)
						result++;
				str = "You answered " + std::to_string(result) + " questions right.";
				MessageBox(hDlg, str.c_str(), "Your result", MB_OK);
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			SetDlgItemText(hDlg, IDC_STATIC, questions[currQuetion][0].c_str());
			for (int i = 0; i < 5; i++)
			{
				ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_HIDE);
				CheckDlgButton(hDlg, IDC_CHECK1 + i, BST_UNCHECKED);
				CheckDlgButton(hDlg, IDC_RADIO1 + i, BST_UNCHECKED);
			}
			switch (typeQuestion[currQuetion])
			{
			case 1:
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_RADIO1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
			case 2:
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_CHECK1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
			}
			break;
		case IDC_BUTTON2:
			result = 0;
			for (int i = 0; i < 10; i++)
				if (mas[i] == true)
					result++;
			str = std::to_string(result);
			MessageBox(hDlg, str.c_str(), "Resalt", MB_OK);
			break;
		case IDC_BUTTON1:
			currAnswer = 0;
			if (currQuetion == 0)
			{
				str = "You are at the beginning";
				MessageBox(hDlg, str.c_str(), "Error", MB_OK);
				currQuetion++;
			}
			currQuetion--;
			SetDlgItemText(hDlg, IDC_STATIC, questions[currQuetion][0].c_str());
			for (int i = 0; i < 5; i++)
			{
				ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_HIDE);
				ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_HIDE);
				CheckDlgButton(hDlg, IDC_CHECK1 + i, BST_UNCHECKED);
				CheckDlgButton(hDlg, IDC_RADIO1 + i, BST_UNCHECKED);
			}
			switch (typeQuestion[currQuetion])
			{
			case 1:
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_RADIO1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
			case 2:
				for (int i = 0; i < questions[currQuetion].size() - 1; i++)
				{
					ShowWindow(GetDlgItem(hDlg, IDC_CHECK1 + i), SW_NORMAL);
					SetDlgItemText(hDlg, IDC_CHECK1 + i, questions[currQuetion][i + 1].c_str());
				}
				break;
			}
			break;
		case IDC_RADIO1:
			currAnswer = 1 << 1;
			break;
		case IDC_RADIO2:
			currAnswer = 1 << 2;
			break;
		case IDC_RADIO3:
			currAnswer = 1 << 3;
			break;
		case IDC_RADIO4:
			currAnswer = 1 << 4;
			break;
		case IDC_RADIO5:
			currAnswer = 1 << 5;
			break;
		case IDC_CHECK1:
			currAnswer += 1 << 1;
			break;
		case IDC_CHECK2:
			currAnswer += 1 << 2;
			break;
		case IDC_CHECK3:
			currAnswer += 1 << 3;
			break;
		case IDC_CHECK4:
			currAnswer += 1 << 4;
			break;
		case IDC_CHECK5:
			currAnswer += 1 << 5;
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}