#pragma once

#define JUMPPOWER 3.5f
#define PLAYER_MOVE_SPEED 3

struct tagGunPoints
{
	int startX, startY;
	int endX, endY;
	float angle;
	float prevAngle;
	bool isUpKeyPressed;
	bool isDownKeyPressed;

	void operator =(const tagGunPoints& pos)
	{
		startX = pos.startX;
		startY = pos.startY;
		endX = pos.endX;
		endY = pos.endY;
		angle = pos.angle;
	}
};
class GUN;
class PLAYER
{
public:
	RECT pos;	//player À§Ä¡
	GUN* gun;	//ÃÑ instence pointer
	int moveSpeed;
	bool isJump;
	float jumpPower;

	tagGunPoints gunPoints;


public:
	PLAYER();
	~PLAYER();
	
	void Init();
	void Jump();
	void Gravity();
};

