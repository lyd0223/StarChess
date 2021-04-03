#pragma once

//클래스 전방선언 : 포인터만 가능
class Image;
class Unit;
class UI_WaitingRoom;
class UI_store;
class UImanager;
class MainGame
{
	Image* mBackBuffer;	//후면버퍼(건들지마라)
private:
	Image* mUI_Board;
	Image* mUI_BackGround;
	Image* mStartScene;
	UImanager* mUImanager;
	bool mIsStart;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

