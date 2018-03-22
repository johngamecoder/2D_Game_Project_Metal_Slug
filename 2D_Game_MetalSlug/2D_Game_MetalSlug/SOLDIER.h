#pragma once
#include "ENEMY.h"

class SOLDIER : public ENEMY
{

public:
	SOLDIER();
	~SOLDIER();

	virtual void Init();
	virtual void Update();
	virtual void Idle();
	virtual void Attack();
	virtual void Move();
	virtual void Dead();
};

