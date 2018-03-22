#pragma once


class ENEMY
{
protected:
	RECT Pos;		//���� position		�� �ֺ��� 2���� Rect�� ���� ù��° rect�� ������ �Ǹ� player���� �ٰ�������, �ι�° Rect�� �ݰ� �Ǹ� shoot�� �ϵ��� ���� ���̴�.
	RECT detectPlayerBoundary;		//player pos�� ������ �Ǹ� player���� �ٰ�������
	RECT shootingPlayerBoundary;	//player pos�� ������ �Ǹ� player�� �����ϵ���
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

