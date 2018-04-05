#pragma once
#include <math.h> 

#define BARREL_SMALL_SPEED 3
#define BARREL_SMALL_SIZE 30
#define BARREL_SMALL_SHELL_SIZE 10
#define BARREL_SMALL_SHELL_SPEED 2
#define BARREL_SMALL_SHELL_GRAVITY 1

#define	BARREL_MEDIUM_SPEED 3
#define	BARREL_MEDIUM_SIZE 30
#define	BARREL_MEDIUM_SHELL_SIZE 10
#define	BARREL_MEDIUM_SHELL_SPEED 3
#define	BARREL_MEDIUM_SHELL_GRAVITY 1

#define BARREL_BIG_WIDTH 300
#define BARREL_BIG_HEIGHT 400
#define	BARREL_BIG_SHELL_SIZE 30
#define	BARREL_BIG_SHELL_SPEED 3


enum PHASE_STATE
{
	isPhase0,
	isPhase1,
	isPhase2,
	isPhase3
};

class BOSS
{
public:
	RECT pos = { 500,50,550,100 };
	RECT tempRect;
private:
	int totalHP;
	bool isDead;
	POINT body_front_point;	//boss의 앞 부분, 열리면서 big 포신이 나오도록
	float body_front_openSpeed;	//문이 열리는 속도 

	RECT playerPos;
	RECT floorPos;
	int timer = 0;

	//중형대포
	RECT barrel_small[2];
	int barrel_small_HP[2];
	tagSHELL barrel_small_shell[2];
	
	//소형대포
	RECT barrel_medium[3];
	int barrel_medium_HP[3];
	tagSHELL barrel_medium_shell[3];

	//큰대포
	RECT barrel_big;
	int barrel_big_HP;
	tagSHELL barrel_big_shell;
	int barrel_big_framecountX;
	int barrel_big_framecountY;


	Image* m_boss;

	int frame_count;
	int frameTemp;
	int currentFrameX;
	Image* m_body_engine;
	Image* m_body_front;
	Image* m_body_top;
	Image* m_body_wheel;

	Image* m_barrel_small[2];
	Image* m_barrel_medium[3];
	Image* m_barrel_big;

	Image* m_effect_small_explosion[3];
	Image* m_effect_medium_explosion[2];

//stage 관련 variable
private:
	int phase;
public:
	BOSS();
	~BOSS();

	void Init();
	void Update(RECT,RECT, tagBULLET*, int);
	void Attack();
	void Move();
	void Dead();
	void Render(HDC);
	void Release();

	void fire(tagSHELL*,int,int,float,int);
	void shell_move();
	void big_shell_move();

};

