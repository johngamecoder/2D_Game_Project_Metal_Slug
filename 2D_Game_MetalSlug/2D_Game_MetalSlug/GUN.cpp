#include "stdafx.h"
#include "GUN.h"


GUN::GUN()
{
}


GUN::~GUN()
{
}

void GUN::Init()
{

}

void GUN::BulletFire(int gunEndX, int gunEndY, float angle)
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].isFired)
		{
			bullet[i].isFired = true;
			bullet[i].pos.left = gunEndX;
			bullet[i].pos.top = gunEndY;
			bullet[i].pos.right = bullet[i].pos.left + BULLET_SIZE;
			bullet[i].pos.bottom = bullet[i].pos.top + BULLET_SIZE;
			bullet[i].angle = angle;
			break;
		}
	}
}

void GUN::BulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!bullet[i].isFired) 
			continue;

		bullet[i].pos.left += cosf(bullet[i].angle) * bullet[i].speed;
		bullet[i].pos.top += -sinf(bullet[i].angle) * bullet[i].speed;
		bullet[i].pos.right = bullet[i].pos.left + BULLET_SIZE;
		bullet[i].pos.bottom = bullet[i].pos.top + BULLET_SIZE;
	}
}

RECT GUN::getBulletPos(int n)
{
	return bullet[n].pos;
}

bool GUN::checkFired(int n)
{
	return bullet[n].isFired;
}

void GUN::setFired(int n, bool b)
{
	bullet[n].isFired = b;
}

