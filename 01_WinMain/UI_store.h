#pragma once
#include "UI.h"

struct Button
{
	RECT rc;
	int x;
	int y;
	int sizex;
	int sizey;
};
class UI_store : public UI
{
protected:
	Button mBuyButton;
	Button mRefreshButton;
	Image* mSlotImage = ImageManager::GetInstance()->FindImage(L"UI_StoreSlot");
	Image* mRefreshButtonImage = ImageManager::GetInstance()->FindImage(L"UI_RefreshButton");
	Image* mButtonImage = ImageManager::GetInstance()->FindImage(L"UI_Button");
public :
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Refresh();
};

