// winapi_diffusion.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "winapi_diffusion.h"

#include "Ball.h"

#include <cmath>
#include <ctime>
#include <vector>

#define MAX_LOADSTRING 100

#define W_WIDTH 800
#define W_HEIGHT 600
#define ID_TIMER 1

// Global Variables:
HINSTANCE hInst;								// current instance
WCHAR szTitle[MAX_LOADSTRING];					// The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, LPWSTR, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

//BOOL SetAtrribute(HWND hWnd, int nIndex, LONG value);
void AnimationTick(HWND hWnd, std::vector<Ball>* balls);
void DrawBalls(HDC hdc, std::vector<Ball>* balls);
void PassBall(Ball& ball);
void ReceiveBall(HDC hdc, WPARAM wparam, LPARAM lparam);

//WORKAROUND
BOOL bLeft = TRUE;
HDC hDC;
HWND hWnd_second;
std::vector<Ball>* balls;
UINT msg_connect;
UINT msg_respond;
UINT msg_passball;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPWSTR lpCmdLine,
					_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPI_DIFFUSION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, lpCmdLine, nCmdShow))
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
BOOL InitInstance(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
	  return FALSE;
	}

	srand((unsigned)time(nullptr));

	msg_connect = RegisterWindowMessage(L"CONNECT");
	msg_respond = RegisterWindowMessage(L"RESPOND");
	msg_passball = RegisterWindowMessage(L"PASSBALL");

	balls =  new std::vector<Ball>();

	if (!lstrcmp(lpCmdLine, L"Right"))
		bLeft = FALSE;

	if (bLeft)
	{
		for (int i = 0; i < 64; ++i)
		{
			int px = 640 + rand() % 128;
			int py = -320 + rand() % 128;

			//int px = 0;
			//int py = 0;

			////

			//int vx = rand() % 32;// -32 + rand() % 64;
			//int vy = 0;// -32 + rand() % 64;

			int vx = -32 + rand() % 64;
			int vy = -32 + rand() % 64;

			//int vx = 0;
			//int vy = 0;

			Vector2D<double> position(px, py);
			Vector2D<double> velocity(vx, vy);

			balls->push_back(Ball(bLeft, 60.0, position, velocity));
		}


		SetWindowPos(hWnd, HWND_TOP, 0, 64, W_WIDTH, W_HEIGHT, NULL);
	}
	else
	{
		SetWindowPos(hWnd, HWND_TOP, W_WIDTH, 64, W_WIDTH, W_HEIGHT, NULL);
//		Sleep(50);
//		PostMessage(HWND_BROADCAST, msg_connect, (WPARAM)hWnd, NULL);
	}

	PostMessage(HWND_BROADCAST, msg_connect, (WPARAM)hWnd, (LPARAM)bLeft);
	
	SetTimer(hWnd, ID_TIMER, 10, nullptr);
	SetMenu(hWnd, nullptr);
//	SetWindowText(hWnd, lpCmdLine);	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hDC = GetDC(hWnd);

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
	if (message == msg_connect && !hWnd_second && (BOOL)lParam != bLeft)
	{
		hWnd_second = (HWND)wParam;
		PostMessage(hWnd_second, msg_respond, (WPARAM)hWnd, NULL);

		wchar_t s[100];
		swprintf_s(s, 100, L"Left, hWnd:%lu, hWnd_second:%lu", (unsigned)hWnd, (unsigned)hWnd_second);

		SetWindowText(hWnd, s);
	}
	else if (message == msg_respond)
	{
//		Sleep(1000);
		hWnd_second = (HWND)wParam;

		wchar_t s[100];
		swprintf_s(s, 100, L"Right, hWnd:%lu, hWnd_second:%lu", (unsigned)hWnd, (unsigned)hWnd_second);

		SetWindowText(hWnd, s);

		//Sleep(1000);
	}
	else if (message == msg_passball)
	{
		ReceiveBall(hDC, wParam, lParam);
	}

	switch (message)
	{
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			SetMapMode(hdc, MM_LOMETRIC);
			DrawBalls(hdc, balls);

			EndPaint(hWnd, &ps);
		}
		break;

	case WM_TIMER:
		{
		switch (wParam) {
		case ID_TIMER:
			AnimationTick(hWnd, balls);
			InvalidateRect(hWnd, nullptr, true);

			wchar_t s[100];
			swprintf_s(s, 100, L"Balls: %u", balls->size());

			SetWindowText(hWnd, s);

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

void AnimationTick(HWND hWnd, std::vector<Ball>* balls)
{
	for (auto it = balls->begin(); it != balls->end();)
	{
		it->Move();
		it->HandleCollision(hWnd, hDC, bLeft, balls);

		if (it->NeedPass() && it->GetLeftOwner() == bLeft)
		{
			// Pass to second process
			PassBall(*it);
			it->SetLeftOwner(!bLeft);
		}

		if (it->NeedErase())
			it = balls->erase(it);
		else
			it++;
	}
}

void DrawBalls(HDC hdc, std::vector<Ball>* balls) {
	HPEN hPen;
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(0xff, 0xff, 0xff));
	hBrush = CreateSolidBrush(RGB(0x00, 0x00, 0xff));

	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	for (auto& ball : *balls)
		ball.Draw(hdc);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void PassBall(Ball& ball)
{
	int py = ball.GetCenter().y;
	short vx = ball.GetVelocity().x;
	short vy = ball.GetVelocity().y;

	int v = vx << 8 * sizeof(short) | (unsigned short)vy;

	auto wparam = (WPARAM)py;
	auto lparam = (LPARAM)v;

	PostMessage(hWnd_second, msg_passball, wparam, lparam);
}

void ReceiveBall(HDC hdc, WPARAM wparam, LPARAM lparam)
{
	int py = (int)wparam;
	int v = (int)lparam;
	short vx = v >> 8 * sizeof(short);
	short vy = v;

	RECT rectangle;
	SetMapMode(hdc, MM_LOMETRIC);
	GetClientRect(WindowFromDC(hdc), &rectangle);
	DPtoLP(hdc, (LPPOINT)&rectangle, 2);

	//wchar_t s[100];
	//swprintf_s(s, 100, L"received, py:%d, vx:%hd, vy:%hd,", (int)py, (short)vx, (short)vy);

	//SetWindowText(hWnd, s);

	if (bLeft)
		balls->push_back(Ball(bLeft, 60.0, rectangle.right, py, vx, vy));
	else
		balls->push_back(Ball(bLeft, 60.0, 0.0, py, vx, vy));
}
