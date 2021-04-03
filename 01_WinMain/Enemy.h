#pragma once
class Image;
class Enemy
{
	float mX;
	float mY;
	float mSizeX;
	float mSizeY;
	RECT mRect;
	float mSpeed;
	Image* mImage;
	float mAngle;

	int mFrameX;
	int mFrameCount;
public:
	void Init(int x, int y);
	void Release();
	void Update();
	void Render(HDC hdc);
};

