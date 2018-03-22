#pragma once


class ENEMY
{
protected:
	RECT Pos;		//적의 position		적 주변에 2개의 Rect를 만들어서 첫번째 rect에 만나게 되면 player에게 다가가도록, 두번째 Rect에 닫게 되면 shoot을 하도록 만들 것이다.
	RECT detectPlayerBoundary;		//player pos와 만나게 되면 player에게 다가가도록
	RECT shootingPlayerBoundary;	//player pos와 만나게 되면 player을 공격하도록
public:
	ENEMY();
	virtual ~ENEMY();
	virtual void Init();
	virtual void Update();
	virtual void Idle();
	virtual void Attack();
	virtual void Move();
	virtual void Dead();

};

