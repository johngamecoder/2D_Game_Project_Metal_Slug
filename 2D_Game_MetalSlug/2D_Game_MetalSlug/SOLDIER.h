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


class SOLDIER : public ENEMY
{
private:
	tagBULLET Ebullet[SOLDIER_BULLET_MAX];
	tagGunPoints EgunPoints;
	int bulletTimer;
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
		Ebullet[n].pos = { 0,0,0,0 };	//��ġ�� �ʱ�ȭ ���־, ���߿� �ٸ� �͵�� �δ�ó�� error �� ���� ���� ����
	}

	virtual void Init();
	virtual void Update(RECT, tagBULLET*,int);
	virtual void Idle();
	virtual void Attack();
	virtual void Move();
	virtual void Dead();
	virtual void Render(HDC);

	void changeGunPos();
	void DetectorPositionUpdate(); 
	void S_BulletFire(int gunEndX, int gunEndY, float angle);
	void S_BulletMove();
	
};

