// winapi_diffusion.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winapi_diffusion.h"

#include <cmath>
#include <ctime>
#include <vector>
#include "Ball.h"

#define MAX_LOADSTRING 100

#define ID_TIMER 1

// Global Variables:
HINSTANCE hInst;								// current instance
WCHAR szTitle[MAX_LOADSTRING];					// The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void drawBalls(HDC hdc, std::vector<Ball>* balls);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPWSTR lpCmdLine,
					_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI_DIFFUSION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI_DIFFUSION));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
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
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI_DIFFUSION));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCEW(IDC_WINAPI_DIFFUSION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//	FUNCTION: InitInstance(HINSTANCE, int)
//
//	PURPOSE: Saves instance handle and creates main window
//
//	COMMENTS:
//
//		In this function, we save the instance handle in a global variable and
//		create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
	  return FALSE;
	}

	srand((unsigned)time(nullptr));

	std::vector<Ball>* balls =  new std::vector<Ball>();
	for (int i = 0; i < 10; ++i)
	{
		int px = 640 + rand() % 128;
		int py = -320 + rand() % 128;

		int vx = -32 + rand() % 64;
		int vy = -32 + rand() % 64;

		Vector2D<double> position(px, py);
		Vector2D<double> velocity(vx, vy);

		balls->push_back(Ball(30.0, position, velocity));
	}

	// on success SetWindowLongPtr rewrites last pointer
	// this line is needed to avoid false zero error code
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)666);
	if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)balls))
		return FALSE;

	SetTimer(hWnd, ID_TIMER, 50, nullptr);
	SetMenu(hWnd, nullptr);
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
	auto balls = (std::vector<Ball>*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch (message)
	{
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			case VK_SPACE:
				//SYSTEMTIME st;
				//GetSystemTime(&st);
				////drawCircle(hdc, st.wMilliseconds);
				//ReleaseDC(hWnd, hdc);
				//InvalidateRect(hWnd, nullptr, false);
				break;

			}
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			SetMapMode(hdc, MM_LOMETRIC);
			// TODO: Add any drawing code that uses hdc here...

			////////
			drawBalls(hdc, balls);
			////////

			EndPaint(hWnd, &ps);

			//SYSTEMTIME st;
			//GetSystemTime(&st);
			//LPTSTR lpszDynamic = new TCHAR[100];
			//// Do something with lpszDynamic
			//_snwprintf(lpszDynamic, 100 * sizeof(TCHAR), L"%d+aaa dzcdsc ac sac sa c sa csa xxx  ", st.wMilliseconds  );
			//SetWindowText(hWnd, lpszDynamic);
			//delete[] lpszDynamic;
		}
		break;

	case WM_TIMER:
		{
		switch (wParam) {
		case ID_TIMER:
			for (auto& ball : *balls)
				ball.Tick();
			InvalidateRect(hWnd, nullptr, true);
			break;
			}
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

void drawBalls(HDC hdc, std::vector<Ball>* balls) {
	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(0xff, 0xff, 0xff));
	hBrush = CreateSolidBrush(RGB(0x00, 0x00, 0xff));

	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	for (auto& ball : *balls)
		ball.Draw(hdc);

	//RECT rcCli;
	//GetClientRect(WindowFromDC(hdc), &rcCli);
	//DPtoLP(hdc, (LPPOINT)&rcCli, 2);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}
