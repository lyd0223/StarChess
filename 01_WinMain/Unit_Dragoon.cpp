#include "pch.h"
#include "Image.h"
#include "Unit_Dragoon.h"

void Unit_Dragoon::Init(int x, int y, string type, int star)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Unit_Dragoon");
	mDeathImage = ImageManager::GetInstance()->FindImage(L"Unit_Dragoon_Death");
	mStoreImage = ImageManager::GetInstance()->FindImage(L"Dragoon_Store");
	mIsPick = 0;
	mIsDeath = 0;

	mX = x;
	mY = y;
	mIsAirUnit = 0;

	mIsRangeAttack = 1;

	mState = State::Idle;
	mAngle = 3 / 2 * PI;
	
	switch (star)
	{
	case 1:
		mUnitStar = 1;
		mImageSizeX = mImage->GetWidth() / 7;
		mImageSizeY = mImage->GetHeight() / 9;
		mAttackDamage = 30;
		mDeffence = 1;
		mHP = 100;
		mNowHP = 100;
		mMP = 100;
		mNowMP = 100;
		mRangeRadius = mImageSizeX / 2 + 100;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 2:
		mUnitStar = 2;
		mImageSizeX = mImage->GetWidth() / 7 + 10;
		mImageSizeY = mImage->GetHeight() / 9 + 10;
		mAttackDamage = 55;
		mDeffence = 2;
		mHP = 200;
		mNowHP = 200;
		mMP = 100;
		mNowMP = 100;
		mRangeRadius = mImageSizeX / 2 + 100;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 3:
		mUnitStar = 3;
		mImageSizeX = mImage->GetWidth() / 7 + 20;
		mImageSizeY = mImage->GetHeight() / 9 + 20;
		mAttackDamage = 100;
		mDeffence = 3;
		mHP = 400;
		mNowHP = 400;
		mMP = 100;
		mNowMP = 100;
		mRangeRadius = mImageSizeX / 2 + 100;
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

void Unit_Dragoon::Update()
{
	mFrameCt++;
	if (mNowHP > 0)
	{

		if (mFrameCt > 20)
		{
			mFrameCt = 0;
			mFrameX++;
		}
		if (mState == State::Idle)
		{
			if (mFrameX >= 7)
			{
				mFrameX = 0;
			}

		}
		else if (mState == State::Move)
		{
			if (mAngle > 3 * PI / 8 && mAngle <= 5 * PI / 8)
				mFrameY = 1;
			else if (mAngle > 5 * PI / 8 && mAngle <= 7 * PI / 8)
				mFrameY = 2;
			else if (mAngle > 7 * PI / 8 && mAngle <= 9 * PI / 8)
				mFrameY = 3;
			else if (mAngle > 9 * PI / 8 && mAngle <= 11 * PI / 8)
				mFrameY = 4;
			else if (mAngle > 11 * PI / 8 && mAngle <= 13 * PI / 8)
				mFrameY = 5;
			else if (mAngle > 13 * PI / 8 && mAngle <= 15 * PI / 8)
				mFrameY = 6;
			else if (mAngle > 15 * PI / 8 && mAngle <= 16 * PI / 8
				|| mAngle > 0 * PI / 8 && mAngle <= 1 * PI / 8)
				mFrameY = 7;
			else if (mAngle > 1 * PI / 8 && mAngle <= 3 * PI / 8)
				mFrameY = 8;

			if (mFrameX >= 7)
			{
				mFrameX = 0;
			}
		}
		else if (mState == State::Attack)
		{
			mFrameY = 0;
			if (mFrameX == 0)
			{
				mBullet.Init(this);
			}
			mBullet.Fire(mTargetUnit);
			if (mFrameX >= 7)
			{
				mFrameX = 0;
				AttackTo(mTargetUnit);
			}
		}
	}
	else
	{
		if (!mIsDeath)
		{
			mIsDeath = 1;
			mFrameX = 0;
			mFrameY = 0;
		}
		if (mFrameCt > 50)
		{
			mFrameCt = 0;
			mFrameX++;
		}
	}
}

void Unit_Dragoon::Death()
{
}

