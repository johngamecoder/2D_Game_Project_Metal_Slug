#pragma once


class ENEMY
{
protected:
	tagCHARACTER _E;
	//RECT Pos;		//적의 position		적 주변에 2개의 Rect를 만들어서 첫번째 rect에 만나게 되면 player에게 다가가도록, 두번째 Rect에 닫게 되면 shoot을 하도록 만들 것이다.
	RECT detectPlayerBoundary;		//player pos와 만나게 되면 player에게 다가가도록
	RECT shootingPlayerBoundary;	//player pos와 만나게 되면 player을 공격하도록
	

	RECT playerPos;	//for checking where is Player
	POINT playerCenterDirection;

	RECT bulletBoarder;

public:
	RECT tempRect;
public:
	ENEMY();
	virtual ~ENEMY();
	
	//RECT getPosition()
	//{
	//	return Pos;
	//}
	//RECT getDetectPlayerBoundary()
	//{
	//	return detectPlayerBoundary;
	//}
	//RECT getShootingPlayerBoundary()
	//{
	//	return shootingPlayerBoundary;
	//}

	virtual void Init()=0;
	virtual void Update(RECT, tagBULLET*,int)=0;	//첫번째 것은 player position, 두번째 인자는 player의 bullet의 주소값 ,세번째 인자는 bullet의 갯수
	virtual void Idle()=0;
	virtual void Attack()=0;
	virtual void Move()=0;
	virtual void Dead()=0;
	virtual void Render(HDC)=0;
	virtual void Release()=0;

	

};

