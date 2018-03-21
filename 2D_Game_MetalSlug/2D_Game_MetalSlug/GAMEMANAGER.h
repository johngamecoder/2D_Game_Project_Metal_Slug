#pragma once
class PLAYER;	//class player가 있으니 나중에 찾으라고 미리 선언
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

