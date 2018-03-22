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
	//player에 관한 setting
	pos.left = PLAYER_POSITION_X;
	pos.top = PLAYER_POSITION_Y;
	pos.right = PLAYER_POSITION_X + PLAYER_SIZE;
	pos.bottom = PLAYER_POSITION_Y + PLAYER_SIZE;
	moveSpeed = PLAYER_MOVE_SPEED;

	//player jump 관련 세팅
	isJump = false;

	//player 총에 관한 setting
	gun = new DEFAULTGUN;
	gun->Init();

	//gun point 관련 세팅
	gunPoints.angle = 0;
	gunPoints.prevAngle = gunPoints.angle;
	gunPoints.isUpKeyPressed = false;
	gunPoints.isDownKeyPressed = false;
}

void PLAYER::Jump()		//- 2차 함수를 사용해서 위로 언덕 방식의 점프를 구현했다.
{
	int tempPower = (jumpPower*jumpPower);

	if (jumpPower >= 0)
		tempPower *= 1;	
	else
		tempPower *= -1;


	pos.top += tempPower;
	pos.bottom += tempPower;

	jumpPower += 0.1f;

	if (jumpPower >= JUMPPOWER)
	{
		isJump = false;
		return;
	}
}

void PLAYER::Gravity()
{
	pos.top += GRAVITY;
	pos.bottom += GRAVITY;
}
