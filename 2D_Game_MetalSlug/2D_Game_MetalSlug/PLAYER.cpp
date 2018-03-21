#include "stdafx.h"
//#include "PLAYER.h"


PLAYER::PLAYER()
{
}


PLAYER::~PLAYER()
{
}

void PLAYER::Init()
{
	gravity = 3.0f;
	isJump = false;
	
	SetPos(200, 300, 250, 350);
	moveSpeed = 3;

}

void PLAYER::Jump()		//- 2차 함수를 사용해서 위로 언덕 방식의 점프를 구현했다.
{
	jumpPower += 0.1f;
	int tempPower = (jumpPower*jumpPower);
	if (jumpPower >= 0)
		tempPower *= 1;	
	else
		tempPower *= -1;

	pos.top += tempPower;
	pos.bottom += tempPower;

	if (jumpPower > JUMPPOWER)
		isJump = false;

}

void PLAYER::Gravity()
{
	pos.top += gravity;
	pos.bottom += gravity;
}
