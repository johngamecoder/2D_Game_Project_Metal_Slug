#pragma once

#define BULLETMAX 5
#define BULLET_SIZE 5

//ÃÑ¾Ë ±¸Á¶Ã¼
struct tagBULLET
{
	bool isFired;
	RECT pos;
	float speed;
	float angle;
};


class PLAYER;
class GUN
{
protected:
	tagBULLET bullet[BULLETMAX];

public:
	GUN();
	virtual ~GUN();
	

	virtual void Init();
	void BulletFire(int,int,float);	//fire
	void BulletMove();	//update

	RECT getBulletPos(int n);
	bool checkFired(int n);
	void setFired(int, bool);
};

