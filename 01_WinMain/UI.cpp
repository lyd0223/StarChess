#include "pch.h"
#include "UI.h"
#include "Unit.h"
#include "Image.h"

void UI::Release()
{
}

void UI::InsertUnit(Unit* unit,bool isstarup)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		if (mSlots[i]->unit == NULL)
		{
			mSlots[i]->unit = unit;
			if (isstarup)
			{
				mSlots[i]->unit->Init(mSlots[i]->x + 50, mSlots[i]->y + 50, unit->GetUnitType(), unit->GetUnitStar()+1);
				mStarUpX = mSlots[i]->x + 50;
				mStarUpY = mSlots[i]->y + 50;
			}
			else
				mSlots[i]->unit->Init(mSlots[i]->x + 50, mSlots[i]->y + 50,unit->GetUnitType(), unit->GetUnitStar());
			mUnitCount++;
			break;
		}
	}
}
void UI::InsertUnit(Slot *slot ,Unit* unit, bool isstarup)
{
	slot->unit = unit;
	slot->unit->Init(slot->x + 50, slot->y + 50,
		unit->GetUnitType(), unit->GetUnitStar());
}

void UI::DeleteUnit(int n)
{
	mSlots[n]->unit = NULL;
	mUnitCount--;
}


