#include "stdafx.h"
#include "BOSS.h"


BOSS::BOSS()
{
}


BOSS::~BOSS()
{
}

void BOSS::Init()
{

	HP = 100;
	isDead = false;
	phase = isPhase0; //Phase 등장신으로 초기화

	//작은 포신들 초기화
	//small
	barrel_small[0] = { pos.left + 2, pos.top + 45, //left top
		pos.left + 2 + BARREL_SMALL_SIZE,pos.top + 45 + BARREL_SMALL_SIZE };	//right bottom
	barrel_small_shell[0] = { false,{0,},BARREL_SMALL_SHELL_SPEED, (float)PI*3/4,0,false,0 };
	barrel_small[1] = { pos.left - 30, pos.top + 62,
		pos.left - 30 + BARREL_SMALL_SIZE, pos.top + 62 + BARREL_SMALL_SIZE };
	barrel_small_shell[1] = { false,{ 0, },BARREL_SMALL_SHELL_SPEED, (float)PI * 3 / 4,0 ,false,0 };
	//small2
	barrel_small2[0] = { pos.left + 55, pos.top + 110,
		pos.left + 55+ BARREL_SMALL2_SIZE, pos.top + 110+ BARREL_SMALL2_SIZE };
	barrel_small2_shell[0] = { false,{ 0, },BARREL_SMALL2_SHELL_SPEED, (float)PI * 5 / 8,0 ,false,0 };
	barrel_small2[1] = { pos.left + 105, pos.top + 110,
		pos.left + 105 + BARREL_SMALL2_SIZE, pos.top + 110 + BARREL_SMALL2_SIZE };
	barrel_small2_shell[1] = { false, { 0, }, BARREL_SMALL2_SHELL_SPEED, (float)PI * 5 / 8, 0 ,false,0 };
	barrel_small2[2] = { pos.left + 85, pos.top + 125,
		pos.left + 85 + BARREL_SMALL2_SIZE, pos.top + 125 + BARREL_SMALL2_SIZE };
	barrel_small2_shell[2] = { false,{ 0, }, BARREL_SMALL2_SHELL_SPEED, (float)PI * 5 / 8, 0,false,0 };


	m_boss = NULL;
	
	//body part
	m_body_engine = new Image;
	m_body_engine->init("Image/boss/body/engine/body_engine.bmp",544,76,8,1,true,RGB(255,0,255));
	m_body_front = new Image;
	m_body_front->init("Image/boss/body/front/body_front.bmp",244,136,2,1,true, RGB(255, 0, 255));
	m_body_top = new Image;
	m_body_top->init("Image/boss/body/top/body_top.bmp",364,164,2,1, true, RGB(255, 0, 255));
	m_body_wheel = new Image;
	m_body_wheel->init("Image/boss/body/wheel/body_wheel.bmp",1536,75,8,1,true, RGB(255, 0, 255));
	
	//BARREL PART
	//small
	m_barrel_small[0] = new Image;
	m_barrel_small[0]->init("Image/boss/barrel/small/barrel_small.bmp", 1012, 36, 22, 1, true, RGB(255, 0, 255));
	m_barrel_small[1] = m_barrel_small[0];

	m_effect_medium_explosion[0] = new Image;
	m_effect_medium_explosion[0]->init("Image/effect/medium_explosion.bmp",2040,155,30,1, true, RGB(255, 0, 255));
	m_effect_medium_explosion[1] = m_effect_medium_explosion[0];

	//small2
	m_barrel_small2[0] = new Image;
	m_barrel_small2[0]->init("Image/boss/barrel/small2/barrel_small2.bmp", 756, 25, 18, 1, true, RGB(255, 0, 255));
	m_barrel_small2[1]= m_barrel_small2[0];
	m_barrel_small2[2]= m_barrel_small2[0];

	m_effect_small_explosion[0] = new Image;
	m_effect_small_explosion[0]->init("Image/effect/small_explosion.bmp", 840, 52, 14, 1, true, RGB(255, 0, 255));
	m_effect_small_explosion[1] = m_effect_small_explosion[0];
	m_effect_small_explosion[2] = m_effect_small_explosion[0];

	frame_count=0;
	frameTemp=0;
	currentFrameX = 0;

}

void BOSS::Update(RECT _playerPos,RECT _floorPos)
{
	if (isDead)
	{
		Dead();
		return;
	}
	playerPos = _playerPos;
	floorPos = _floorPos;
	
	//잠시 phase1인 상태!
	//phase = isPhase1;

	switch (phase)
	{
	case isPhase0:
		pos.left -= 1;
		pos.right -= 1;
		for (int i = 0; i < 2; i++)
		{
			barrel_small[i].left -= 1;
			barrel_small[i].right -= 1;
		}
		for (int i = 0; i < 3; i++)
		{
			barrel_small2[i].left -= 1;
			barrel_small2[i].right -= 1;
		}

		if (pos.left < 501)
			phase = isPhase1;
		break;
	case isPhase1:
	{
		if (HP < 51)
			phase = isPhase2;

		//공격
		if (timer++ % 20 == 9)
		{
			fire(&barrel_small_shell[0], barrel_small[0].left,
				barrel_small[0].top, barrel_small_shell[0].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_small_shell[0].frameCount = 0;
		}
		if (timer % 20 == 19)
		{
			fire(&barrel_small_shell[1], barrel_small[1].left,
				barrel_small[1].top, barrel_small_shell[1].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_small_shell[1].frameCount = 0;
		}

		if (timer % 30 == 5)
		{
			fire(&barrel_small2_shell[0], barrel_small2[0].left,
				barrel_small2[0].top, barrel_small2_shell[0].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_small2_shell[0].frameCount = 0;
		}
		if (timer % 30 == 15)
		{
			fire(&barrel_small2_shell[1], barrel_small2[1].left,
				barrel_small2[1].top, barrel_small2_shell[1].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_small2_shell[1].frameCount = 0;
		}
		if (timer % 30 == 25)
		{
			fire(&barrel_small2_shell[2], barrel_small2[2].left,
				barrel_small2[2].top, barrel_small2_shell[2].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_small2_shell[2].frameCount = 0;
		}



		// ----------------------포탄이 땅에 떨어졌는지 check----------------------
		//medium explosion
		for (int i = 0; i < 2; i++)
		{
			if (!barrel_small_shell[i].isFired)
				continue;
			barrel_small_shell[i].isFired =
				!(IntersectRect(&tempRect, &barrel_small_shell[i].pos, &floorPos));
			if (barrel_small_shell[i].isFired)
				continue;
			//땅에 다았다면,//포탄이 떨어진 위치를 남기고 포탄은 초기화
			barrel_small_shell[i].isExploded = !(barrel_small_shell[i].isFired);
			barrel_small_shell[i].explodedPos.x = barrel_small_shell[i].pos.left;
			barrel_small_shell[i].explodedPos.y = barrel_small_shell[i].pos.top - 130;
			barrel_small_shell[i].pos = { 0, };	//떨어진다음에는 포지션 초기화
		}
		//small explosion
		for (int i = 0; i < 3; i++)
		{
			if (!barrel_small2_shell[i].isFired)
				continue;
			barrel_small2_shell[i].isFired =
				!(IntersectRect(&tempRect, &barrel_small2_shell[i].pos, &floorPos));
			if (barrel_small2_shell[i].isFired)
				continue;
			//땅에 다았다면,//포탄이 떨어진 위치를 남기고 포탄은 초기화
			barrel_small2_shell[i].isExploded = !(barrel_small2_shell[i].isFired);
			barrel_small2_shell[i].explodedPos.x = barrel_small2_shell[i].pos.left;
			barrel_small2_shell[i].explodedPos.y = barrel_small2_shell[i].pos.top - 40;
			barrel_small2_shell[i].pos = { 0, };	//떨어진다음에는 포지션 초기화
		}
		shell_move();
		
	}
	break;
	case isPhase2:
		break;
	}
	
	




	//frame control
	frame_count++;
	if (frame_count % 3 == 0)
	{
		frameTemp++;
	}

}

void BOSS::Attack()
{
}

void BOSS::Move()
{
}

void BOSS::Dead()
{
}

void BOSS::Render(HDC hdc)
{
	switch (phase)
	{
	case isPhase0:
	{
		//body render
		currentFrameX = frameTemp % 2;
		m_body_top->setFrameX(currentFrameX);
		m_body_top->frameRender(hdc, pos.left, pos.top);
		m_body_front->setFrameX(currentFrameX);
		m_body_front->frameRender(hdc, pos.left - 70, pos.top + 70);	//이 수치들은 지우지 마라!! ㅋㅋㅋㅋㅋ 미세 조정한거임!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 130, pos.top + 120);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 130);

		//barrel render
		currentFrameX = frameTemp % 22;
		m_barrel_small[0]->setFrameX(currentFrameX);
		m_barrel_small[0]->frameRender(hdc, barrel_small[0].left, barrel_small[0].top);
		m_barrel_small[1]->setFrameX(currentFrameX + 4);
		m_barrel_small[1]->frameRender(hdc, barrel_small[1].left, barrel_small[1].top);

		currentFrameX = frameTemp % 12;
		m_barrel_small2[0]->setFrameX(currentFrameX);
		m_barrel_small2[0]->frameRender(hdc, barrel_small2[0].left, barrel_small2[0].top);
		m_barrel_small2[1]->setFrameX(currentFrameX + 2);
		m_barrel_small2[1]->frameRender(hdc, barrel_small2[1].left, barrel_small2[1].top);
		m_barrel_small2[2]->setFrameX(currentFrameX + 4);
		m_barrel_small2[2]->frameRender(hdc, barrel_small2[2].left, barrel_small2[2].top);
	}
		break;
	case isPhase1:
	{
		//body render
		currentFrameX = frameTemp % 2;
		m_body_top->setFrameX(currentFrameX);
		m_body_top->frameRender(hdc, pos.left, pos.top);
		m_body_front->setFrameX(currentFrameX);
		m_body_front->frameRender(hdc, pos.left - 70, pos.top + 70);	//이 수치들은 지우지 마라!! ㅋㅋㅋㅋㅋ 미세 조정한거임!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 130, pos.top + 120);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 130);

		//barrel render
		currentFrameX = frameTemp % 22;
		m_barrel_small[0]->setFrameX(currentFrameX);
		m_barrel_small[0]->frameRender(hdc, barrel_small[0].left, barrel_small[0].top);
		m_barrel_small[1]->setFrameX(currentFrameX + 4);
		m_barrel_small[1]->frameRender(hdc, barrel_small[1].left, barrel_small[1].top);

		currentFrameX = frameTemp % 12;
		m_barrel_small2[0]->setFrameX(currentFrameX);
		m_barrel_small2[0]->frameRender(hdc, barrel_small2[0].left, barrel_small2[0].top);
		m_barrel_small2[1]->setFrameX(currentFrameX + 2);
		m_barrel_small2[1]->frameRender(hdc, barrel_small2[1].left, barrel_small2[1].top);
		m_barrel_small2[2]->setFrameX(currentFrameX + 4);
		m_barrel_small2[2]->frameRender(hdc, barrel_small2[2].left, barrel_small2[2].top);

		//--------------------shell render----------------------
		for (int i = 0; i < 2; i++)
		{
			if (!barrel_small_shell[i].isFired)
				continue;
			Rectangle(hdc, barrel_small_shell[i].pos.left, barrel_small_shell[i].pos.top, barrel_small_shell[i].pos.right, barrel_small_shell[i].pos.bottom);
		}
		for (int i = 0; i < 3; i++)
		{
			if (!barrel_small2_shell[i].isFired)
				continue;
			Rectangle(hdc, barrel_small2_shell[i].pos.left, barrel_small2_shell[i].pos.top, barrel_small2_shell[i].pos.right, barrel_small2_shell[i].pos.bottom);
		}

		//----------------------effect render----------------------
		for (int i = 0; i < 2; i++)
		{
			if (!(barrel_small_shell[i].isExploded))
				continue;
			if (frameTemp % 2 == 1)
				barrel_small_shell[i].frameCount++;
			m_effect_medium_explosion[i]->setFrameX(barrel_small_shell[i].frameCount);
			m_effect_medium_explosion[i]->frameRender(hdc, barrel_small_shell[i].explodedPos.x, barrel_small_shell[i].explodedPos.y);
			if (barrel_small_shell[i].frameCount > 30)
			{
				barrel_small_shell[i].isExploded = false;
				barrel_small_shell[i].frameCount = 0;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (!(barrel_small2_shell[i].isExploded))
				continue;
			if (frameTemp % 2 == 1)
				barrel_small2_shell[i].frameCount++;
			m_effect_small_explosion[i]->setFrameX(barrel_small2_shell[i].frameCount);
			m_effect_small_explosion[i]->frameRender(hdc, barrel_small2_shell[i].explodedPos.x, barrel_small2_shell[i].explodedPos.y);
			if (barrel_small2_shell[i].frameCount > 14)
			{
				barrel_small2_shell[i].isExploded = false;
				barrel_small2_shell[i].frameCount = 0;
			}
		}
	}
	break;
	case isPhase2:
		break;
	}
}

void BOSS::Release()
{
	delete m_body_engine;
	delete m_body_front;
	delete m_body_top;
	delete m_body_wheel;

	delete m_barrel_small[0];
	delete m_barrel_small2[0];

	delete m_effect_small_explosion[0];
	delete m_effect_medium_explosion[0];
}

void BOSS::fire(tagSHELL* bullet, int gunEndX, int gunEndY, float angle,int bullet_size)
{
	if (!bullet->isFired)
	{
		bullet->isFired = true;
		bullet->pos.left = gunEndX;
		bullet->pos.top = gunEndY;
		bullet->pos.right = bullet->pos.left + bullet_size;
		bullet->pos.bottom = bullet->pos.top + bullet_size;
		bullet->angle = angle;
		bullet->timer = 0;
	}
}

void BOSS::shell_move()
{
	for (int i = 0; i < 2; i++)
	{
		if (!barrel_small_shell[i].isFired)
			continue;
		barrel_small_shell[i].timer += 0.05f;	//이 타이
		barrel_small_shell[i].pos.top +=(BARREL_SMALL_SHELL_GRAVITY * barrel_small_shell[i].timer);
		barrel_small_shell[i].pos.left += cosf(barrel_small_shell[i] .angle) * barrel_small_shell[i].speed;
		barrel_small_shell[i].pos.top += -sinf(barrel_small_shell[i] .angle) * barrel_small_shell[i].speed;
		barrel_small_shell[i].pos.right =  barrel_small_shell[i].pos.left + BARREL_SMALL_SHELL_SIZE;
		barrel_small_shell[i].pos.bottom = barrel_small_shell[i].pos.top + BARREL_SMALL_SHELL_SIZE;
	}
	for (int i = 0; i < 3; i++)
	{
		if (!barrel_small2_shell[i].isFired)
			continue;
		barrel_small2_shell[i].timer += 0.05f;
		barrel_small2_shell[i].pos.top += (BARREL_SMALL2_SHELL_GRAVITY * barrel_small2_shell[i].timer);
		barrel_small2_shell[i].pos.left += cosf(barrel_small2_shell[i].angle) * barrel_small2_shell[i].speed;
		barrel_small2_shell[i].pos.top += -sinf(barrel_small2_shell[i].angle) * barrel_small2_shell[i].speed;
		barrel_small2_shell[i].pos.right = barrel_small2_shell[i].pos.left + BARREL_SMALL2_SHELL_SIZE;
		barrel_small2_shell[i].pos.bottom = barrel_small2_shell[i].pos.top + BARREL_SMALL2_SHELL_SIZE;

	}
	

}

