#pragma once
class GROUNDnOBSTACLE
{
private:
	RECT floorPos;
public:
	GROUNDnOBSTACLE();
	~GROUNDnOBSTACLE();

	void Init();
	RECT getFloorPos();
};

