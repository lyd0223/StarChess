#pragma once
#include "Unit.h"
class Unit_Zergling : public Unit
{
protected:

public:
	Unit_Zergling()
	{
		mUnitStar = 1;
		mUnitType = "Zergling";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;
};


