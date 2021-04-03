#include "pch.h"
#include "UI_store.h"
#include "Unit.h"
#include "Image.h"
#include "Unit_Dragoon.h"
#include "Unit_Reaver.h"
#include "Unit_Carrier.h"
#include "Unit_Zealot.h"
#include "Unit_Zergling.h"
#include "Unit_Marine.h"
void UI_store::Init()
{
	mBuyButton.x = 100;
	mBuyButton.y = 700;
	mBuyButton.sizex = 100;
	mBuyButton.sizey = 50;
	mBuyButton.rc = RectMake(mBuyButton.x, mBuyButton.y, mBuyButton.sizex, mBuyButton.sizey);
	mRefreshButton.x = 100;
	mRefreshButton.y = 750;
	mRefreshButton.sizex = 100;
	mRefreshButton.sizey = 50;
	mRefreshButton.rc = RectMake(mRefreshButton.x, mRefreshButton.y, mRefreshButton.sizex, mRefreshButton.sizey);

	for (int i = 0; i < 5; i++)
	{
		Slot* mSlot = new Slot();
		mSlot->x = 200 + 160 * i;
		mSlot->y = 700;
		mSlot->sizex = 160;
		mSlot->sizey = 100;
		mSlot->rc = RectMake(mSlot->x, mSlot->y, mSlot->sizex, mSlot->sizey);
		mSlot->unit = NULL;
		mSlots.push_back(mSlot);
	}
}

void UI_store::Update()
{
	if (PtInRect(&mRefreshButton.rc, _mousePosition))
	{
		mRefreshButton.sizex = 110;
		mRefreshButton.sizey = 55;
		mRefreshButton.rc = RectMake(mRefreshButton.x, mRefreshButton.y, mRefreshButton.sizex, mRefreshButton.sizey);

		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
		{
			Refresh();
		}
	}
	else
	{
		mRefreshButton.sizex = 100;
		mRefreshButton.sizey = 50; 
		mRefreshButton.rc = RectMake(mRefreshButton.x, mRefreshButton.y, mRefreshButton.sizex, mRefreshButton.sizey);

	}
}

void UI_store::Render(HDC hdc)
{
	mButtonImage->Render(hdc, mBuyButton.rc.left, mBuyButton.rc.top);
	mRefreshButtonImage->Render(hdc, mRefreshButton.rc.left, mRefreshButton.rc.top);
	for (int i = 0; i < mSlots.size(); i++)
	{
		mSlotImage->Render(hdc, mSlots[i]->rc.left, mSlots[i]->rc.top);
		if (mSlots[i]->unit != NULL)
		{
			mSlots[i]->unit->GetStoreImage()->Render(hdc, mSlots[i]->rc.left +5, mSlots[i]->rc.top+5);
		}
	}
}

void UI_store::Refresh()
{
	for (int i = 0; i < mSlots.size(); i++)
	{
		mSlots[i]->unit = NULL;
	}
	for (int i = 0; i < mSlots.size(); i++)
	{
		Unit_Dragoon* mDragoon = nullptr;
		Unit_Zergling* mZergling = nullptr;
		Unit_Marine* mMarine = nullptr;
		Unit_Zealot* mZealot = nullptr;
		switch (Random::GetInstance()->RandomInt(5))
		{
		case 0:
			mZealot = new Unit_Zealot();
			InsertUnit(mZealot, false);
			break;
		case 1:
			mDragoon = new Unit_Dragoon();
			InsertUnit(mDragoon,false);
			break;
		case 2:
			mZergling = new Unit_Zergling();
			InsertUnit(mZergling,false);
			break;
		case 3:
			mMarine = new Unit_Marine();
			InsertUnit(mMarine,false);
			break;
		case 4:
			mZergling = new Unit_Zergling();
			InsertUnit(mZergling, false);
			break;
		}
	}
}
