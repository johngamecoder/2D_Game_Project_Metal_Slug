//// 2D_Game_MetalSlug.cpp : Defines the entry point for the application.
////
//
#include "stdafx.h"


HWND hWnd;	//윈도우 헨들
HINSTANCE g_hInst;

GAMEMANAGER* gameManager;	//game manager
MSG Message;	//Message.pt.x ,y 가 마우스 포인터이니 이거 써보자

void setWindowSize(int x, int y, int width, int Height);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LPCWSTR lpszClass = L"Metal Slug";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	//WndClass 정의
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = (LPCSTR)lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);


	//Create Window
	hWnd = CreateWindow((LPCSTR)lpszClass, (LPCSTR)lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	gameManager = new GAMEMANAGER;
	gameManager->Init();

	//show window
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(hWnd, nCmdShow);

	//메세지 루프
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	//게임 메니저 Release();
	gameManager->Release();
	delete(gameManager);
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return gameManager->GameProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int Height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = Height;
	// 실제 윈도우 크기조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);

}







//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//	case WM_CREATE:
//		gameManager = new GAMEMANAGER;
//
//		break;
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // Parse the menu selections:
//            switch (wmId)
//            {
//            //case IDM_ABOUT:
//            //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//            //    break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: Add any drawing code that uses hdc here...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
