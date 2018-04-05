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


	//player jump ���� ����
	isJump = false;
	isfired = false;


	//player �ѿ� ���� setting
	gun = new DEFAULTGUN;
	gun->Init();

	//gun point ���� ����
	gunPoints = {0,0,0,0,0,0,false,false};

	//�Ѿ��� ȭ�� �ֺ����� ���� ��� �̰ɷ� reset ������
	bulletBoarder = { 0,0,WINSIZEX ,WINSIZEY };

	//player �̹���
	m_player_top = NULL;
	m_player_bottom = NULL;
	currentFrameY = 0;
	playerState = 0;
	
	//top
	m_idle_top = new Image;
	m_idle_top->init("Image/player/idle_top/idle_top.bmp", 1200, 600, 4, 2, true, RGB(255, 0, 255));
	m_shooting_top = new Image;
	m_shooting_top->init("Image/player/shooting_top/shooting_top.bmp", 2400, 600, 8, 2, true, RGB(255, 0, 255));
	m_shootdown_top = new Image;
	m_shootdown_top->init("Image/player/shootdown_top/shootdown_top.bmp", 1800, 600, 6, 2, true, RGB(255, 0, 255));
	m_shootup_top = new Image;
	m_shootup_top->init("Image/player/shootup_top/shootup_top.bmp", 1800, 600, 6, 2, true, RGB(255, 0, 255));
	
	//leg
	m_idle_leg = new Image;
	m_idle_leg->init("Image/player/idle_leg/idle_leg.bmp", 300, 600, 1, 2, true, RGB(255, 0, 255));
	m_walk_leg = new Image;
	m_walk_leg->init("Image/player/walk_leg/walk_leg.bmp", 3600, 600, 12, 2, true, RGB(255, 0, 255));
	m_jump_leg = new Image;
	m_jump_leg->init("Image/player/jump_leg/jump_leg.bmp", 2400, 600, 8, 2, true, RGB(255, 0, 255));


}

void PLAYER::Update(tagKEYBOARD keyBoard)
{

	Move(keyBoard.leftKeyPressed, keyBoard.rightKeyPressed, keyBoard.upKeyPressed, keyBoard.downKeyPressed);

	//player Jump & gravity(falling) �κ�
	if (keyBoard.W_KeyPressed)
	{
		jumpPower = -(JUMPPOWER);
		isJump = true;
		frameTemp = 0;
	}
	playerJump();

	//player �� Handle �κ�
	changeGunPos();
	if (keyBoard.Q_KeyPressed)
	{
		gun->BulletFire(gunPoints.endX, gunPoints.endY, gunPoints.angle);
		isfired = true;
		frameTemp = 0;
	}
	gun->BulletMove();



	//���� frame ������ ������ reset�ǵ���	//�̰� ��� 5�� �Ҹ���! Ȯ���غ��� ��ó��!
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!IntersectRect(&tempRect, &bulletBoarder, &gun->getBulletPos(i)))
			gun->setFired(i, false);
	}


	//state change
	if (isfired)
		playerState += T_SHOOTING;

	//FrameX count + Ÿ�̸ӵ����� ���
	frame_count++;
	if (frame_count % 10 == 0)
	{
		frameTemp++;
		if (frame_count % 80 == 0)
			isfired = false;
	}

}

void PLAYER::Render(HDC hdc)
{
	switch (playerState)
	{
	case idle_idle:	//�̰� ���߿� �� �ڷ� �Ұ���
		m_player_top	= m_idle_top;
		Top_currentFrameX = frameTemp % 4;	//�̹��� X ������ ��ŭ �������̴�.
		m_player_bottom = m_idle_leg;
		Bottom_currentFrameX = 0;
		break;
	case idle_walk:
		m_player_top	= m_idle_top;
		Top_currentFrameX = frameTemp % 4;
		m_player_bottom = m_walk_leg;
		Bottom_currentFrameX = frameTemp % 12;
		break;
	case idle_jump:
		m_player_top	= m_idle_top;
		Top_currentFrameX = frameTemp % 4;
		m_player_bottom = m_jump_leg;
		Bottom_currentFrameX = frameTemp % 8;
		break;

	case shooting_idle:
		m_player_top	= m_shooting_top;
		Top_currentFrameX = frameTemp % 8;
		m_player_bottom = m_idle_leg;
		Bottom_currentFrameX = 0;
		break;
	case shooting_walk:
		m_player_top	= m_shooting_top;
		Top_currentFrameX = frameTemp % 8;
		m_player_bottom = m_walk_leg;
		Bottom_currentFrameX = frameTemp % 12;
		break;
	case shooting_jump:
		m_player_top		= m_shooting_top;
		Top_currentFrameX = frameTemp % 8;
		m_player_bottom = m_jump_leg;
		Bottom_currentFrameX = frameTemp % 8;
		break;

	case shootdown_idle:							
		m_player_top = m_shootdown_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_idle_leg;
		Bottom_currentFrameX = 0;
		break;
	case shootdown_walk:
		m_player_top = m_shootdown_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_walk_leg;
		Bottom_currentFrameX = frameTemp % 12;
		break;
	case shootdown_jump:
		m_player_top = m_shootdown_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_jump_leg;
		Bottom_currentFrameX = frameTemp % 8;
		break;

	case shootup_idle : 
		m_player_top = m_shootup_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_idle_leg;
		Bottom_currentFrameX = 0;
		break;
	case shootup_walk : 
		m_player_top = m_shootup_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_walk_leg;
		Bottom_currentFrameX = frameTemp % 12;
		break;
	case shootup_jump : 
		m_player_top = m_shootup_top;
		Top_currentFrameX = frameTemp % 6;
		m_player_bottom = m_jump_leg;
		Bottom_currentFrameX = frameTemp % 8;
		break;
	}
	playerState = 0;	//idle_idle�� �ʱ�ȭ


	

	//�� ��µǴ� �κ�	//
	Rectangle(hdc, pos.left, pos.top, pos.right, pos.bottom);

	m_player_bottom->setFrameY(currentFrameY);
	m_player_bottom->setFrameX(Bottom_currentFrameX);
	m_player_bottom->frameRender(hdc, pos.left - 120, pos.top );

	m_player_top->setFrameY(currentFrameY);
	m_player_top->setFrameX(Top_currentFrameX);
	m_player_top->frameRender(hdc, pos.left-120, pos.top-138);
	
}

void PLAYER::Release()
{
	delete m_idle_top;
	delete m_shooting_top;		
	delete m_shootdown_top;
	delete m_shootup_top;
	

	delete m_idle_leg;
	delete m_walk_leg;
	delete m_jump_leg;

	delete gun;
}


void PLAYER::Move(bool leftKeyPressed,bool rightKeyPressed,bool upKeyPressed,bool downKeyPressed)
{
	

	if (leftKeyPressed)
	{
		
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		gunPoints.prevAngle = PI;

		////frame control
		currentFrameY = 1;
		if(!isJump)
			playerState += B_WALK;	//�ȴ� ���̴�	//������ �ƴҶ�
	}
	if (rightKeyPressed)
	{

		
		//�̰� ���� anymachinegun ���� �ٲ�� �ٽ� �����ؾ� �� �κ�
		gunPoints.prevAngle = 0;
		
		////frame control
		currentFrameY = 0;
		if (!isJump)
			playerState += B_WALK; //�ȴ� ���̴�	//������ �ƴҶ�
	}
	if (upKeyPressed)
	{
		gunPoints.isUpKeyPressed = true;
		playerState += T_SHOOTUP;
	}
	if (downKeyPressed)
	{
		gunPoints.isDownKeyPressed = true;
		playerState += T_SHOOTDOWN;
	}
	
}

void PLAYER::playerJump()
{
	if (isJump)
	{
		Jump();
		playerState += B_JUMP;
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
	pos.top += GRAVITYTEMP;
	pos.bottom += GRAVITYTEMP;
}

void PLAYER::setFloorPos(RECT _floorPos)
{
	floorPos = _floorPos;
}

