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
	//key�Է��� �޴� �κ�
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
	
	//player Jump �κ�
	if (player.isJump)
		player.Jump();
	else
		if (player.pos.bottom < 350) //�̰� ��� temp�� ����
			player.Gravity();
	


	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	bulletFire();
	//}
	/*bulletMove();
	collision();
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;*/

	//�������� ���Ƶ� hWnd, extern�� ����ϴ°� �ſ� �߿�!
	InvalidateRect(hWnd, 0, true);
}

void GAMEMANAGER::Render(HDC hdc)
{
	//Paint player
	Rectangle(hdc, player.GetPos().left, player.GetPos().top, player.GetPos().right, player.GetPos().bottom);

	//paint Gun
	
	//MoveToEx(hdc, tempGP.startX, tempGP.startY, NULL);	//���� hdc�� �ȱ�� 
	//LineTo(hdc, tempGP.endX, tempGP.endY);	//���� �׸���.
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
