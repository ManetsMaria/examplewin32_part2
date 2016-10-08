#undef UNICODE
#define ID_TIMER 1
#include <windows.h>
#include <iostream>
#include<string>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;
bool isPointInCircle(int x, int y, RECT rect)
{
    int centreX = (rect.left + rect.right) / 2;
    int centreY = (rect.top + rect.bottom) / 2;
    int dist = (x - centreX)*(x - centreX) + (y - centreY)*(y - centreY);
    return dist < (rect.left - rect.right)*(rect.left - rect.right) / 4;
}
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hMainWnd;
    static char szClassName[] = "MyClass";
    MSG msg;
    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);

    hMainWnd = CreateWindow(
        szClassName, "A Hello1 Application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        (HWND)NULL, (HMENU)NULL,
        (HINSTANCE)hInstance, NULL
        );

    if (!hMainWnd) {
        MessageBox(NULL, "Cannot create main window", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

///////////////////////////////////////////////////////////


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    static int sx, sy;
    static int x, y;
    static HBRUSH hBrush;
    static HBRUSH hBrushNorm;
    static bool change[3];
    switch (uMsg)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    case WM_CREATE:
        for (int i=0; i<3; i++)
        {
           change[i]=FALSE;
        }
        hBrushNorm = CreateSolidBrush(RGB(100, 100, 130));
        SetTimer(hWnd, ID_TIMER, 90, NULL);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        for (int i=0; i<3; i++)
        {
            if (change[i]==TRUE)
            {
              hBrush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
              SelectObject(hdc, hBrush);
            }
            else
            {
                SelectObject(hdc, hBrushNorm);
            }
            Ellipse(hdc, 50+i*70, 50+i*70, 100+i*70, 100+i*70);
            DeleteObject(hBrush);
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        for (int i=0; i<3; i++)
        {
            rect.left=50+i*70;
            rect.top=50+i*70;
            rect.right=100+i*70;
            rect.bottom=100+i*70;
            if (isPointInCircle(x, y, rect))
            {
               change[i]=TRUE;
            }
        }
        break;
    case WM_RBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        for (int i=0; i<3; i++)
        {
            rect.left=50+i*70;
            rect.top=50+i*70;
            rect.right=100+i*70;
            rect.bottom=100+i*70;
            if (isPointInCircle(x, y, rect))
            {
               change[i]=FALSE;
            }
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(hBrushNorm);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
return 0;
}
