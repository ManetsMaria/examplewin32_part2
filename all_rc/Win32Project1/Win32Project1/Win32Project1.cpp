// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#define ID_TIMER 1
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
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
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

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
}



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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = MAKEINTRESOURCE (IDR_MENU1);
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
HMENU hMenu, hFileMenu;
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
bool isPointInCircle(int x, int y, RECT rect)
{
	int centreX = (rect.left + rect.right) / 2;
	int centreY = (rect.top + rect.bottom) / 2;
	int dist = (x - centreX)*(x - centreX) + (y - centreY)*(y - centreY);
	return dist < (rect.left - rect.right)*(rect.left - rect.right) / 4;
}
static RECT rectmas[3];
static bool change[3];
static bool radius[3];
void changeRadius(RECT &rect, bool &r)
{
	if (!r)
	{
		rect.bottom--;
		rect.left--;
		rect.right--;
		rect.top--;
		r = TRUE;
	}
	else
	{
		rect.bottom++;
		rect.left++;
		rect.right++;
		rect.top++;
		r = FALSE;
	}
}
static HPEN hPen;
static HBRUSH hBrushNorm;
void br(HBRUSH &hBrush, int a, int b, int c)
{
	hBrush = CreateSolidBrush(RGB(a, b, c));
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	static HINSTANCE hInstance;
	static int sx, sy;
	static int x, y;
	POINT point;
	switch (uMsg)
	{
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
		hMenu = GetSubMenu(hMenu, 0);
		hBrushNorm = CreateSolidBrush(RGB(100, 130, 100));
		hPen = CreatePen(1, 5, RGB(0, 0, 0));
		for (int i = 0; i<3; i++)
		{
			change[i] = FALSE;
			rect.left = 50 + i * 70;
			rect.top = 50 + i * 70;
			rect.right = 100 + i * 70;
			rect.bottom = 100 + i * 70;
			rectmas[i] = rect;
			radius[i] = FALSE;
		}
		SetTimer(hWnd, ID_TIMER, 90, NULL);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hBrushNorm);
		SelectObject(hdc, hPen);
		for (int i = 0; i<3; i++)
		{
			Ellipse(hdc, rectmas[i].left, rectmas[i].top, rectmas[i].right, rectmas[i].bottom);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_BALLS_CHANGE1BALL:
			if (change[0])
				change[0] = FALSE;
			else
				change[0] = TRUE;
			break;
		case ID_BALLS_CHANGE2BALL:
			if (change[1])
				change[1] = FALSE;
			else
				change[1] = TRUE;
			break;
		case ID_BALLS_CHANGE3BALL:
			if (change[2])
				change[2] = FALSE;
			else
				change[2] = TRUE;
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		};
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (int i = 0; i<3; i++)
		{
			if (isPointInCircle(x, y, rectmas[i]))
			{
				change[i] = TRUE;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		for (int i = 0; i<3; i++)
		{
			if (isPointInCircle(x, y, rectmas[i]))
			{
				change[i] = FALSE;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		point.x = x;
		point.y = y;
		ClientToScreen(hWnd, &point);
		TrackPopupMenu(hMenu, 0, point.x, point.y, 0, hWnd, NULL);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		for (int i = 0; i<3; i++)
			if (change[i] == TRUE)
				changeRadius(rectmas[i], radius[i]);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(hBrushNorm);
		KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
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
		if (LOWORD(wParam) == IDC_RADIO1)
		{
			hBrushNorm = CreateSolidBrush(RGB(255, 255, 255));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO2)
		{
			hBrushNorm = CreateSolidBrush(RGB(0, 0, 0));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO3)
		{
			hBrushNorm = CreateSolidBrush(RGB(10, 170, 100));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO4)
		{
			hPen = CreatePen(1, 1, RGB(0, 0, 0));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO5)
		{
			hPen = CreatePen(1, 10, RGB(0, 0, 0));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_RADIO6)
		{
			hPen = CreatePen(1, 20, RGB(0, 0, 0));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
