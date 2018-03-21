#pragma once
class PLAYER;	//class player�� ������ ���߿� ã����� �̸� ����
class GUN;
class GAMEMANAGER
{
private:
	PLAYER player;
	GUN* gun;
public:
	GAMEMANAGER();
	~GAMEMANAGER();

	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT GameProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

