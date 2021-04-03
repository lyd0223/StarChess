#pragma once

//Ŭ���� ���漱�� : �����͸� ����
class Image;
class Unit;
class UI_WaitingRoom;
class UI_store;
class UImanager;
class MainGame
{
	Image* mBackBuffer;	//�ĸ����(�ǵ�������)
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

