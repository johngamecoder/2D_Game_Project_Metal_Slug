#pragma once

#define BULLETMAX 10


//�Ѿ� ����ü
struct tagBULLET
{
	bool isFired;
	RECT pos;
	float speed;
	float angle;
};



class GUN
{
protected:
	tagBULLET bullet[BULLETMAX];
public:
	GUN();
	virtual ~GUN();
	

	virtual void Init();
	virtual void Fire();
};

