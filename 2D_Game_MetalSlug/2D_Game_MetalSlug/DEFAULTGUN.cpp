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
	
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet->isFired = false;
		bullet->speed = DEFAULTGUNSPEED;
		bullet->angle = 0;
	}
}