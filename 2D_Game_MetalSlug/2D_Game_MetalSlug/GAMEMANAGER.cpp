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
	//�������� ���Ƶ� hWnd, extern�� ����ϴ°� �ſ� �߿�!
	InvalidateRect(hWnd, 0, true);
	player.setFloorPos(GnO.getFloorPos());

	//key�Է��� �޴� �κ�
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
		keyBoard.leftKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
		keyBoard.rightKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_UP))
		keyBoard.upKeyPressed = true;
	if (keyManager::getSingleton()->isStayKeyDown(VK_DOWN))
		keyBoard.downKeyPressed = true;									//�̺κ��� ��� �ұ�... ���1. �켱 ������ �ϸ� �ٽ� ���� ���ƿö� ���� ������ ���ϰ� �ؾ� ��, ���2 ���� �Ŀ� �� ���� �������� �׿� �°� �� �� ���� �ö󼭰� �Ǿ� ��! Case 2��
	if (keyManager::getSingleton()->isOnceKeyDown(0x57/*'W for jump'*/) && !player.isJump)/*isStayKeyDown(VK_RIGHT)*/
		keyBoard.W_KeyPressed = true;
	if (keyManager::getSingleton()->isOnceKeyDown(0x51/*'Q for shoot'*/))
		keyBoard.Q_KeyPressed = true;
	
	//0x45 /*'E for shoot'*/
	
	//-----------------characters Updates---------------
	player.Update(keyBoard);
	//�ϴ� �̷��� temp�� �ķ��� ������, ���߿� ���� ���� �ٲ�� ��� �޶����� �𸥴�. �׷��� ������ ���Ǹ� ���� �ٽ� �� ������ �غ���
	enemy->Update(player.getPlayerPos(),player.getPlayerBulletPointer(),player.getPlayerBulletNum());

	//--------------------------------------------


	//keyBoard reset
	keyBoard = { 0, };
}

void GAMEMANAGER::Render(HDC hdc)
{
	//=====================Double Buffering =========================//
	HDC memDC = this->getBackBuffer()->getMemDC();
	//��� �� ��Ʈ��
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================================//
	//painting enemy
	enemy->Render(memDC);
	
	//painting Player;
	player.Render(memDC);
	//Rectangle(memDC, tempRect.left, tempRect.left, tempRect.right, tempRect.bottom);

	//paint Gun Handle 
	tempRect = player.getPlayerPos();
	MoveToEx(memDC, player.gunPoints.startX, player.gunPoints.startY, NULL);	//���� hdc�� �ȱ�� 
	LineTo(memDC, player.gunPoints.endX, player.gunPoints.endY);	//���� �׸���.

	//paint bullet
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!player.gun->checkFired(i))
			continue;
		tempRect = player.gun->getBulletPos(i);
		Rectangle(memDC, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	}


	//=================================================================//
	//���ۿ� ������ HDC�� �׸��� �κ�
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
		SetTimer(hWnd, TIMER_ID, 10, nullptr);	//0.01�ʿ� �ѹ�

		break;
	case WM_TIMER:
		this->Update();
		//painting�� �� �ȵǸ� ���⿡ message�� �־ render�� update �� ���ÿ� ����ǵ��� �־ ����� ����
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
	case WM_KEYDOWN:	//�̰� ESC ������ �������ϸ� �����̴� �ʿ������ ���쵵��
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


