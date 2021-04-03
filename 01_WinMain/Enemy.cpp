#include "pch.h"
#include "Enemy.h"

#include "Image.h"

void Enemy::Init(int x, int y)
{
	mImage = ImageManager::GetInstance()->FindImage(L"Enemy");

	mX = x;
	mY = y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mSpeed = 5.f;
	mAngle = 0.f;

	mFrameCount = mFrameX = 0;
}

void Enemy::Release()
{
	
}

void Enemy::Update()
{
	mX += cosf(mAngle) * mSpeed;
	mY -= sinf(mAngle) * mSpeed;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (mRect.left <= 0)mAngle = 0.f;
	else if (mRect.right >= WINSIZEX)mAngle = PI;

	mFrameCount++;
	if (mFrameCount >= 5)
	{
		mFrameCount = 0;
		mFrameX = (mFrameX + 1) % 10;
	}
}

void Enemy::Render(HDC hdc)
{
}
