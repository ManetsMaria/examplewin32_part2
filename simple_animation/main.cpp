#define ID_TIMER 1
#undef UNICODE
#include <windows.h>
#include <iostream>
#include <string>
#include <ostream>
#include <stdio.h>
using namespace std;
static HBRUSH on[3];
static HBRUSH off[3];
static HBRUSH real[3];
static bool blink=FALSE;
static bool red=TRUE;
void blinking (bool &blink, int i, HBRUSH real[])
{
  if (!blink)
  {
    real[i]=off[i];
    blink=TRUE;
  }
  else
  {
    real[i]=on[i];
    blink=FALSE;
  }
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
    static int second=0;
    static HBRUSH hBrush;
    switch (uMsg)
    {
    case WM_SIZE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        break;
    case WM_CREATE:
        SetTimer(hWnd, ID_TIMER, 800, NULL);
        hBrush = CreateSolidBrush(RGB(100, 100, 150));
        on[0] = CreateSolidBrush(RGB(255, 0, 0));
        off[0] = CreateSolidBrush(RGB(70, 0, 0));
        on[1] = CreateSolidBrush(RGB(255, 255, 0));
        off[1] = CreateSolidBrush(RGB(70, 70, 0));
        on[2] = CreateSolidBrush(RGB(0, 255, 0));
        off[2] = CreateSolidBrush(RGB(0, 70, 0));
        real[0]=on[0];
        real[1]=off[1];
        real[2]=off[2];
        return 0;
    case WM_TIMER:
        InvalidateRect(hWnd, NULL, TRUE);
        second++;
        if (second%9==4)
         {
             real[1]=on[1];
         }
         if (second%9==0)
         {
            real[1]=off[1];
            if (red)
         {
             real[0]=off[0];
             real[2]=on[2];
             red=FALSE;
         }
            else
            {
                real[0]=on[0];
                real[2]=off[2];
                red=TRUE;
            }
         }
         if (real[1]==on[1])
            if (red)
             blinking(blink, 0, real);
            else
             blinking(blink, 2, real);
        return 0;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);
        SelectObject(hdc, hBrush);
        Rectangle(hdc, sx*3/5, sy/5, sx*9/21, sy*4/5);
        SelectObject(hdc, real[0]);
        Ellipse(hdc, 385, 90, 435, 140);
        SelectObject(hdc, real[1]);
        Ellipse(hdc, 385, 155, 435, 205);
        SelectObject(hdc, real[2]);
        Ellipse(hdc, 385, 220, 435, 270);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        for (int i=0; i<3; i++)
        {
            DeleteObject(on[i]);
            DeleteObject(off[i]);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
return 0;
}
