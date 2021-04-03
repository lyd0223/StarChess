#include "pch.h"
#include "Unit.h"

#include "Image.h"
#include "Bullet.h"


void Unit::Release()
{
	SafeDelete(mImage);
}


void Unit::Render(HDC hdc)
{
	if (mNowHP > 0)
	{
		if (mIsPick)
		{
			mStatusImage->Render(hdc, mX + 50, mY + 50);
			//À¯´ÖÅ¸ÀÔ
			wstring wstringtemp;
			wstringtemp.assign(mUnitType.begin(), mUnitType.end());
			TextOut(hdc, mX + 80, mY + 80, wstringtemp.c_str(), wstringtemp.length());
			//À¯´Ö ¼º±Þ
			switch (mUnitStar)
			{
			case 1:
				TextOut(hdc, mX + 150, mY + 80, L"¡Ú", 1);
				break;
			case 2:
				TextOut(hdc, mX + 150, mY + 80, L"¡Ú¡Ú", 2);
				break;
			case 3:
				TextOut(hdc, mX + 150, mY + 80, L"¡Ú¡Ú¡Ú", 3);
				break;
			}
			
			TextOut(hdc, mX + 80, mY + 100, (L"HP : " + to_wstring(mNowHP)).c_str(), (L"HP : " + to_wstring(mHP)).length());
			TextOut(hdc, mX + 80, mY + 115, (L"MP : " + to_wstring(mNowMP)).c_str(), (L"MP : " + to_wstring(mNowMP)).length());

			TextOut(hdc, mX + 80, mY + 135, (L"DAM : " + to_wstring(mAttackDamage)).c_str(), (L"DAM : " + to_wstring(mAttackDamage)).length());
			TextOut(hdc, mX + 80, mY + 150, (L"DEF : " + to_wstring(mDeffence)).c_str(), (L"DEF : " + to_wstring(mDeffence)).length());

			if (mIsAirUnit)
			{

			}
			mImage->AlphaScaleFrameRender(hdc, mRect.left, mRect.top, mFrameX, mFrameY, mSizeX, mSizeY, 0.5f);
		}
		else
		{
			mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mFrameX, mFrameY,mSizeX,mSizeY);
			mBackbarImage->ScaleRender(hdc, mRect.left, mRect.top - 10, mSizeX, 5);
			mHPbarImage->ScaleRender(hdc, mRect.left, mRect.top - 10, int((float)mSizeX * ((float)mNowHP / (float)mHP)), 5);
			mBackbarImage->ScaleRender(hdc, mRect.left, mRect.top - 5, mSizeX, 5);
			mMPbarImage->ScaleRender(hdc, mRect.left, mRect.top - 5, mSizeX, 5);

			if (mIsAirUnit)
			{

			}
		}
		if (mIsRangeAttack)
		{
			if (mState == State::Attack)
			{
				if (mBullet.GetBulletImage() != NULL)
					mBullet.Render(hdc);
			}

		}
	}
	else
	{
		mDeathImage->FrameRender(hdc, mRect.left, mRect.top, mFrameX, mFrameY);
	}
}

void Unit::Move(float moveX, float moveY)
{
	mX += moveX;
	mY += moveY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Unit::MoveTO(Unit* unit)
{
	if (!mIsDeath)
	{
		mTargetUnit = unit;
		mAngle = Math::GetAngle(mX, mY, unit->GetmX(), unit->GetmY());
		float distance;
		distance = Math::GetDistance(mX, mY, unit->GetmX(), unit->GetmY());
		if (!IntersectRectToCircle(unit->GetRect(), mX, mY, mRangeRadius))
		{
			mX += mSpeed * cosf(mAngle);
			mY -= mSpeed * sinf(mAngle);
			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
			mState = State::Move;
		}
		else
		{
			mState = State::Attack;
		}

	}

}
void Unit::AttackTo(Unit* unit)
{
	unit->SetNowHP(mAttackDamage);
}

void Unit::Replace(int x, int y)
{
	mX = x;
	mY = y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}


