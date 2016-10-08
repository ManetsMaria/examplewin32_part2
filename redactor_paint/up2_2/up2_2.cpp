// up2_2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "up2_2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Color(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	PenColor(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Width(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Figure(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_UP2_2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_UP2_2));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UP2_2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_UP2_2);
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
static int brushred = 255, brushyellow = 255, brushblue = 255;
static int pencolor = 0;
static int penwidth = 2;
	static bool circle=FALSE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT style;
	static HINSTANCE hInstance;
	POINT point;
	static HDC hDC;
	static int x1, y1, x2, y2;
	static BOOL bTracking = FALSE;
	static HBRUSH hOldBrush, hBrush;
	static HPEN hDotPen, hOldPen, Pen;
	switch (uMsg)
	{
	case WM_CREATE:
		style = GetClassLong(hWnd, GCL_STYLE);
		hInst = GetModuleHandle(NULL);
		SetClassLong(hWnd, GCL_STYLE, style | CS_DBLCLKS);
		hDotPen = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		hDC = GetDC(hWnd);
		hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
		hMenu = GetSubMenu(hMenu, 0);
		break;
	case WM_LBUTTONDOWN:
		bTracking = TRUE;
		SetROP2(hDC, R2_NOTXORPEN);
		x1 = x2 = LOWORD(lParam);
		y1 = y2 = HIWORD(lParam);
		SelectObject(hDC, hOldBrush);
		SelectObject(hDC, hDotPen);
		if (!circle)
			Rectangle(hDC, x1, y1, x2, y2);
		else
		{
			Ellipse(hDC, x1, y1, x2, y2);
		}
		break;
	case WM_LBUTTONUP:
		if (bTracking) {
			bTracking = FALSE;
			SetROP2(hDC, R2_COPYPEN);
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			Pen = CreatePen(2, penwidth, RGB(pencolor, pencolor, pencolor));
			hBrush = CreateSolidBrush(RGB(brushred, brushyellow, brushblue));
			SelectObject(hDC, hBrush);
			SelectObject(hDC, Pen);
			if (!circle)
			    Rectangle(hDC, x1, y1, x2, y2);
			else
			{
				Ellipse(hDC, x1, y1, x2, y2);
			}
		}
		break;
	case WM_MOUSEMOVE:
		if (bTracking) {
			if (!circle)
			   Rectangle(hDC, x1, y1, x2, y2);
			else
				Ellipse(hDC, x1, y1, x2, y2);
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			if (!circle)
				Rectangle(hDC, x1, y1, x2, y2);
			else
			{
				Ellipse(hDC, x1, y1, x2, y2);
			}
		}
			break;
	case WM_RBUTTONDOWN:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		ClientToScreen(hWnd, &point);
		TrackPopupMenu(hMenu, 0, point.x, point.y, 0, hWnd, NULL);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_COLOR:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Color);
			break;
		case IDM_PenColor:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, PenColor);
			break;
		case IDM_Width:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Width);
			break;
		case IDM_Figure:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hWnd, Figure);
			break;
		}
		return 0;
	case WM_DESTROY:
		DeleteObject(hOldBrush);
		DeleteObject(hBrush);
		DeleteObject(hOldPen);
		DeleteObject(hDotPen);
		ReleaseDC(hWnd, hDC);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK Color(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		if (LOWORD(wParam) == ID_BRUSHCOLOR_YELLOW)
		{
			brushred = 0;
			brushyellow = 255;
			brushblue = 0;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_BRUSHCOLOR_RED)
		{
			brushred = 255;
			brushyellow = 0;
			brushblue = 0;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_BRUSHCOLOR_BLUE)
		{
			brushred = 0;
			brushyellow = 0;
			brushblue = 255;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK PenColor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		if (LOWORD(wParam) == ID_PENCOLOR_BLACK32792)
		{
			pencolor = 0;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_PENCOLOR_WHITE)
		{
			pencolor = 255;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Width(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		if (LOWORD(wParam) == ID_WIDTHPEN_SMALL32789)
		{
			penwidth = 1;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_WIDTHPEN_NORMAL32790)
		{
			penwidth = 5;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_WIDTHPEN_LARGE32791)
		{
			penwidth = 10;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK Figure(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		if (LOWORD(wParam) == ID_FIGURE_RECTANGLE32784)
		{
			circle = FALSE;
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == ID_FIGURE_CIRCLE32785)
		{
			circle = TRUE;
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
