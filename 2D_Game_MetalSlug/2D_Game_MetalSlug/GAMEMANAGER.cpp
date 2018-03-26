#include "stdafx.h"
//#include "GAMEMANAGER.h"
//#include "PLAYER.h"

void GAMEMANAGER::setBackBuffer()
{
	m_backbuffer = new Image;
	m_backbuffer->init(WINSIZEX, WINSIZEY);
}

GAMEMANAGER::GAMEMANAGER()
{
}


GAMEMANAGER::~GAMEMANAGER()
{
}

void GAMEMANAGER::Init()
{
	keyManager::getSingleton()->init();
	keyBoard = { 0, };
	
	setBackBuffer();

	mousePoint = { 0,0 };

	player.Init();
	GnO.Init();


	enemy = new SOLDIER;
	enemy->Init();
	
}

void GAMEMANAGER::Update()
{
	//전역으로 놓아둔 hWnd, extern을 사용하는것 매우 중요!
	InvalidateRect(hWnd, 0, true);
	player.setFloorPos(GnO.getFloorPos());

	//key입력을 받는 부분
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
		keyBoard.leftKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
		keyBoard.rightKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_UP))
		keyBoard.upKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_DOWN))
		keyBoard.downKeyPressed = true;									//이부분을 어떻게 할까... 고민1. 우선 점프를 하면 다시 땅에 돌아올때 까지 점프를 못하게 해야 함, 고민2 점프 후에 돌 위로 떨어지면 그에 맞게 또 돌 위에 올라서게 되야 함! Case 2개
	if (keyManager::getSingleton()->isOnceKeyDown(0x57/*'W for jump'*/) && !player.isJump)/*isStayKeyDown(VK_RIGHT)*/
		keyBoard.W_KeyPressed = true;
	if (keyManager::getSingleton()->isOnceKeyDown(0x51/*'Q for shoot'*/))
		keyBoard.Q_KeyPressed = true;
	
	//0x45 /*'E for shoot'*/
	
	//-----------------characters Updates---------------
	player.Update(keyBoard);
	//일단 이렇게 temp로 후려쳐 놨지만, 나중에 가서 총이 바뀌면 어떻게 달라질지 모른다. 그러니 윤성우 강의를 보고 다시 재 정립을 해보자
	enemy->Update(player.getPlayerPos(),player.getPlayerBulletPointer(),player.getPlayerBulletNum());

	//--------------------------------------------


	//keyBoard reset
	keyBoard = { 0, };
}

void GAMEMANAGER::Render(HDC hdc)
{
	//=====================Double Buffering =========================//
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================================//
	//painting enemy
	enemy->Render(memDC);
	
	//painting Player;
	player.Render(memDC);
	//Rectangle(memDC, tempRect.left, tempRect.left, tempRect.right, tempRect.bottom);

	//paint Gun Handle 
	tempRect = player.getPlayerPos();
	MoveToEx(memDC, player.gunPoints.startX, player.gunPoints.startY, NULL);	//먼저 hdc를 옴기고 
	LineTo(memDC, player.gunPoints.endX, player.gunPoints.endY);	//선을 그린다.

	//paint bullet
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!player.gun->checkFired(i))
			continue;
		tempRect = player.gun->getBulletPos(i);
		Rectangle(memDC, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	}


	//=================================================================//
	//백퍼에 내용을 HDC에 그리는 부분
	this->getBackBuffer()->render(hdc, 0, 0);
	//=================================================================//
}


void GAMEMANAGER::Release()
{
	keyManager::getSingleton()->release();
	player.Release();

	delete(enemy);
	delete(m_backbuffer);
}

LRESULT GAMEMANAGER::GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, TIMER_ID, 10, nullptr);	//0.01초에 한번

		break;
	case WM_TIMER:
		this->Update();
		//painting이 잘 안되면 여기에 message를 넣어서 render도 update 와 동시에 실행되도록 넣어서 사용해 보자
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->Render(hdc);
		EndPaint(hWnd, &ps);
		break;
	//case WM_MOUSEMOVE:
	//	mousePoint.x = LOWORD(lParam);
	//	mousePoint.y = HIWORD(lParam);
	//	printf("X: %d  Y: %d \n", mousePoint.x, mousePoint.y);
	//	break;
	case WM_KEYDOWN:	//이건 ESC 누르면 끝나도록만 쓸것이니 필요없으면 지우도록
		switch (wParam)
		{
			{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
			}
		}break;
	case WM_DESTROY:
		
		KillTimer(hWnd, 123);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
	return 0;
}


