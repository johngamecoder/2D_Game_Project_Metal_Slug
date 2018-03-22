#include "stdafx.h"


GROUNDnOBSTACLE::GROUNDnOBSTACLE()
{
}


GROUNDnOBSTACLE::~GROUNDnOBSTACLE()
{
}

void GROUNDnOBSTACLE::Init()
{
	floorPos.left = 0;
	floorPos.top = 400;
	floorPos.right = 800;
	floorPos.bottom = 700;
}

RECT GROUNDnOBSTACLE::getFloorPos()
{
	return floorPos;
}
