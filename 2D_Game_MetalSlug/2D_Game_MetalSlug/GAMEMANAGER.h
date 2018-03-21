#pragma once
class PLAYER;	//class player�� ������ ���߿� ã����� �̸� ����
class GUN;
class GAMEMANAGER
{
private:
	PLAYER player;
	RECT bulletBoarder;
	RECT tempRect;
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

