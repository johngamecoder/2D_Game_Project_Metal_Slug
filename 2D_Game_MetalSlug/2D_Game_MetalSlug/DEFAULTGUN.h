#pragma once
#include "GUN.h"

#define DEFAULTGUNSPEED 15

class DEFAULTGUN : public GUN
{
public:
	DEFAULTGUN();
	~DEFAULTGUN();

	virtual void Init();
};

