#include "pch.h"
#include "Bullet.h"
#include "Unit.h"
#include "Image.h"

void Bullet::Init(Unit *unit)
{
	mUnit = unit;
	string str = "Unit_" + unit->GetUnitType() +"_Bullet";
	mBulletType.assign(str.begin(), str.end());
	mBulletImage = ImageManager::GetInstance()->FindImage(mBulletType);
	mFrameX = 0;
	mFrameY = 0;
	mBulletX = unit->GetmX();
	mBulletY = unit->GetmY();
	mBulletSizeX = mBulletImage->GetWidth() / mBulletImage->GetFrameX();
	mBulletSizeY = mBulletImage->GetHeight() / mBulletImage->GetFrameY();
	mBulletRect = RectMakeCenter(mBulletX, mBulletY, mBulletSizeX, mBulletSizeY);
	mBulletSpeed = 1.5f;
	mAngle = 0;
	mIsStop = 0;
}

void Bullet::Fire(Unit* target)
{
	RECT rctemp;
	RECT targetrc;
	targetrc = RectMakeCenter(target->GetmX(), target->GetmY(), 5, 5);
	if (IntersectRect(&rctemp,&targetrc, &mBulletRect))
	{
		mIsStop = 1;
	}
	mAngle = Math::GetAngle(mBulletX, mBulletY, target->GetmX(), target->GetmY());
	mBulletX += mBulletSpeed * cosf(mAngle);
	mBulletY -= mBulletSpeed * sinf(mAngle);
	mBulletRect = RectMakeCenter(mBulletX, mBulletY, mBulletSizeX, mBulletSizeY);
	
}

void Bullet::Render(HDC hdc)
{
	if(!mIsStop)
		mBulletImage->FrameRender(hdc, mBulletRect.left, mBulletRect.top, mFrameX, mFrameY);
}