#pragma once

class Unit;
class Bullet
{
	Unit *mUnit;
	Image* mBulletImage;
	int mFrameX;
	int mFrameY;
	bool mIsStop;
	wstring mBulletType;
	int mBulletX;
	int mBulletY;
	int mBulletSizeX;
	int mBulletSizeY;
	RECT mBulletRect;
	float mBulletSpeed;
	float mAngle;

public:
	void Init(Unit *unit);
	void Fire(Unit *target);
	void Render(HDC hdc);
	Image* GetBulletImage() { return mBulletImage; };
};

