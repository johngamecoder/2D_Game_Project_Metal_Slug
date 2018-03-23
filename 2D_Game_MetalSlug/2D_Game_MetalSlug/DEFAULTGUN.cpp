#include "stdafx.h"
#include "DEFAULTGUN.h"


DEFAULTGUN::DEFAULTGUN()
{
	Init();
}


DEFAULTGUN::~DEFAULTGUN()
{
}

void DEFAULTGUN::Init()
{
	bulletNum = BULLETMAX;
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i].isFired = false;
		bullet[i].speed = DEFAULTGUNSPEED;
		bullet[i].angle = 0;
	}
}


