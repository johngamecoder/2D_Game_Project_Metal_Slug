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
	//player�� ���� setting
	pos.left = PLAYER_POSITION_X;
	pos.top = PLAYER_POSITION_Y;
	pos.right = PLAYER_POSITION_X + PLAYER_SIZE;
	pos.bottom = PLAYER_POSITION_Y + PLAYER_SIZE;
	moveSpeed = PLAYER_MOVE_SPEED;

	//player jump ���� ����
	isJump = false;

	//player �ѿ� ���� setting
	gun = new DEFAULTGUN;
	gun->Init();

	//gun point ���� ����
	gunPoints = {0,0,0,0,0,0,false,false};

	//�Ѿ��� ȭ�� �ֺ����� ���� ��� �̰ɷ� reset ������
	bulletBoarder = { 0,0,WINSIZEX ,WINSIZEY };
}

void PLAYER::Update(tagKEYBOARD keyBoard)
{
	Move(keyBoard.leftKeyPressed, keyBoard.rightKeyPressed, keyBoard.upKeyPressed, keyBoard.downKeyPressed);
	
	//player Jump & gravity(falling) �κ�
	if (keyBoard.W_KeyPressed)
	{
		jumpPower = -(JUMPPOWER);
		isJump = true;
	}
	playerJump();

	//player �� Handle �κ�
	changeGunPos();
	if (keyBoard.Q_KeyPressed)
	{
		gun->BulletFire(gunPoints.endX, gunPoints.endY, gunPoints.angle);
	}
	gun->BulletMove();

	//���� frame ������ ������ reset�ǵ���
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &gun->getBulletPos(i)))
			gun->setFired(i, false);
	}
}

void PLAYER::Move(bool leftKeyPressed,bool rightKeyPressed,bool upKeyPressed,bool downKeyPressed)
{
	if (leftKeyPressed)
	{
		pos.left -= moveSpeed;
		pos.right -= moveSpeed;
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		gunPoints.prevAngle = PI;	
	}
	if (rightKeyPressed)
	{
		pos.left += moveSpeed;
		pos.right += moveSpeed;

		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		gunPoints.prevAngle = 0;
	}
	if (upKeyPressed)
	{
		gunPoints.isUpKeyPressed = true;
	}
	if (downKeyPressed)
	{
		gunPoints.isDownKeyPressed = true;
	}
	
}

void PLAYER::playerJump()
{
	if (isJump)
	{
		Jump();
	}
	else if (!IntersectRect(&tempRect, &pos, &floorPos))
	{
		Gravity();
	}

}

RECT PLAYER::getPlayerPos()
{
	return pos;
}

tagBULLET * PLAYER::getPlayerBulletPointer()
{
	return gun->getBulletPointer();
}

int PLAYER::getPlayerBulletNum()
{
	return gun->getBulletNum();
}

void PLAYER::changeGunPos()
{
	gunPoints.startX = pos.left + (PLAYER_SIZE / 2);
	gunPoints.startY = pos.top + (PLAYER_SIZE / 2);


	//gun�� end point�� angle�� ���� �޶����� ����
	if (gunPoints.isUpKeyPressed || gunPoints.isDownKeyPressed)
	{
		if (gunPoints.isUpKeyPressed)
		{
			gunPoints.angle = PI / 2;
			gunPoints.isUpKeyPressed = false;
		}
		else
		{
			gunPoints.angle = PI + (PI / 2);	
			gunPoints.isDownKeyPressed = false;
		}
	}
	else
		gunPoints.angle = gunPoints.prevAngle;


	gunPoints.endX = cosf(gunPoints.angle)*PLAYER_SIZE + gunPoints.startX;
	gunPoints.endY = -(sinf(gunPoints.angle)*PLAYER_SIZE) + gunPoints.startY;
}

void PLAYER::Jump()		//- 2�� �Լ��� ����ؼ� ���� ��� ����� ������ �����ߴ�.
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

void PLAYER::setFloorPos(RECT _floorPos)
{
	floorPos = _floorPos;
}

