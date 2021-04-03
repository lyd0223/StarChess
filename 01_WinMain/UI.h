#pragma once

class Unit;
struct Slot
{
	int x;
	int y;
	int sizex;
	int sizey;
	RECT rc;
	Unit* unit;
};

class UI
{
protected:
	int mUnitCount;
	vector<Slot*> mSlots;
	int mStarUpX = 100;
	int mStarUpY = 100;
	
public :
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render(HDC hdc) {};
	void Release();
	void InsertUnit(Unit* unit , bool isstarup);
	void InsertUnit(Slot *slot,Unit* unit, bool isstarup);
	void DeleteUnit(int n);
	int GetUnitCount() { return mUnitCount; };
	vector<Slot*> GetSlots() { return mSlots; };
	int GetStarUpX() { return mStarUpX; };
	int GetStarUpY() { return mStarUpY; };
};

