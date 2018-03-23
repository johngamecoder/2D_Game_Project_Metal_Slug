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

	virtual void Init();
	virtual void Update(RECT, tagBULLET*,int);	//ù��° ���� player position, �ι�° ���ڴ� player�� bullet�� �ּҰ� ,����° ���ڴ� bullet�� ����
	virtual void Idle();
	virtual void Attack();
	virtual void Move();
	virtual void Dead();
	virtual void Render(HDC);

	

};

