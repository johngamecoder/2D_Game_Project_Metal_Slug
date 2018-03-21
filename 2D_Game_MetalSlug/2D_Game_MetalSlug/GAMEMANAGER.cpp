#include "stdafx.h"
//#include "GAMEMANAGER.h"
//#include "PLAYER.h"

GAMEMANAGER::GAMEMANAGER()
{
}


GAMEMANAGER::~GAMEMANAGER()
{
}

void GAMEMANAGER::Init()
{
	keyManager::getSingleton()->init();
	player.Init();
	gun = new DEFAULTGUN;
}

void GAMEMANAGER::Update()
{
	//key입력을 받는 부분
	if (keyManager::getSingleton()->isStayKeyDown(VK_LEFT))
	{
		player.pos.left -= player.moveSpeed;
		player.pos.right-= player.moveSpeed;
	}
	if (keyManager::getSingleton()->isStayKeyDown(VK_RIGHT))
	{
		player.pos.left += player.moveSpeed;
		player.pos.right += player.moveSpeed;
	}
	if (keyManager::getSingleton()->isOnceKeyDown(VK_SPACE) && !player.isJump)/*isStayKeyDown(VK_RIGHT)*/
	{
		player.isJump = true;
		player.jumpPower = -(JUMPPOWER);
	}
	
	//player Jump 부분
	if (player.isJump)
		player.Jump();
	else
		if (player.pos.bottom < 350) //이거 잠깐 temp로 쓰자
			player.Gravity();
	


	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	bulletFire();
	//}
	/*bulletMove();
	collision();
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;*/

	//전역으로 놓아둔 hWnd, extern을 사용하는것 매우 중요!
	InvalidateRect(hWnd, 0, true);
}

void GAMEMANAGER::Render(HDC hdc)
{
	//Paint player
	Rectangle(hdc, player.GetPos().left, player.GetPos().top, player.GetPos().right, player.GetPos().bottom);

	//paint Gun
	
	//MoveToEx(hdc, tempGP.startX, tempGP.startY, NULL);	//먼저 hdc를 옴기고 
	//LineTo(hdc, tempGP.endX, tempGP.endY);	//선을 그린다.
}


void GAMEMANAGER::Release()
{
	keyManager::getSingleton()->release();
	delete(gun);
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
