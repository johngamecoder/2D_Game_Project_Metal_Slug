#pragma once
class PLAYER;	//class player�� ������ ���߿� ã����� �̸� ����
class GUN;
class GROUNDnOBSTACLE;
class GAMEMANAGER
{
private:
	PLAYER player;
	GROUNDnOBSTACLE GnO;	
	RECT bulletBoarder;	//���� �� RECT�� �Ѿ�� �ʱ�ȭ�ϰ� �ȴ�.
	RECT tempRect;		//intersectRect �� ����ϱ� ���� ����� ���� various usage temporary Rect
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

