#include "pch.h"
#include "Unit_Marine.h"
#include "Image.h"

void Unit_Marine::Init(int x, int y, string type, int star)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Unit_Marine");
	mDeathImage = ImageManager::GetInstance()->FindImage(L"Unit_Marine_Death");
	mStoreImage = ImageManager::GetInstance()->FindImage(L"Marine_Store");

	mIsPick = 0;
	mIsDeath = 0;
	mX = x;
	mY = y;
	mIsAirUnit = 0;
	mIsRangeAttack = 1;
	mState = State::Idle;
	mAngle = 3 / 2 * PI;
	//1성 2성 3성
	switch (star)
	{
	case 1:
		mUnitStar = 1;
		mImageSizeX = mImage->GetWidth() / 64;
		mImageSizeY = mImage->GetHeight() / 9;
		mAttackDamage = 10;
		mDeffence = 2;
		mHP = 60;
		mNowHP = 60;
		mMP = 100;
		mNowMP = 0;
		mRangeRadius = mImageSizeX / 2+100;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 2:
		mUnitStar = 2;
		mImageSizeX = mImage->GetWidth() / 64 + 10;
		mImageSizeY = mImage->GetHeight() / 9 + 10;
		mAttackDamage = 18;
		mDeffence = 3;
		mHP = 110;
		mNowHP = 110;
		mMP = 100;
		mNowMP = 0;
		mRangeRadius = mImageSizeX / 2+ 100;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 3:
		mUnitStar = 3;
		mImageSizeX = mImage->GetWidth() / 64 + 20;
		mImageSizeY = mImage->GetHeight() / 9 + 20;
		mAttackDamage = 30;
		mDeffence = 5;
		mHP = 250;
		mNowHP = 250;
		mMP = 100;
		mNowMP = 100;
		mRangeRadius = mImageSizeX / 2 +100;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	}
	mSizeX = mImageSizeX;
	mSizeY = mImageSizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 0.5f;
	mFrameX = 0;
	mFrameY = 0;
	mFrameCt = 0;
}

void Unit_Marine::Update()
{
	mFrameCt++;
	if (mNowHP > 0)
	{
		if (mFrameCt > 10)
		{
			mFrameCt = 0;
			mFrameY++;
		}
		if (mState == State::Idle)
		{
			mFrameY = 0;
			if (mFrameY >= 1)
			{
				mFrameY = 0;
			}
		}
		else if (mState == State::Move)
		{
			if (mAngle >= 0 && mAngle < PI / 8)
				mFrameX = 8;
			else if (mAngle >= 1 * PI / 8 && mAngle < 2 * PI / 8)
				mFrameX = 6;
			else if (mAngle >= 2 * PI / 8 && mAngle < 3 * PI / 8)
				mFrameX = 4;
			else if (mAngle >= 3 * PI / 8 && mAngle < 4 * PI / 8)
				mFrameX = 2;
			else if (mAngle >= 4 * PI / 8 && mAngle < 5 * PI / 8)
				mFrameX = 0;
			else if (mAngle >= 5 * PI / 8 && mAngle < 6 * PI / 8)
				mFrameX = 30;
			else if (mAngle >= 6 * PI / 8 && mAngle < 7 * PI / 8)
				mFrameX = 28;
			else if (mAngle >= 7 * PI / 8 && mAngle < 8 * PI / 8)
				mFrameX = 26;

			else if (mAngle >= 8 * PI / 8 && mAngle < 9 * PI / 8)
				mFrameX = 24;
			else if (mAngle >= 9 * PI / 8 && mAngle < 10 * PI / 8)
				mFrameX = 22;
			else if (mAngle >= 10 * PI / 8 && mAngle < 11 * PI / 8)
				mFrameX = 20;
			else if (mAngle >= 11 * PI / 8 && mAngle < 12 * PI / 8)
				mFrameX = 18;
			else if (mAngle >= 12 * PI / 8 && mAngle < 13 * PI / 8)
				mFrameX = 16;
			else if (mAngle >= 13 * PI / 8 && mAngle < 14 * PI / 8)
				mFrameX = 14;
			else if (mAngle >= 14 * PI / 8 && mAngle < 15 * PI / 8)
				mFrameX = 12;
			else if (mAngle >= 15 * PI / 8 && mAngle < 16 * PI / 8)
				mFrameX = 10;

			if (mFrameY >= 9)
			{
				mFrameY = 0;
			}
		}
		else if (mState == State::Attack)
		{
			if (mAngle >= 0 && mAngle < PI / 8)
				mFrameX = 40;
			else if (mAngle >= 1 * PI / 8 && mAngle < 2 * PI / 8)
				mFrameX = 38;
			else if (mAngle >= 2 * PI / 8 && mAngle < 3 * PI / 8)
				mFrameX = 36;
			else if (mAngle >= 3 * PI / 8 && mAngle < 4 * PI / 8)
				mFrameX = 34;
			else if (mAngle >= 4 * PI / 8 && mAngle < 5 * PI / 8)
				mFrameX = 32;
			else if (mAngle >= 5 * PI / 8 && mAngle < 6 * PI / 8)
				mFrameX = 62;
			else if (mAngle >= 6 * PI / 8 && mAngle < 7 * PI / 8)
				mFrameX = 60;
			else if (mAngle >= 7 * PI / 8 && mAngle < 8 * PI / 8)
				mFrameX = 58;

			else if (mAngle >= 8 * PI / 8 && mAngle < 9 * PI / 8)
				mFrameX = 56;
			else if (mAngle >= 9 * PI / 8 && mAngle < 10 * PI / 8)
				mFrameX = 54;
			else if (mAngle >= 10 * PI / 8 && mAngle < 11 * PI / 8)
				mFrameX = 52;
			else if (mAngle >= 11 * PI / 8 && mAngle < 12 * PI / 8)
				mFrameX = 50;
			else if (mAngle >= 12 * PI / 8 && mAngle < 13 * PI / 8)
				mFrameX = 48;
			else if (mAngle >= 13 * PI / 8 && mAngle < 14 * PI / 8)
				mFrameX = 46;
			else if (mAngle >= 14 * PI / 8 && mAngle < 15 * PI / 8)
				mFrameX = 44;
			else if (mAngle >= 15 * PI / 8 && mAngle < 16 * PI / 8)
				mFrameX = 42;

			if (mFrameY != 0)
			{
				if (mFrameCt > 5)
				{
					mFrameCt = 0;
					mFrameY++;
				}
			}
			if (mFrameY >= 4)
			{
				mFrameY = 0;
				AttackTo(mTargetUnit);
			}
		}
	}
	//죽었을때
	else
	{
		if (!mIsDeath)
		{
			mFrameX = 0;
			mFrameY = 0;
			mIsDeath = 1;
		}
		if (mFrameCt > 20)
		{
			mFrameCt = 0;
			mFrameX++;
		}
	}

}
