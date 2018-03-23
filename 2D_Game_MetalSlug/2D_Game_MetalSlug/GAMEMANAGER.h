#pragma once
#include "Image.h"

class PLAYER;	//class player�� ������ ���߿� ã����� �̸� ����
class GUN;
class GROUNDnOBSTACLE;
class ENEMY;



class GAMEMANAGER
{
private:
	PLAYER player;
	GROUNDnOBSTACLE GnO;	
	
	
	//Enemy
	ENEMY* enemy;
	RECT tempRect;		//intersectRect �� ����ϱ� ���� ����� ���� various usage temporary Rect
	
private:
	tagKEYBOARD keyBoard;
	POINT mousePoint;

	Image * m_backbuffer; //�����
	void setBackBuffer(); //����� ���� �Լ�

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

