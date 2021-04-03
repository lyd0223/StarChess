#pragma once
#include "Unit.h"
class Unit_Marine : public Unit
{
protected:

public:
	Unit_Marine()
	{
		mUnitStar = 1;
		mUnitType = "Marine";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;
};


