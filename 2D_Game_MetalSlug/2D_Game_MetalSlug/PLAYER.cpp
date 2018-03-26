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
	isIdle = false;

	//player 총에 관한 setting
	gun = new DEFAULTGUN;
	gun->Init();

	//gun point 관련 세팅
	gunPoints = {0,0,0,0,0,0,false,false};

	//총알이 화면 주변에서 나갈 경우 이걸로 reset 시켜줌
	bulletBoarder = { 0,0,WINSIZEX ,WINSIZEY };

	//player 이미지
	m_player_top = NULL;
	m_player_bottom = NULL;
	currentFrameX = 0;
	currentFrameY = 0;

	m_idle_top = new Image;
	m_idle_top->init("Image/player/idle_top/idle_top.bmp", 400, 200, 4, 2, true, RGB(255, 0, 255));
	m_shooting_top = new Image;
	m_shooting_top->init("Image/player/shooting_top/shooting_top.bmp", 800, 200, 8, 2, true, RGB(255, 0, 255));
	
	m_walk_leg = new Image;
	m_walk_leg->init("Image/player/walk_leg/walk_leg.bmp", 1200, 200, 12, 2, true, RGB(255, 0, 255));
	m_jump_leg = new Image;
	m_jump_leg->init("Image/player/jump_leg/jump_leg.bmp", 1200, 200, 12, 2, true, RGB(255, 0, 255));
	//m_player_idle.image_top = new Image;
	//m_player_idle.image_bottom = new Image;
	//m_player_idle.image_top->init("Image/player/idle_top/idle_top.bmp", pos.left, pos.top, 400, 200, 4, 2, true, RGB(255, 0, 255));
	//m_player_idle.image_bottom->init("Image/player/jump_leg/jump_leg.bmp",pos.left, pos.top, 800, 200, 8, 2, true, RGB(255, 0, 255));
	//m_player_idle.count = 0;
	//m_player_idle.index = 0;
	//m_player_shoot.image_top = new Image;
	//m_player_shoot.image_bottom = NULL;
	//m_player_shoot.image_top->init("Image/player/shootinig_top/shooting_top.bmp", pos.left, pos.top, 800, 200, 8, 2, true, RGB(255, 0, 255));
	//a = m_player_shoot.image_top;
	//m_player_shoot.count = 0;
	//m_player_shoot.index = 0;
	////m_player_jump.image = new Image;
	////m_player_jump.image->init("Image/player/Jump/Player_Jump.bmp", pos.left, pos.top, 360, 100, 12, 2, true, RGB(255, 0, 255));
	////m_player_jump.count = 0;
	////m_player_jump.index = 0;

}

void PLAYER::Update(tagKEYBOARD keyBoard)
{

	Move(keyBoard.leftKeyPressed, keyBoard.rightKeyPressed, keyBoard.upKeyPressed, keyBoard.downKeyPressed);

	//player Jump & gravity(falling) 부분
	if (keyBoard.W_KeyPressed)
	{
		jumpPower = -(JUMPPOWER);
		isJump = true;
	}
	playerJump();

	//player 총 Handle 부분
	changeGunPos();
	if (keyBoard.Q_KeyPressed)
	{
		gun->BulletFire(gunPoints.endX, gunPoints.endY, gunPoints.angle);
	}
	gun->BulletMove();

	//총이 frame 밖으로 나가면 reset되도록
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &gun->getBulletPos(i)))
			gun->setFired(i, false);
	}


	//m_player_idle.count++;
	//if (m_player_idle.count % 4 == 0)
	//{
	//	m_player_idle.count = 0;
	//	m_player_idle.index--;
	//	if (m_player_idle.index < 0)
	//	{
	//		m_player_idle.index = 4;
	//	}
	//	m_player_idle.image_top->setFrameX(m_player_idle.index);
	//	m_player_idle.image_bottom->setFrameX(m_player_idle.index);
	//}

	//m_player_shoot.count++;
	//if (m_player_shoot.count % 8 == 0)
	//{
	//	m_player_shoot.count = 0;
	//	m_player_shoot.index--;
	//	if (m_player_shoot.index < 0)
	//	{
	//		m_player_shoot.index = 8;
	//	}
	//	m_player_shoot.image_top->setFrameX(m_player_idle.index);
	//}
	
	

}

void PLAYER::runFrame()
{

}
void PLAYER::Render(HDC hdc)
{

	//m_player_idle.image_bottom->frameRender(hdc, pos.left, pos.top + 92);
	//m_player_idle.image_top->frameRender(hdc, pos.left, pos.top+6);
	//m_player_shoot.image_top->frameRender(hdc, pos.left, pos.top);
	///*if (isJump)
	//	m_player_jump.image->frameRender(hdc, pos.left, pos.top);*/
	
	//m_player_bottom->frameRender(hdc, pos.left, pos.top + 92);
	//m_player_top->frameRender(hdc, pos.left, pos.top);
	
}

void PLAYER::Release()
{
	//delete m_player_idle.image_top;
	//delete m_player_idle.image_bottom;
	//delete m_player_shoot.image_top;
	delete gun;
}


void PLAYER::Move(bool leftKeyPressed,bool rightKeyPressed,bool upKeyPressed,bool downKeyPressed)
{
	

	if (leftKeyPressed)
	{
		pos.left -= moveSpeed;
		pos.right -= moveSpeed;
		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		gunPoints.prevAngle = PI;

		////frame control
		currentFrameX = 1;
		//m_player_idle.image_top->setFrameY(1);
		//m_player_idle.image_bottom->setFrameY(1);
		//m_player_shoot.image_top->setFrameY(1);
	}
	if (rightKeyPressed)
	{
		pos.left += moveSpeed;
		pos.right += moveSpeed;

		//이건 총이 anymachinegun 으로 바뀌면 다시 생각해야 할 부분
		gunPoints.prevAngle = 0;
		
		////frame control
		currentFrameY = 0;
		//m_player_idle.image_top->setFrameY(0);
		//m_player_idle.image_bottom->setFrameY(0);
		//m_player_shoot.image_top->setFrameY(0);
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


	//gun의 end point가 angle에 따라 달라지게 만듬
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

void PLAYER::Jump()		//- 2차 함수를 사용해서 위로 언덕 방식의 점프를 구현했다.
{


	//code
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

