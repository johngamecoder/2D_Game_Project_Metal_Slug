#pragma once

#define JUMPPOWER 3.5f
#define PLAYER_MOVE_SPEED 3
#define PLAYER_SIZE 50


class GUN;
class PLAYER
{
private:
	RECT tempRect;		//잠시 사용할 UTILITY
	RECT bulletBoarder;	//총이 이 RECT를 넘어가면 초기화하게 된다.
	RECT floorPos;
	RECT pos;			//player 위치
	long moveSpeed;
	float jumpPower;

	
public:
	bool isJump;
	GUN * gun;	//총 instence pointer
	tagGunPoints gunPoints;
public:
	PLAYER();
	~PLAYER();
	
	void Init();

	void Update(tagKEYBOARD);
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

