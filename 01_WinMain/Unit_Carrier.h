#pragma once
#include "Unit.h"
class Unit_Carrier : public Unit
{
protected:

public:
	Unit_Carrier()
	{
		mUnitStar = 1;
		mUnitType = "Carrier";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;

};

