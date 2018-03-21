#pragma once
#include "GUN.h"

#define DEFAULTGUNSPEED 5

class DEFAULTGUN : public GUN
{
public:
	DEFAULTGUN();
	~DEFAULTGUN();

	virtual void Init();

};

