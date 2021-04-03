#include "pch.h"
#include "Unit_Carrier.h"
#include "Image.h"

void Unit_Carrier::Init(int x, int y, string type, int star)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Unit_Carrier");
	mIsPick = 0;
	mX = x;
	mY = y;
	mIsAirUnit = 1;
	switch (star)
	{
	case 1:
		mUnitStar = 1;
		mImageSizeX = mImage->GetWidth() / 1;
		mImageSizeY = mImage->GetHeight() / 16;
		mSizeX = mImageSizeX;
		mSizeY = mImageSizeY;
		break;
	case 2:
		mUnitStar = 2;
		mImageSizeX = mImage->GetWidth() / 1+10;
		mImageSizeY = mImage->GetHeight() / 16+10;
		mSizeX = mImageSizeX;
		mSizeY = mImageSizeY;
		break;
	case 3:
		mUnitStar = 3;
		mImageSizeX = mImage->GetWidth() / 1+20;
		mImageSizeY = mImage->GetHeight() / 16+20;
		mSizeX = mImageSizeX;
		mSizeY = mImageSizeY;
		break;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 10.f;
	mFrameX = 0;
	mFrameY = 0;
	mFrameCt = 0;
}

void Unit_Carrier::Update()
{
	mFrameCt++;
	if (mFrameCt > 20)
	{
		mFrameCt = 0;

		
	}
}

