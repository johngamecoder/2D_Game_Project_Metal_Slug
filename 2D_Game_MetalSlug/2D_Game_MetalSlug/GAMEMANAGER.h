#pragma once
class PLAYER;	//class player가 있으니 나중에 찾으라고 미리 선언
class GUN;
class GROUNDnOBSTACLE;
class GAMEMANAGER
{
private:
	PLAYER player;
	GROUNDnOBSTACLE GnO;	
	RECT bulletBoarder;	//총이 이 RECT를 넘어가면 초기화하게 된다.
	RECT tempRect;		//intersectRect 를 사용하기 위해 만들어 놓은 various usage temporary Rect
public:
	GAMEMANAGER();
	~GAMEMANAGER();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	
	void playerJump();
	void changeGunPos();
	
};

