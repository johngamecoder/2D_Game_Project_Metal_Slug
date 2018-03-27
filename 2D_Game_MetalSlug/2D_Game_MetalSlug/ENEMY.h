#pragma once


class ENEMY
{
protected:
	tagCHARACTER _E;
	//RECT Pos;		//���� position		�� �ֺ��� 2���� Rect�� ���� ù��° rect�� ������ �Ǹ� player���� �ٰ�������, �ι�° Rect�� �ݰ� �Ǹ� shoot�� �ϵ��� ���� ���̴�.
	RECT detectPlayerBoundary;		//player pos�� ������ �Ǹ� player���� �ٰ�������
	RECT shootingPlayerBoundary;	//player pos�� ������ �Ǹ� player�� �����ϵ���
	

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
	virtual void Update(RECT, tagBULLET*,int)=0;	//ù��° ���� player position, �ι�° ���ڴ� player�� bullet�� �ּҰ� ,����° ���ڴ� bullet�� ����
	virtual void Idle()=0;
	virtual void Attack()=0;
	virtual void Move()=0;
	virtual void Dead()=0;
	virtual void Render(HDC)=0;
	virtual void Release()=0;

	

};

