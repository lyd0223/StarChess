#pragma once
class Unit;
class UI;
class UI_store;
class UI_Board;
class UI_WaitingRoom;

class UImanager
{
	int mGold;
	bool mIsShowStatus;
	UI_Board* mBoard;
	UI_store* mStore;
	UI_WaitingRoom* mWaitingRoom;
	map<string, int> mStarCount;
	int num = 999;

	Image* mStarUpImage = ImageManager::GetInstance()->FindImage(L"StarUpEffect");
	bool mIsStarUp = 0;
	int mFrameX = 0;
	int mFrameY = 0;
	int mFrameCt = 0;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void StarUp(Unit* unit);
	void SetGold(int gold) { mGold += gold; };
	

};

