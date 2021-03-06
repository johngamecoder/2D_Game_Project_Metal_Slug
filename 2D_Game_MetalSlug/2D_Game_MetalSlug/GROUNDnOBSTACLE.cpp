#include "stdafx.h"


GROUNDnOBSTACLE::GROUNDnOBSTACLE()
{
}


GROUNDnOBSTACLE::~GROUNDnOBSTACLE()
{
}

void GROUNDnOBSTACLE::Init()
{
	floorPos = { 0,570,WINSIZEX,WINSIZEY };

	front_background_pos={ -4800,0};
	m_front_background = new Image;
	m_front_background->init("Image/background/front_background_test.bmp", 6114, 672, true, RGB(255, 0, 255));
	//m_front_background->init("Image/background/front_background.bmp", 1950, 360, true, RGB(255, 0, 255));

	back_background_pos = { 0,0 };
	m_back_background = new Image;
	m_back_background->init("Image/background/back_background_test.bmp", 4500, 480);
	//m_back_background->init("Image/background/back_background.bmp", 1500, 160);
}

//void GROUNDnOBSTACLE::Update(long left,int vertical_line)
//{
//	//if (vertical_line - left>0)
//	//	front_background_pos.x += 3;
//	//if (left > 0)
//	//	front_background_pos.x -= 3;
//}


void GROUNDnOBSTACLE::Render(HDC hdc)
{
	//m_back_background->render(hdc, back_background_pos.x, back_background_pos.y);
	m_front_background->render(hdc, front_background_pos.x, front_background_pos.y);
}

void GROUNDnOBSTACLE::Release()
{
	delete m_front_background;
	delete m_back_background;
}

RECT GROUNDnOBSTACLE::getFloorPos()
{
	return floorPos;
}
