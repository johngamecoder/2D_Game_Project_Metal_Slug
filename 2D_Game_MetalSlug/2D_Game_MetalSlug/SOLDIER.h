#pragma once
#include "ENEMY.h"
#define SOLDIER_DETECTING_PLAYER_RANGE 200
#define SOLDIER_SHOOTING_PLAYER_RANGE 100

#define SOLDIER_SIZE 50
#define SOLDIER_SPEED 1

#define SOLDIER_GUN_LENGTH 30
#define SOLDIER_BULLET_MAX 3
#define SOLDIER_BULLET_SIZE 7
#define SOLDIER_BULLET_SPEED 3
#define SOLDIER_BULLET_DELAY 20

struct ENEMYSTATE
{
	bool isIdle;
	bool isMove;
	bool isShoot;
};

class SOLDIER : public ENEMY
{
private:
	tagBULLET Ebullet[SOLDIER_BULLET_MAX];
	tagGunPoints EgunPoints;
	int bulletTimer;

	ENEMYSTATE enemyState;

private:
	Image* m_enemy_rifle;
	int currentFrameY;
	int currentFrameX;
	int frame_count;
	int frameTemp;

	Image* m_rifle_idle;
	Image* m_rifle_move;
	Image* m_rifle_shoot;


public:
	SOLDIER();
	~SOLDIER();

	RECT getBulletPos(int n)
	{
		return Ebullet[n].pos;
	}
	void setFired(int n, bool b)
	{
		Ebullet[n].isFired = b;
		Ebullet[n].pos = { 0,0,0,0 };	//위치를 초기화 해주어서, 나중에 다른 것들과 부닥처서 error 가 나는 것을 방지
	}

	virtual void Init();
	virtual void Update(RECT, tagBULLET*,int);
	virtual void Idle();
	virtual void Attack();
	virtual void Move();
	virtual void Dead();
	virtual void Render(HDC);
	virtual void Release();

	void changeGunPos();
	void DetectorPositionUpdate(); 
	void S_BulletFire(int gunEndX, int gunEndY, float angle);
	void S_BulletMove();
	
};

