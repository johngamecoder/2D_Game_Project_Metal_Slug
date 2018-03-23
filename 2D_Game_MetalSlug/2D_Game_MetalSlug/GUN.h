#pragma once

#define BULLETMAX 5
#define BULLET_SIZE 5




class PLAYER;
class GUN
{
protected:
	tagBULLET bullet[BULLETMAX];
	int bulletNum;
public:
	GUN();
	virtual ~GUN();
	

	virtual void Init();
	void BulletFire(int,int,float);	//fire
	void BulletMove();	//update

	RECT getBulletPos(int n)
	{
		return bullet[n].pos;
	}
	tagBULLET* getBulletPointer()
	{
		return bullet;
	}
	int getBulletNum()
	{
		return bulletNum;
	}
	bool checkFired(int n);
	void setFired(int, bool);
};

