#pragma once
#include "UI.h"

class UI_Board : public UI
{
protected:
	vector<Slot*> mEnemySlots;
	vector<Unit*> mEnemyUnits;
	vector<Unit*> mPlayerUnits;
	bool mIsStart;
	int mTimerCount;
	int mTimer;
	int mStage;
public:
	void Init()override;
	void Update()override;
	void Render(HDC hdc)override;
	bool GetIsStart() { return mIsStart; };
};

