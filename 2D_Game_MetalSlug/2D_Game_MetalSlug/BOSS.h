#pragma once

#define BARREL_SMALL_SPEED 3
#define BARREL_SMALL_SIZE 30
#define BARREL_SMALL_SHELL_SIZE 10
#define BARREL_SMALL_SHELL_SPEED 2
#define BARREL_SMALL_SHELL_GRAVITY 1

#define	BARREL_SMALL2_SPEED 3
#define	BARREL_SMALL2_SIZE 30
#define	BARREL_SMALL2_SHELL_SIZE 10
#define	BARREL_SMALL2_SHELL_SPEED 3
#define	BARREL_SMALL2_SHELL_GRAVITY 1


enum PHASE_STATE
{
	isPhase0,
	isPhase1,
	isPhase2
};

class BOSS
{
public:
	RECT pos = { 600,200,650,250 };
	RECT tempRect;
private:
	int HP;
	bool isDead;
	RECT playerPos;
	RECT floorPos;
	int timer = 0;

	
	RECT barrel_small[2];
	tagSHELL barrel_small_shell[2];

	RECT barrel_small2[3];
	tagSHELL barrel_small2_shell[3];
	


	Image* m_boss;

	int frame_count;
	int frameTemp;
	int currentFrameX;
	Image* m_body_engine;
	Image* m_body_front;
	Image* m_body_top;
	Image* m_body_wheel;

	Image* m_barrel_small[2];
	Image* m_barrel_small2[3];

	Image* m_effect_small_explosion[3];
	Image* m_effect_medium_explosion[2];

//stage ฐüทร variable
private:
	int phase;
public:
	BOSS();
	~BOSS();

	void Init();
	void Update(RECT,RECT);
	void Attack();
	void Move();
	void Dead();
	void Render(HDC);
	void Release();

	void fire(tagSHELL*,int,int,float,int);
	void shell_move();
};

