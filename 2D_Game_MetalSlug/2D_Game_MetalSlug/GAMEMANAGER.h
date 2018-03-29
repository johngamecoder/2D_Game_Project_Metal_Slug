#pragma once
#include "Image.h"

class PLAYER;	//class player�� ������ ���߿� ã����� �̸� ����
class GUN;
class GROUNDnOBSTACLE;
class ENEMY;
class BOSS;

#define PLAYER_MOVE_SPEED 2

class GAMEMANAGER
{
	//����ϴ� class �� has-a ����
private:
	PLAYER player;
	GROUNDnOBSTACLE GnO;
	BOSS boss;
	//Enemy
	ENEMY* enemy;
	RECT tempRect;		//intersectRect �� ����ϱ� ���� ����� ���� various usage temporary Rect
	
private:
	tagKEYBOARD keyBoard;
	POINT mousePoint;

	int vertical_line;
	
	int boss_line; 

	Image * m_backbuffer; //�����
	void setBackBuffer(); //����� ���� �Լ�

public:
	RECT player_Pos;

public:
	GAMEMANAGER();
	~GAMEMANAGER();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	//����� ������
	Image* getBackBuffer() { return m_backbuffer; }
	
};

