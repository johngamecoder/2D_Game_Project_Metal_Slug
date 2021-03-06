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

	totalHP = 100;
	isDead = false;
	body_front_point = { pos.left - 210, pos.top + 210 };
	body_front_openSpeed = 3;
	

	//拙精 匂重級 段奄鉢
	//small
	barrel_small[0] = { pos.left + 6, pos.top + 135, //left top
		pos.left + 6 + BARREL_SMALL_SIZE,pos.top + 135 + BARREL_SMALL_SIZE };	//right bottom
	barrel_small_HP[0] = 10;
	barrel_small_shell[0] = { false,{0,},BARREL_SMALL_SHELL_SPEED, (float)PI*3/4,0,false,0 };
	barrel_small[1] = { pos.left - 90, pos.top + 186,
		pos.left - 90 + BARREL_SMALL_SIZE, pos.top + 186 + BARREL_SMALL_SIZE };
	barrel_small_HP[1] = 10;
	barrel_small_shell[1] = { false,{ 0, },BARREL_SMALL_SHELL_SPEED, (float)PI * 3 / 4,0 ,false,0 };
	//medium
	barrel_medium[0] = { pos.left + 165, pos.top + 330,
		pos.left + 165 + BARREL_MEDIUM_SIZE, pos.top + 330+ BARREL_MEDIUM_SIZE };
	barrel_medium_HP[0] = 10;
	barrel_medium_shell[0] = { false,{ 0, },BARREL_MEDIUM_SHELL_SPEED, (float)PI * 5 / 8,0 ,false,0 };
	barrel_medium[1] = { pos.left + 315, pos.top + 330,
		pos.left + 315 + BARREL_MEDIUM_SIZE, pos.top + 330 + BARREL_MEDIUM_SIZE };
	barrel_medium_HP[1] = 10;
	barrel_medium_shell[1] = { false, { 0, }, BARREL_MEDIUM_SHELL_SPEED, (float)PI * 5 / 8, 0 ,false,0 };
	barrel_medium[2] = { pos.left + 225, pos.top + 375,
		pos.left + 225 + BARREL_MEDIUM_SIZE, pos.top + 375 + BARREL_MEDIUM_SIZE };
	barrel_medium_HP[2] = 10;
	barrel_medium_shell[2] = { false,{ 0, }, BARREL_MEDIUM_SHELL_SPEED, (float)PI * 5 / 8, 0,false,0 };
	//big
	barrel_big_HP = 1;//節獣 戚杏稽
	barrel_big_shell = { false,{ 0, },BARREL_BIG_SHELL_SPEED, (float)PI * 3 / 4,0,false,0 };
	barrel_big = { pos.left - 177, pos.top - 33 ,0,0 };
	m_boss = NULL;
	
	//body part
	m_body_engine = new Image;
	m_body_engine->init("Image/boss/body/engine/body_engine.bmp",1632,228,8,1,true,RGB(255,0,255));
	m_body_front = new Image;
	m_body_front->init("Image/boss/body/front/body_front.bmp",732,408,2,1,true, RGB(255, 0, 255));
	m_body_top = new Image;
	m_body_top->init("Image/boss/body/top/body_top.bmp",364*3,164 * 3,2,1, true, RGB(255, 0, 255));
	m_body_wheel = new Image;
	m_body_wheel->init("Image/boss/body/wheel/body_wheel.bmp",1536 * 3,75 * 3,8,1,true, RGB(255, 0, 255));
	
	//BARREL PART
	//small
	m_barrel_small[0] = new Image;
	m_barrel_small[0]->init("Image/boss/barrel/small/barrel_small.bmp", 1012 * 3, 36 * 3, 22, 1, true, RGB(255, 0, 255));
	m_barrel_small[1] = m_barrel_small[0];

	m_effect_medium_explosion[0] = new Image;
	m_effect_medium_explosion[0]->init("Image/effect/medium_explosion.bmp",2040 * 3,155 * 3,30,1, true, RGB(255, 0, 255));
	m_effect_medium_explosion[1] = m_effect_medium_explosion[0];

	//medium
	m_barrel_medium[0] = new Image;
	m_barrel_medium[0]->init("Image/boss/barrel/medium/barrel_medium.bmp", 756 * 3, 25 * 3, 18, 1, true, RGB(255, 0, 255));
	m_barrel_medium[1]= m_barrel_medium[0];
	m_barrel_medium[2]= m_barrel_medium[0];

	m_effect_small_explosion[0] = new Image;
	m_effect_small_explosion[0]->init("Image/effect/small_explosion.bmp", 840 * 3, 52 * 3, 14, 1, true, RGB(255, 0, 255));
	m_effect_small_explosion[1] = m_effect_small_explosion[0];
	m_effect_small_explosion[2] = m_effect_small_explosion[0];

	//big
	m_barrel_big = new Image;
	m_barrel_big->init("Image/boss/barrel/big/barrel_big_test.bmp",7632,3195, 16,5, true, RGB(255, 0, 255));
	barrel_big_framecountX = 0;
	barrel_big_framecountY=0;

	frame_count=0;
	frameTemp=0;
	currentFrameX = 0;

}

void BOSS::Update(RECT _playerPos,RECT _floorPos, tagBULLET* _bullet,int n)
{
	if (isDead)
	{
		Dead();
		return;
	}
	playerPos = _playerPos;
	floorPos = _floorPos;
	//boss hp亜 50戚 鞠檎 phase 2稽 亜惟 馬壱 0戚 鞠檎 宋惟 馬澗 依
	totalHP = barrel_small_HP[0] + barrel_small_HP[1] + barrel_medium_HP[0] + barrel_medium_HP[2] + barrel_medium_HP[2] + barrel_big_HP;
	
	//printf("%d \n", totalHP);
	//節獣 phase1昔 雌殿!
	//phase = isPhase1;

	switch (phase)
	{
	case isPhase0:
	{
		pos.left -= 1;
		pos.right -= 1;
		body_front_point.x -= 1;
		for (int i = 0; i < 2; i++)
		{
			barrel_small[i].left -= 1;
			barrel_small[i].right -= 1;
		}
		for (int i = 0; i < 3; i++)
		{
			barrel_medium[i].left -= 1;
			barrel_medium[i].right -= 1;
		}

		if (pos.left < 450)
			phase = isPhase1;
	}
		break;
	case isPhase1:
	{
		if (totalHP < 51)
			phase = isPhase2;
		//player拭惟 因維 閤紹澗走 溌昔 板 HP 縁奄

		//Player拭惟 恥拭 限紹澗走 溌昔馬澗 採歳
		for (int i = 0; i < n; i++)
		{
			if (!_bullet[i].isFired)
				continue;
			
			//戚員拭澗 唖 匂重級戚 限紹澗走 check 馬切
			for (int j = 0; j < 2; j++)
			{
				if (IntersectRect(&tempRect, &_bullet[i].pos, &barrel_small[j]))
				{
					barrel_small_HP[j] -= 1;
					_bullet[i].isFired = false;	//限精 恥硝 蒸蕉爽奄
					_bullet[i].pos = { 0, };	//限精 恥硝 段奄鉢背爽奄
				}
			}
			for (int j = 0; j < 3; j++)
			{
				if (IntersectRect(&tempRect, &_bullet[i].pos, &barrel_medium[j]))
				{
					barrel_medium_HP[j] -= 1;
					_bullet[i].isFired = false;	//限精 恥硝 蒸蕉爽奄
					_bullet[i].pos = { 0, };	//限精 恥硝 段奄鉢背爽奄
				}
			}
		}
		
		//因維
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
			fire(&barrel_medium_shell[0], barrel_medium[0].left,
				barrel_medium[0].top, barrel_medium_shell[0].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_medium_shell[0].frameCount = 0;
		}
		if (timer % 30 == 15)
		{
			fire(&barrel_medium_shell[1], barrel_medium[1].left,
				barrel_medium[1].top, barrel_medium_shell[1].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_medium_shell[1].frameCount = 0;
		}
		if (timer % 30 == 25)
		{
			fire(&barrel_medium_shell[2], barrel_medium[2].left,
				barrel_medium[2].top, barrel_medium_shell[2].angle,
				BARREL_SMALL_SHELL_SIZE);
			//barrel_medium_shell[2].frameCount = 0;
		}



		// ----------------------匂添戚 競拭 恭嬢然澗走 check----------------------
		//medium explosion
		for (int i = 0; i < 2; i++)
		{
			if (!barrel_small_shell[i].isFired)
				continue;
			barrel_small_shell[i].isFired =
				!(IntersectRect(&tempRect, &barrel_small_shell[i].pos, &floorPos));
			if (barrel_small_shell[i].isFired)
				continue;
			//競拭 陥紹陥檎,//匂添戚 恭嬢遭 是帖研 害奄壱 匂添精 段奄鉢
			barrel_small_shell[i].isExploded = !(barrel_small_shell[i].isFired);
			barrel_small_shell[i].explodedPos.x = barrel_small_shell[i].pos.left;
			barrel_small_shell[i].explodedPos.y = barrel_small_shell[i].pos.top - 390;
			barrel_small_shell[i].pos = { 0, };	//恭嬢遭陥製拭澗 匂走芝 段奄鉢
		}
		//small explosion
		for (int i = 0; i < 3; i++)
		{
			if (!barrel_medium_shell[i].isFired)
				continue;
			barrel_medium_shell[i].isFired =
				!(IntersectRect(&tempRect, &barrel_medium_shell[i].pos, &floorPos));
			if (barrel_medium_shell[i].isFired)
				continue;
			//競拭 陥紹陥檎,//匂添戚 恭嬢遭 是帖研 害奄壱 匂添精 段奄鉢
			barrel_medium_shell[i].isExploded = !(barrel_medium_shell[i].isFired);
			barrel_medium_shell[i].explodedPos.x = barrel_medium_shell[i].pos.left;
			barrel_medium_shell[i].explodedPos.y = barrel_medium_shell[i].pos.top - 120;
			barrel_medium_shell[i].pos = { 0, };	//恭嬢遭陥製拭澗 匂走芝 段奄鉢
		}
		shell_move();
		
	}
	break;
	case isPhase2:
	{
		if (body_front_openSpeed > 0)
		{
			body_front_point.x -= body_front_openSpeed;
			body_front_openSpeed -= 0.2f;
		}
	}
		break;
	case isPhase3:
	{	
		barrel_big_framecountY = 1;
		//barrel_big_framecountX = 15;
		//if (frame_count % 50==49)
		//	barrel_big_framecountX++;
		if (barrel_big_framecountX > 8)
			barrel_big_framecountX = 0;
		if (0 <= playerPos.right&&playerPos.right < 100)
			barrel_big_framecountX = 8;
		if (100 <= playerPos.right&&playerPos.right < 200)
			barrel_big_framecountX = 7;
		if (200 <= playerPos.right&&playerPos.right < 300)
			barrel_big_framecountX = 6;
		if (300 <= playerPos.right&&playerPos.right < 400)
			barrel_big_framecountX = 5;
		if (400 <= playerPos.right&&playerPos.right < 500)
			barrel_big_framecountX = 4;

		



		//int dx = barrel_big.right - playerPos.right;
		//int dy = -(barrel_big.top - playerPos.bottom);
		//double rad = atan2(dx, dy);
		//rad=rad * 180 / PI;
		//蟹掻拭 戚暗 郊蚊!(匂重蒋生稽)
		//if (!barrel_big_shell.isFired)
		//{
		//	int dx = barrel_big.left - playerPos.right;
		//	int dy = -(barrel_big.top - playerPos.bottom) ;
		//	double rad = atan2(dx, dy); 
		//	fire(&barrel_big_shell, barrel_big.left, barrel_big.top, -(rad+PI/2), BARREL_BIG_SHELL_SIZE);
		//	rad *= 100;
		//	barrel_big_framecountX = (int)rad% 9;
		//}
		//else
		//	big_shell_move();


		//// ----------------------匂添戚 競拭 恭嬢然澗走 check----------------------
		////big explosion
		//if (barrel_big_shell.isFired)
		//{
		//	barrel_big_shell.isFired = !(IntersectRect(&tempRect, &barrel_big_shell.pos, &floorPos));
		//	if(barrel_big_shell.isFired)
		//	{
		//		//barrel_big_shell.explodedPos聖 煽舌馬壱 effect研 益 採歳拭 賑督 獣徹切
		//	}
		//}
			
	}
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
		m_body_front->frameRender(hdc, body_front_point.x, body_front_point.y);	//戚 呪帖級精 走酔走 原虞!! せせせせせ 耕室 繕舛廃暗績!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 390, pos.top + 360);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 390);

		//barrel render
		currentFrameX = frameTemp % 22;
		m_barrel_small[0]->setFrameX(currentFrameX);
		m_barrel_small[0]->frameRender(hdc, barrel_small[0].left, barrel_small[0].top);
		m_barrel_small[1]->setFrameX(currentFrameX + 4);
		m_barrel_small[1]->frameRender(hdc, barrel_small[1].left, barrel_small[1].top);

		currentFrameX = frameTemp % 12;
		m_barrel_medium[0]->setFrameX(currentFrameX);
		m_barrel_medium[0]->frameRender(hdc, barrel_medium[0].left, barrel_medium[0].top);
		m_barrel_medium[1]->setFrameX(currentFrameX + 2);
		m_barrel_medium[1]->frameRender(hdc, barrel_medium[1].left, barrel_medium[1].top);
		m_barrel_medium[2]->setFrameX(currentFrameX + 4);
		m_barrel_medium[2]->frameRender(hdc, barrel_medium[2].left, barrel_medium[2].top);
	}
		break;
	case isPhase1:
	{
		//body render
		currentFrameX = frameTemp % 2;
		m_body_top->setFrameX(currentFrameX);
		m_body_top->frameRender(hdc, pos.left, pos.top);
		m_body_front->setFrameX(currentFrameX);
		m_body_front->frameRender(hdc, body_front_point.x, body_front_point.y);	//戚 呪帖級精 走酔走 原虞!! せせせせせ 耕室 繕舛廃暗績!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 390, pos.top + 360);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 390);

		//barrel render
		currentFrameX = frameTemp % 22;
		m_barrel_small[0]->setFrameX(currentFrameX);
		m_barrel_small[0]->frameRender(hdc, barrel_small[0].left, barrel_small[0].top);
		m_barrel_small[1]->setFrameX(currentFrameX + 4);
		m_barrel_small[1]->frameRender(hdc, barrel_small[1].left, barrel_small[1].top);

		currentFrameX = frameTemp % 12;
		m_barrel_medium[0]->setFrameX(currentFrameX);
		m_barrel_medium[0]->frameRender(hdc, barrel_medium[0].left, barrel_medium[0].top);
		m_barrel_medium[1]->setFrameX(currentFrameX + 2);
		m_barrel_medium[1]->frameRender(hdc, barrel_medium[1].left, barrel_medium[1].top);
		m_barrel_medium[2]->setFrameX(currentFrameX + 4);
		m_barrel_medium[2]->frameRender(hdc, barrel_medium[2].left, barrel_medium[2].top);

		//--------------------shell render----------------------
		for (int i = 0; i < 2; i++)
		{
			if (!barrel_small_shell[i].isFired)
				continue;
			Rectangle(hdc, barrel_small_shell[i].pos.left, barrel_small_shell[i].pos.top, barrel_small_shell[i].pos.right, barrel_small_shell[i].pos.bottom);
		}
		for (int i = 0; i < 3; i++)
		{
			if (!barrel_medium_shell[i].isFired)
				continue;
			Rectangle(hdc, barrel_medium_shell[i].pos.left, barrel_medium_shell[i].pos.top, barrel_medium_shell[i].pos.right, barrel_medium_shell[i].pos.bottom);
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
			if (!(barrel_medium_shell[i].isExploded))
				continue;
			if (frameTemp % 2 == 1)
				barrel_medium_shell[i].frameCount++;
			m_effect_small_explosion[i]->setFrameX(barrel_medium_shell[i].frameCount);
			m_effect_small_explosion[i]->frameRender(hdc, barrel_medium_shell[i].explodedPos.x, barrel_medium_shell[i].explodedPos.y);
			if (barrel_medium_shell[i].frameCount > 14)
			{
				barrel_medium_shell[i].isExploded = false;
				barrel_medium_shell[i].frameCount = 0;
			}
		}
		//戚暗 溌昔遂戚艦 走酔切
		//for (int i = 0; i < 2; i++)
		//{
		//	Rectangle(hdc, barrel_small[i].left, barrel_small[i].top, barrel_small[i].right, barrel_small[i].bottom);
		//}
		//for (int i = 0; i < 3; i++)
		//{
		//	Rectangle(hdc, barrel_medium[i].left, barrel_medium[i].top, barrel_medium[i].right, barrel_medium[i].bottom);
		//}
		//MoveToEx(hdc, 0, 0, NULL);	//胡煽 hdc研 身奄壱 
		//LineTo(hdc, barrel_medium[2].left, barrel_medium[2].top);	//識聖 益鍵陥.
		
	}
	break;
	case isPhase2:
	{
		//body render
		currentFrameX = frameTemp % 2;
		m_body_top->setFrameX(currentFrameX);
		m_body_top->frameRender(hdc, pos.left, pos.top);
		m_body_front->setFrameX(currentFrameX);
		m_body_front->frameRender(hdc, body_front_point.x, body_front_point.y);	//戚 呪帖級精 走酔走 原虞!! せせせせせ 耕室 繕舛廃暗績!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 390, pos.top + 360);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 390);

		//big barrel render
		if (body_front_openSpeed <= 0)
		{
			if (frameTemp % 2 == 1)
			{
				m_barrel_big->setFrameX(barrel_big_framecountX++);
			}
			m_barrel_big->frameRender(hdc, barrel_big.left - 55, barrel_big.top - 210);
		}
		if (barrel_big_framecountX > 20)
		{
			phase = isPhase3;
			barrel_big_framecountX = 0;
			m_barrel_big->setFrameY(1);
			barrel_big.right = barrel_big.left + BARREL_BIG_WIDTH;
			barrel_big.bottom = barrel_big.top + BARREL_BIG_HEIGHT; 
		}
	}
		break;
	case isPhase3:
	{
		//body render
		currentFrameX = frameTemp % 2;
		m_body_top->setFrameX(currentFrameX);
		m_body_top->frameRender(hdc, pos.left, pos.top);
		m_body_front->setFrameX(currentFrameX);
		m_body_front->frameRender(hdc, body_front_point.x, body_front_point.y);	//戚 呪帖級精 走酔走 原虞!! せせせせせ 耕室 繕舛廃暗績!

		currentFrameX = frameTemp % 8;
		m_body_engine->setFrameX(currentFrameX);
		m_body_engine->frameRender(hdc, pos.left + 390, pos.top + 360);
		m_body_wheel->setFrameX(currentFrameX);
		m_body_wheel->frameRender(hdc, pos.left, pos.top + 390);

		//big barrel render
		//Rectangle(hdc, barrel_big.left, barrel_big.top, barrel_big.right, barrel_big.bottom);
		m_barrel_big->setFrameX(barrel_big_framecountX);
		m_barrel_big->setFrameY(barrel_big_framecountY);
		m_barrel_big->frameRender(hdc, barrel_big.left-55, barrel_big.top-210);

		//shell render
		Rectangle(hdc, barrel_big_shell.pos.left, barrel_big_shell.pos.top, barrel_big_shell.pos.right, barrel_big_shell.pos.bottom);
		
	}
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
	delete m_barrel_medium[0];

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
		barrel_small_shell[i].timer += 0.05f;	//戚 展戚
		barrel_small_shell[i].pos.top +=(BARREL_SMALL_SHELL_GRAVITY * barrel_small_shell[i].timer);
		barrel_small_shell[i].pos.left += cosf(barrel_small_shell[i] .angle) * barrel_small_shell[i].speed;
		barrel_small_shell[i].pos.top += -sinf(barrel_small_shell[i] .angle) * barrel_small_shell[i].speed;
		barrel_small_shell[i].pos.right =  barrel_small_shell[i].pos.left + BARREL_SMALL_SHELL_SIZE;
		barrel_small_shell[i].pos.bottom = barrel_small_shell[i].pos.top + BARREL_SMALL_SHELL_SIZE;
	}
	for (int i = 0; i < 3; i++)
	{
		if (!barrel_medium_shell[i].isFired)
			continue;
		barrel_medium_shell[i].timer += 0.05f;
		barrel_medium_shell[i].pos.top += (BARREL_MEDIUM_SHELL_GRAVITY * barrel_medium_shell[i].timer);
		barrel_medium_shell[i].pos.left += cosf(barrel_medium_shell[i].angle) * barrel_medium_shell[i].speed;
		barrel_medium_shell[i].pos.top += -sinf(barrel_medium_shell[i].angle) * barrel_medium_shell[i].speed;
		barrel_medium_shell[i].pos.right = barrel_medium_shell[i].pos.left + BARREL_MEDIUM_SHELL_SIZE;
		barrel_medium_shell[i].pos.bottom = barrel_medium_shell[i].pos.top + BARREL_MEDIUM_SHELL_SIZE;
	}
}

void BOSS::big_shell_move()
{
	if (barrel_big_shell.isFired)
	{
		barrel_big_shell.pos.left += cosf(barrel_big_shell.angle) * barrel_big_shell.speed;
		barrel_big_shell.pos.top += -sinf(barrel_big_shell.angle) * barrel_big_shell.speed;
		barrel_big_shell.pos.right	= barrel_big_shell.pos.left + BARREL_BIG_SHELL_SIZE;
		barrel_big_shell.pos.bottom = barrel_big_shell.pos.top + BARREL_BIG_SHELL_SIZE;
	}

}

