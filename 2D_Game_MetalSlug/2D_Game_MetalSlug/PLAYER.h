#pragma once

#define JUMPPOWER 3.5f
#define PLAYER_MOVE_SPEED 3
#define PLAYER_SIZE 50


class GUN;
class PLAYER
{
private:
	RECT tempRect;		//��� ����� UTILITY
	RECT bulletBoarder;	//���� �� RECT�� �Ѿ�� �ʱ�ȭ�ϰ� �ȴ�.
	RECT floorPos;
	RECT pos;			//player ��ġ
	long moveSpeed;
	float jumpPower;

	
public:
	bool isJump;
	GUN * gun;	//�� instence pointer
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

