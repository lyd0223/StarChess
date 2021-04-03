#pragma once
#include "UI.h"

class UI_WaitingRoom : public UI
{
protected:
	Image* mSlotImage = ImageManager::GetInstance()->FindImage(L"UI_WaitingRoomSlot");

public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
};

