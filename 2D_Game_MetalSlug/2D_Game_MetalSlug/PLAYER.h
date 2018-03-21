#pragma once

#define JUMPPOWER 3.5f
struct tagGunPoints
{
	int startX, startY;
	int endX, endY;
	float angle;
};

class PLAYER
{
private:
	tagGunPoints gunPoints;
	float gravity;
	 //x변수
	 //상수a
public:
	int moveSpeed;
	bool isJump;
	float jumpPower;

	RECT pos;
public:
	PLAYER();
	~PLAYER();
	RECT GetPos()
	{
		return pos;
	}
	void SetPos(int _left,int _top,int _right,int _bottom)
	{
		pos.left = _left;
		pos.top = _top;
		pos.right = _right;
		pos.bottom = _bottom;
	}
	void Init();
	void Jump();
	void Gravity();
	
	void setGunPoints()
	{
		gunPoints.startX = pos.right - pos.left ;
		gunPoints.startY = pos.bottom - pos.top;
		gunPoints.endX= gunPoints.startX+20;
		gunPoints.endY= pos.bottom - pos.top;
		gunPoints.angle = 0;
	}
	tagGunPoints getGunPoints()
	{
		return gunPoints;
	}
};

