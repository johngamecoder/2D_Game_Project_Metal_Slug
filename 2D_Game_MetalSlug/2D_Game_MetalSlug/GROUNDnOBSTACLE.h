#pragma once
class GROUNDnOBSTACLE
{
public:
	POINT front_background_pos;	//front_background position
	POINT back_background_pos;	//back_background position

	RECT floorPos;

private:
	Image* m_front_background;
	Image* m_back_background;


public:
	GROUNDnOBSTACLE();
	~GROUNDnOBSTACLE();

	void Init();
	//void Update(long,int);
	void Render(HDC);
	void Release();
	RECT getFloorPos();
};

