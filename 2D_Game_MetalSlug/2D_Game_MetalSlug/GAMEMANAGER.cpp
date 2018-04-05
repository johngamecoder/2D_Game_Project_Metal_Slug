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

	//EIC = new ENEMY_IMAGE_CONTAINER;
	//for (int i = 0; i < ENEMY_INSTANCE_NUM; i++)
	//{
	//	enemy[i].ptr	= new SOLDIER;
	//	enemy[i].ptr->_m_ = EIC;
	//	enemy[i].isOff = false;
	//	enemy[i].ptr->Init(700+(i*20));
	//}
	//enemy = new SOLDIER;
	//enemy->_m_ = EIC;
	//enemy->Init();

	boss.Init();
	
	vertical_line = 500;
	boss_line = 500;
}

void GAMEMANAGER::Update()
{
	//�������� ���Ƶ� hWnd, extern�� ����ϴ°� �ſ� �߿�!
	InvalidateRect(hWnd, 0, false);	//�� �ڿ� true false ���� true�� ��� ���� �ٲٴ°�, false�� �ٲ�� �͸� �׷��ִ°�
	
	player.setFloorPos(GnO.floorPos);
	player_Pos = player.getPlayerPos();
	//key�Է��� �޴� �κ�
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
	{
		if (player.pos.left > 0)	//window ���� screen�� ������ �ڷ� ���ư�����
		{
			player.pos.left -= PLAYER_MOVE_SPEED;
			player.pos.right -= PLAYER_MOVE_SPEED;
		}
		else
		{
			//background move
			//GnO.front_background_pos.x += PLAYER_MOVE_SPEED;
			//GnO.back_background_pos.x += PLAYER_MOVE_SPEED / 2;
			//move enemy
			//���� enemy���� ���� ����� ���� ���⿡�� for �� �����鼭 �����̵��� ����!
			//if (!enemy->_E.isDead)
			//{
			//	enemy->_E.Pos.left += PLAYER_MOVE_SPEED;
			//	enemy->_E.Pos.right += PLAYER_MOVE_SPEED;
			//}
		}
			
			
		keyBoard.leftKeyPressed = true;
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
	{
		if (vertical_line - player.pos.right > 0)	//vertical line �������� �Ѿ�� background �� �����̵���
		{
			player.pos.left += PLAYER_MOVE_SPEED;
			player.pos.right += PLAYER_MOVE_SPEED;
		}
		else
		{
			//background move
			if (vertical_line < boss_line)
			{
				GnO.front_background_pos.x -= PLAYER_MOVE_SPEED;
				GnO.back_background_pos.x -= PLAYER_MOVE_SPEED / 2;
				boss_line -= PLAYER_MOVE_SPEED;
			}

			////move enemy
			////���߿���enemy->_E.isDead �� false �� ����鸸 �����̰� ����!
			//for (int i = 0; i < ENEMY_INSTANCE_NUM; i++)
			//{
			//	if (!enemy[i].isOff)
			//	{
			//		if (!enemy[i].ptr->_E.isDead)
			//		{
			//			enemy[i].ptr->_E.Pos.left -= PLAYER_MOVE_SPEED;
			//			enemy[i].ptr->_E.Pos.right -= PLAYER_MOVE_SPEED;
			//		}
			//	}
			//	
			//}
			//if (!enemy->_E.isDead)
			//{
			//	enemy->_E.Pos.left -= PLAYER_MOVE_SPEED;
			//	enemy->_E.Pos.right -= PLAYER_MOVE_SPEED;
			//}
		}
		keyBoard.rightKeyPressed = true;
	}
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
	////�ϴ� �̷��� temp�� �ķ��� ������, ���߿� ���� ���� �ٲ�� ��� �޶����� �𸥴�. �׷��� ������ ���Ǹ� ���� �ٽ� �� ������ �غ���
	//for (int i = 0; i < ENEMY_INSTANCE_NUM; i++)
	//{
	//	if(!enemy[i].isOff)
	//		enemy[i].ptr->Update(player_Pos, player.getPlayerBulletPointer(), player.getPlayerBulletNum());
	//	enemy[i].isOff = enemy[i].ptr->isOff;
	//}
	
	
	//if(vertical_line>=boss_line)
	//	boss.Update(player.pos,GnO.floorPos);
	boss.Update(player.pos, GnO.floorPos, player.getPlayerBulletPointer(), player.getPlayerBulletNum());	//�̰� ���� �������� (���� ����� ���� ���� Ǯ���)
	//------------------background Updates----------------

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
	
	//if (vertical_line >= boss_line)
	//	boss.Render(memDC);
	boss.Render(memDC);	//�̰� ���� ��������

						//floor rectangel
	//Rectangle(memDC, GnO.floorPos.left, GnO.floorPos.top, GnO.floorPos.right, GnO.floorPos.bottom);
	GnO.Render(memDC);
	////painting enemy
	//for (int i = 0; i < ENEMY_INSTANCE_NUM; i++)
	//{
	//	if(!enemy[i].isOff)
	//		enemy[i].ptr->Render(memDC);
	//}
	


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

	MoveToEx(memDC, vertical_line, 0, NULL);
	LineTo(memDC, vertical_line, 800);
	MoveToEx(memDC, boss_line, 0, NULL);
	LineTo(memDC, boss_line, 800);
	//=================================================================//
	//���ۿ� ������ HDC�� �׸��� �κ�
	this->getBackBuffer()->render(hdc, 0, 0);
	//=================================================================//
}

void GAMEMANAGER::Release()
{
	keyManager::getSingleton()->release();
	player.Release();
	//for (int i = 0; i < ENEMY_INSTANCE_NUM; i++)
	//{
	//	enemy[i].ptr->Release();
	//}
	//
	GnO.Release();
	boss.Release();
	delete EIC;
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
