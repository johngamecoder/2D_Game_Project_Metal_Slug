#pragma once
#include "Image.h"

class PLAYER;	//class player가 있으니 나중에 찾으라고 미리 선언
class GUN;
class GROUNDnOBSTACLE;
class ENEMY;
class BOSS;

#define PLAYER_MOVE_SPEED 2

class GAMEMANAGER
{
	//사용하는 class 들 has-a 관계
private:
	PLAYER player;
	GROUNDnOBSTACLE GnO;
	BOSS boss;
	//Enemy
	ENEMY* enemy;
	RECT tempRect;		//intersectRect 를 사용하기 위해 만들어 놓은 various usage temporary Rect
	
private:
	tagKEYBOARD keyBoard;
	POINT mousePoint;

	int vertical_line;
	
	int boss_line; 

	Image * m_backbuffer; //백버퍼
	void setBackBuffer(); //백버퍼 세팅 함수

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
	
	//백버퍼 얻어오기
	Image* getBackBuffer() { return m_backbuffer; }
	
};

