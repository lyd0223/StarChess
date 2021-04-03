#include "pch.h"
#include "Unit_Reaver.h"
#include "Image.h"

void Unit_Reaver::Init(int x, int y, string type, int star)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Unit_Reaver");
	mIsPick = 0;
	mX = x;
	mY = y;
	mIsAirUnit = 0;
	//1¼º 2¼º 3¼º
	switch (star)
	{
	case 1:
		mUnitStar = 1;
		mImageSizeX = mImage->GetWidth() / 9;
		mImageSizeY = mImage->GetHeight() / 16;
		break;
	case 2:
		mUnitStar = 2;
		mImageSizeX = mImage->GetWidth() / 9 + 10;
		mImageSizeY = mImage->GetHeight() / 16 + 10;
		break;
	case 3:
		mUnitStar = 3;
		mImageSizeX = mImage->GetWidth() / 9 + 20;
		mImageSizeY = mImage->GetHeight() / 16 + 20;
		break;
	}
	mSizeX = mImageSizeX;
	mSizeY = mImageSizeY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 2.f;
	mFrameX = 0;
	mFrameY = 0;
	mFrameCt = 0;
}

void Unit_Reaver::Update()
{
	mFrameCt++;
	if (mFrameCt > 20)
	{
		mFrameCt = 0;
		mFrameX++;

		if (mFrameX >= 9)
		{
			mFrameX = 0;
		}
	}
}

