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
	//전역으로 놓아둔 hWnd, extern을 사용하는것 매우 중요!
	InvalidateRect(hWnd, 0, true);

	//key입력을 받는 부분
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
	{
		player.pos.left -= player.moveSpeed;
		player.pos.right-= player.moveSpeed;

		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		player.gunPoints.prevAngle = PI+0.01f;	//+0.01f는 미세 조정을 위하여
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
	{
		player.pos.left += player.moveSpeed;
		player.pos.right += player.moveSpeed;
		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		player.gunPoints.prevAngle = 0;
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_UP))
	{
		player.gunPoints.isUpKeyPressed = true;
		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_DOWN))
	{
		player.gunPoints.isDownKeyPressed = true;
		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		
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

	//player Jump & gravity(falling) 부분
	playerJump();

	//player gun line 
	changeGunPos();

	//총이 frame 밖으로 나가면 reset되도록
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
	MoveToEx(hdc, player.gunPoints.startX, player.gunPoints.startY, NULL);	//먼저 hdc를 옴기고 
	LineTo(hdc, player.gunPoints.endX, player.gunPoints.endY);	//선을 그린다.

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
	

	//gun의 end point가 angle에 따라 달라지게 만듬
	if (player.gunPoints.isUpKeyPressed || player.gunPoints.isDownKeyPressed)
	{
		if (player.gunPoints.isUpKeyPressed)
		{
			player.gunPoints.angle = PI / 2;
			player.gunPoints.isUpKeyPressed = false;
		}
		else 
		{
			player.gunPoints.angle = PI + (PI / 2)+0.01f;	//미세조정 0.01f
			player.gunPoints.isDownKeyPressed = false;
		}
	}
	else
		player.gunPoints.angle = player.gunPoints.prevAngle;
		
		
	player.gunPoints.endX = cosf(player.gunPoints.angle)*PLAYER_SIZE + player.gunPoints.startX;
	player.gunPoints.endY = -(sinf(player.gunPoints.angle)*PLAYER_SIZE) + player.gunPoints.startY;
}