#pragma once

#define BULLETMAX 10


//ÃÑ¾Ë ±¸Á¶Ã¼
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

