#include "stdafx.h"
//#include "GAMEMANAGER.h"
//#include "PLAYER.h"

GAMEMANAGER::GAMEMANAGER()
{
	bulletBoarder.left = 0;
	bulletBoarder.top = 0;
	bulletBoarder.right = WINSIZEX;
	bulletBoarder.bottom = WINSIZEY;
}


GAMEMANAGER::~GAMEMANAGER()
{
}

void GAMEMANAGER::Init()
{
	keyManager::getSingleton()->init();
	player.Init();
	GnO.Init();
}

void GAMEMANAGER::Update()
{
	//�������� ���Ƶ� hWnd, extern�� ����ϴ°� �ſ� �߿�!
	InvalidateRect(hWnd, 0, true);

	//key�Է��� �޴� �κ�
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
	{
		player.pos.left -= player.moveSpeed;
		player.pos.right-= player.moveSpeed;

		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		player.gunPoints.prevAngle = PI+0.01f;	//+0.01f�� �̼� ������ ���Ͽ�
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
	{
		player.pos.left += player.moveSpeed;
		player.pos.right += player.moveSpeed;
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		player.gunPoints.prevAngle = 0;
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_UP))
	{
		player.gunPoints.isUpKeyPressed = true;
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_DOWN))
	{
		player.gunPoints.isDownKeyPressed = true;
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		
	}
	if (keyManager::getSingleton()->isOnceKeyDown(0x57/*'W for jump'*/) && !player.isJump)/*isStayKeyDown(VK_RIGHT)*/
	{
		player.isJump = true;
		player.jumpPower = -(JUMPPOWER);
	}
	if (keyManager::getSingleton()->isOnceKeyDown(0x51/*'Q for shoot'*/))
	{
		player.gun->BulletFire(player.gunPoints.endX,player.gunPoints.endY, player.gunPoints.angle);
	}	 //0x45 /*'E for shoot'*/
	player.gun->BulletMove();

	//player Jump & gravity(falling) �κ�
	playerJump();

	//player gun line 
	changeGunPos();

	//���� frame ������ ������ reset�ǵ���
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &player.gun->getBulletPos(i)))
			player.gun->setFired(i, false);
	}
	
	

}

void GAMEMANAGER::Render(HDC hdc)
{
	//Paint player
	Rectangle(hdc, player.pos.left, player.pos.top, player.pos.right, player.pos.bottom);

	//paint Gun
	MoveToEx(hdc, player.gunPoints.startX, player.gunPoints.startY, NULL);	//���� hdc�� �ȱ�� 
	LineTo(hdc, player.gunPoints.endX, player.gunPoints.endY);	//���� �׸���.

	//paint bullet
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!player.gun->checkFired(i))
			continue;
		tempRect = player.gun->getBulletPos(i);
		Rectangle(hdc, tempRect.left, tempRect.top, tempRect.right, tempRect.bottom);
	}
	
}


void GAMEMANAGER::Release()
{
	keyManager::getSingleton()->release();
	delete(player.gun);
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

void GAMEMANAGER::playerJump()
{
	//printf("player.pos.bottom : %d\n", player.pos.bottom);
	if (player.isJump)
	{
		player.Jump();
		
		//printf("player.pos.bottom : %d\n", player.pos.bottom);
	}
	else if(!IntersectRect(&tempRect,&player.pos,&GnO.getFloorPos()))
	{
		player.Gravity();
	}
		
}

void GAMEMANAGER::changeGunPos()
{
	player.gunPoints.startX = player.pos.left + (PLAYER_SIZE / 2);
	player.gunPoints.startY = player.pos.top + (PLAYER_SIZE / 2);
	

	//gun�� end point�� angle�� ���� �޶����� ����
	if (player.gunPoints.isUpKeyPressed || player.gunPoints.isDownKeyPressed)
	{
		if (player.gunPoints.isUpKeyPressed)
		{
			player.gunPoints.angle = PI / 2;
			player.gunPoints.isUpKeyPressed = false;
		}
		else 
		{
			player.gunPoints.angle = PI + (PI / 2)+0.01f;	//�̼����� 0.01f
			player.gunPoints.isDownKeyPressed = false;
		}
	}
	else
		player.gunPoints.angle = player.gunPoints.prevAngle;
		
		
	player.gunPoints.endX = cosf(player.gunPoints.angle)*PLAYER_SIZE + player.gunPoints.startX;
	player.gunPoints.endY = -(sinf(player.gunPoints.angle)*PLAYER_SIZE) + player.gunPoints.startY;
}