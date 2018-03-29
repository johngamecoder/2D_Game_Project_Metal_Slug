#include "stdafx.h"
#include "ENEMY_IMAGE_CONTAINER.h"


ENEMY_IMAGE_CONTAINER::ENEMY_IMAGE_CONTAINER()
{
	Init();
}


ENEMY_IMAGE_CONTAINER::~ENEMY_IMAGE_CONTAINER()
{
	Release();
}

void ENEMY_IMAGE_CONTAINER::Init()
{
	rifle_idle = new Image;
	rifle_idle->init("Image/enemy/rifle/idle/rifle_idle.bmp", 600, 100, 12, 2, true, RGB(255, 0, 255));
	rifle_move = new Image;
	rifle_move->init("Image/enemy/rifle/move/rifle_move.bmp", 700, 100, 14, 2, true, RGB(255, 0, 255));
	rifle_shoot = new Image;
	rifle_shoot->init("Image/enemy/rifle/shoot/rifle_shoot.bmp", 1000, 100, 20, 2, true, RGB(255, 0, 255));
	dead_norm = new Image;
	dead_norm->init("Image/enemy/dead/norm/dead_norm.bmp", 550, 100, 11, 2, true, RGB(255, 0, 255));
}

void ENEMY_IMAGE_CONTAINER::Release()
{
	delete rifle_idle;
	delete rifle_move;
	delete rifle_shoot;
	delete dead_norm;
}
