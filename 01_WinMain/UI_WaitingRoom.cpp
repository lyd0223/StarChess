#include "pch.h"
#include "UI_WaitingRoom.h"
#include "Unit.h"
#include "Image.h"
void UI_WaitingRoom::Init()
{
	
	for (int i = 0; i < 6; i++)
	{
		Slot* mSlot = new Slot();
		mSlot->x = 850;
		mSlot->y = 80+ 90 * i;
		mSlot->sizex = 90;
		mSlot->sizey = 90;
		mSlot->rc = RectMake(mSlot->x, mSlot->y, mSlot->sizex, mSlot->sizey);
		mSlot->unit = NULL;
		mSlots.push_back(mSlot);
	}
}

void UI_WaitingRoom::Update()
{
	

}

void UI_WaitingRoom::Render(HDC hdc)
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		mSlotImage->Render(hdc, mSlots[i]->rc.left - 5, mSlots[i]->rc.top);
		if (mSlots[i]->unit != NULL)
		{
			mSlots[i]->unit->Render(hdc);
			
		}
	}
}

