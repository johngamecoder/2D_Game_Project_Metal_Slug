#pragma once

#define JUMPPOWER 3.5f
#define PLAYER_SIZE 20


class GUN;



/*
	top은 10의 자리 :	Bottom은 1의 차리
	idle 0				idle 0
	shooting 1			walk 1
						jump 2
*/
#define T_IDLE 0
#define T_SHOOTING 10
#define T_SHOOTDOWN 20
#define T_SHOOTUP 30

#define B_IDLE 0
#define B_WALK 1
#define B_JUMP 2

enum PLAYERSTATE 
{
	idle_idle = 00,			//   T_IDLE + B_IDLE
	idle_walk = 01,			//   T_IDLE + B_WALK
	idle_jump = 02,			//   T_IDLE + B_JUMP
	
	shooting_idle = 10,		//	T_SHOOTING + B_IDLE
	shooting_walk = 11,		//	T_SHOOTING + B_WALK
	shooting_jump = 12,		//	T_SHOOTING + B_JUMP

	shootdown_idle = 20,	//	T_SHOOTDOWN+B_IDLE
	shootdown_walk = 21,	//	T_SHOOTDOWN+B_WALK
	shootdown_jump = 22,	//	T_SHOOTDOWN+B_JUMP

	shootup_idle = 30,		//	T_SHOOTUP+B_IDLE
	shootup_walk = 31,		//	T_SHOOTUP+B_WALK
	shootup_jump = 32,		//	T_SHOOTUP+B_JUMP
};

class PLAYER
{
public:
	RECT pos;			//player 위치
private:
	RECT tempRect;		//잠시 사용할 UTILITY
	RECT bulletBoarder;	//총이 이 RECT를 넘어가면 초기화하게 된다.
	RECT floorPos;
	
	float jumpPower;

private:
	Image* m_player_top;
	Image* m_player_bottom;
	int currentFrameY;
	int Top_currentFrameX=0;
	int Bottom_currentFrameX=0;
	int frameTemp = 0;

	int playerState;
	int frame_count = 0;

	Image* m_idle_top;
	Image* m_shooting_top;
	Image* m_shootdown_top;
	Image* m_shootup_top;

	Image* m_idle_leg;
	Image* m_walk_leg;
	Image* m_jump_leg;
	
	//void frameControl(int n, int t);
public:
	bool isJump;
	bool isfired;

	GUN * gun;	//총 instence pointer
	tagGunPoints gunPoints;
public:
	PLAYER();
	~PLAYER();
	
	void Init();
	void Update(tagKEYBOARD);
	void Render(HDC);
	void Release();



	void Move(bool,bool,bool,bool);
	void playerJump();

	RECT getPlayerPos();
	tagBULLET* getPlayerBulletPointer();
	int getPlayerBulletNum();

	void changeGunPos();
	void Jump();
	void Gravity();
	void setFloorPos(RECT _floorPos);
};

