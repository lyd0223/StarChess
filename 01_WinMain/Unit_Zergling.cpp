#include "pch.h"
#include "Unit_Zergling.h"
#include "Image.h"

void Unit_Zergling::Init(int x, int y, string type, int star)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Unit_Zergling");
	mDeathImage = ImageManager::GetInstance()->FindImage(L"Unit_Zergling_Death");
	mStoreImage = ImageManager::GetInstance()->FindImage(L"Zergling_Store");

	mIsPick = 0;
	mIsDeath = 0;
	mX = x;
	mY = y;
	mIsAirUnit = 0;
	mIsRangeAttack = 0;
	mState = State::Idle;
	mAngle = 3 / 2 * PI;
	//1�� 2�� 3��
	switch (star)
	{
	case 1:
		mUnitStar = 1;
		mImageSizeX = mImage->GetWidth() / 36;
		mImageSizeY = mImage->GetHeight() / 7;
		mAttackDamage = 8;
		mDeffence = 1;
		mHP = 50;
		mNowHP = 50;
		mMP = 100;
		mNowMP = 0;
		mRangeRadius = mImageSizeX / 2;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 2:
		mUnitStar = 2;
		mImageSizeX = mImage->GetWidth() / 36 + 10;
		mImageSizeY = mImage->GetHeight() / 7 + 10;
		mAttackDamage = 15;
		mDeffence = 2;
		mHP = 90;
		mNowHP = 90;
		mMP = 100;
		mNowMP = 0;
		mRangeRadius = mImageSizeX / 2;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	case 3:
		mUnitStar = 3;
		mImageSizeX = mImage->GetWidth() / 36 + 20;
		mImageSizeY = mImage->GetHeight() / 7 + 20;
		mAttackDamage = 25;
		mDeffence = 3;
		mHP = 200;
		mNowHP = 200;
		mMP = 100;
		mNowMP = 100;
		mRangeRadius = mImageSizeX / 2;
		mRange = EllipseMakeCenter(mX, mY, mRangeRadius);
		break;
	}
	mSizeX = mImageSizeX;
	mSizeY = mImageSizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 1.f;
	mFrameX = 0;
	mFrameY = 0;
	mFrameCt = 0;
}

void Unit_Zergling::Update()
{
	mFrameCt++;
	if (mNowHP > 0)
	{
		if (mFrameCt > 5)
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
				mFrameX = 4;
			else if (mAngle >= 1 * PI / 8 && mAngle < 2 * PI / 8)
				mFrameX = 3;
			else if (mAngle >= 2 * PI / 8 && mAngle < 3 * PI / 8)
				mFrameX = 2;
			else if (mAngle >= 3 * PI / 8 && mAngle < 4 * PI / 8)
				mFrameX = 1;
			else if (mAngle >= 4 * PI / 8 && mAngle < 5 * PI / 8)
				mFrameX = 0;
			else if (mAngle >= 5 * PI / 8 && mAngle < 6 * PI / 8)
				mFrameX = 15;
			else if (mAngle >= 6 * PI / 8 && mAngle < 7 * PI / 8)
				mFrameX = 14;
			else if (mAngle >= 7 * PI / 8 && mAngle < 8 * PI / 8)
				mFrameX = 13;

			else if (mAngle >= 8 * PI / 8 && mAngle < 9 * PI / 8)
				mFrameX = 12;
			else if (mAngle >= 9 * PI / 8 && mAngle < 10 * PI / 8)
				mFrameX = 11;
			else if (mAngle >= 10 * PI / 8 && mAngle < 11 * PI / 8)
				mFrameX = 10;
			else if (mAngle >= 11 * PI / 8 && mAngle < 12 * PI / 8)
				mFrameX = 9;
			else if (mAngle >= 12 * PI / 8 && mAngle < 13 * PI / 8)
				mFrameX = 8;
			else if (mAngle >= 13 * PI / 8 && mAngle < 14 * PI / 8)
				mFrameX = 7;
			else if (mAngle >= 14 * PI / 8 && mAngle < 15 * PI / 8)
				mFrameX = 6;
			else if (mAngle >= 15 * PI / 8 && mAngle < 16 * PI / 8)
				mFrameX = 5;

			if (mFrameY >= 7)
			{
				mFrameY = 0;
			}
		}
		else if (mState == State::Attack)
		{
			if (mAngle >= 0 && mAngle < PI / 8)
				mFrameX = 20;
			else if (mAngle >= 1 * PI / 8 && mAngle < 2 * PI / 8)
				mFrameX = 19;
			else if (mAngle >= 2 * PI / 8 && mAngle < 3 * PI / 8)
				mFrameX = 18;
			else if (mAngle >= 3 * PI / 8 && mAngle < 4 * PI / 8)
				mFrameX = 17;
			else if (mAngle >= 4 * PI / 8 && mAngle < 5 * PI / 8)
				mFrameX = 16;
			else if (mAngle >= 5 * PI / 8 && mAngle < 6 * PI / 8)
				mFrameX = 31;
			else if (mAngle >= 6 * PI / 8 && mAngle < 7 * PI / 8)
				mFrameX = 30;
			else if (mAngle >= 7 * PI / 8 && mAngle < 8 * PI / 8)
				mFrameX = 29;

			else if (mAngle >= 8 * PI / 8 && mAngle < 9 * PI / 8)
				mFrameX = 28;
			else if (mAngle >= 9 * PI / 8 && mAngle < 10 * PI / 8)
				mFrameX = 27;
			else if (mAngle >= 10 * PI / 8 && mAngle < 11 * PI / 8)
				mFrameX = 26;
			else if (mAngle >= 11 * PI / 8 && mAngle < 12 * PI / 8)
				mFrameX = 25;
			else if (mAngle >= 12 * PI / 8 && mAngle < 13 * PI / 8)
				mFrameX = 24;
			else if (mAngle >= 13 * PI / 8 && mAngle < 14 * PI / 8)
				mFrameX = 23;
			else if (mAngle >= 14 * PI / 8 && mAngle < 15 * PI / 8)
				mFrameX = 22;
			else if (mAngle >= 15 * PI / 8 && mAngle < 16 * PI / 8)
				mFrameX = 21;

			if (mFrameY != 0)
			{
				if (mFrameCt > 2)
				{
					mFrameCt = 0;
					mFrameY++;
				}
			}
			if (mFrameY >= 5)
			{
				mFrameY = 0;
				AttackTo(mTargetUnit);
			}
		}
	}
	//�׾�����
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