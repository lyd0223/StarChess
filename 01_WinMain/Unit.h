#pragma once
#include "Bullet.h"
class Image;

enum class State : int
{
	Idle,
	Move,
	Attack
};
class Unit
{
protected:
	float mX;
	float mY;
	float mSizeX;
	float mSizeY; 
	RECT mRect;
	float mSpeed;
	Image* mImage;
	Image* mStatusImage = ImageManager::GetInstance()->FindImage(L"Status");
	Image* mDeathImage ;
	Image* mHPbarImage = ImageManager::GetInstance()->FindImage(L"HPbar");
	Image* mMPbarImage = ImageManager::GetInstance()->FindImage(L"MPbar");
	Image* mBackbarImage = ImageManager::GetInstance()->FindImage(L"Backbar");
	Image* mStarImage = ImageManager::GetInstance()->FindImage(L"Star");
	Image* mStoreImage;
	

	bool mIsPick;
	int mFrameX;
	int mFrameY;
	int mFrameCt;
	float mAngle;
	State mState;
	int mAttackDamage;
	int mDeffence;
	int mHP;
	int mNowHP;
	int mMP;
	int mNowMP;
	float mRangeRadius;
	RECT mRange;
	string mUnitType;
	bool mIsAirUnit;
	bool mIsDeath;
	bool mIsRangeAttack;
	Bullet mBullet;
	int mUnitStar;
	int mImageSizeX;
	int mImageSizeY;
	Unit* mTargetUnit;

public:
	virtual void Init(int x, int y, string type, int star) {};
	void Release();
	virtual void Update() {};
	void Render(HDC hdc);

	void Move(float moveX, float moveY);
	void MoveTO(Unit *unit);
	void AttackTo(Unit* unit);
	void SetNowHP(int attackdamage) { mNowHP -= attackdamage-mDeffence; };
	void SetNowMP(int mp) { mNowMP += mp; };
	void SetIsPickTrue() { mIsPick = 1; };
	void SetIsPickFalse() { mIsPick = 0; };
	int GetIsDeath() { return mIsDeath; };
	int GetUnitStar() { return mUnitStar; };
	string GetUnitType() { return mUnitType; };
	RECT GetRect() { return mRect; };
	RECT* GetRectptr() { return &mRect; };
	float GetmX() { return mX; };
	float GetmY() { return mY; };
	void SetmX(float x) { mX = x; };
	void SetmY(float y) { mY = y; };
	void SetFrameX(int x) { mFrameX = x; };
	Image* GetStoreImage() { return mStoreImage; };
	void SetImage(Image* image) { mImage = image; };
	void Replace(int x, int y);
	virtual void Death() {};

};

