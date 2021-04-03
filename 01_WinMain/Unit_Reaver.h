#pragma once
#include "Unit.h"
class Unit_Reaver : public Unit
{
protected:

public:
	Unit_Reaver()
	{
		mUnitStar = 1;
		mUnitType = "Reaver";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;

};

