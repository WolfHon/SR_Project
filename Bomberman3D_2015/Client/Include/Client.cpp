#include "stdafx.h"
#include "Client.h"

#include "MainApp.h"
#include "Include.h"
#include "Engine_Function.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;								
TCHAR szTitle[MAX_LOADSTRING];					
TCHAR szWindowClass[MAX_LOADSTRING];
HWND g_hWnd;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(274);

	/*if (AllocConsole())
	{
	freopen("CONOUT$", "wb", stdout);
	}*/
#endif

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	
	MSG msg;
	msg.message = WM_NULL;
	HACCEL hAccelTable;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

	CMainApp*	pMainApp = CMainApp::Create();
	if(pMainApp == NULL)
		return 0;

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		pMainApp->Update();
		pMainApp->Render();
	}

	Engine::Safe_Delete(pMainApp);

#ifdef _DEBUG
	//FreeConsole();
#endif

	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	RECT rc = {0, 0, WINCX, WINCY};

	hInst = hInstance;
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

#ifdef _DEBUG
	hWnd = CreateWindow(szWindowClass, szTitle, /*WS_POPUPWINDOW*/WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN) / 2 - WINCX / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WINCY / 2,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	//hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUPWINDOW, GetSystemMetrics(SM_CXSCREEN) + GetSystemMetrics(SM_CXSCREEN) / 2 - WINCX / 2,
	//	GetSystemMetrics(SM_CYSCREEN) / 2 - WINCY / 2, WINCX, WINCY, NULL, NULL, hInstance, NULL);
#else
	hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUPWINDOW, GetSystemMetrics(SM_CXSCREEN) / 2 - WINCX / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - WINCY / 2,
		rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
#endif

	if (!hWnd)
		return FALSE;

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

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
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);		
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