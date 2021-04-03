#pragma once
#include "Unit.h"
class Unit_Zealot : public Unit
{
protected:

public:
	Unit_Zealot()
	{
		mUnitStar = 1;
		mUnitType = "Zealot";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;
};


