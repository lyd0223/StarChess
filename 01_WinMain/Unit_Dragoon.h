#pragma once
#include "Unit.h"
#include "Bullet.h"

class Unit_Dragoon : public Unit
{
protected:
	bool mIsShooting;

public:
	Unit_Dragoon()
	{
		mUnitStar = 1;
		mUnitType = "Dragoon";
	}
	void Init(int x, int y, string type, int star)override;
	void Update()override;
	void Death()override;
};

