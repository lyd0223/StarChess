#include "pch.h"
#include "MainGame.h"
#include "Image.h"

#include "UImanager.h"

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);
	
	//모든 이미지 싱글톤 이미지매니저에 불러옴.
	ImageManager::GetInstance()->
		LoadFromFile(L"StartScene", Resources(L"startscene.bmp"), WINSIZEX, WINSIZEY, true);
	ImageManager::GetInstance()->
		LoadFromFile(L"UI_board", Resources(L"Chessboard.bmp"), 750, 750, true);
	ImageManager::GetInstance()->
		LoadFromFile(L"BackGround",Resources(L"BackGround.bmp"), WINSIZEX, WINSIZEY, true);
	ImageManager::GetInstance()->
		LoadFromFile(L"Star", Resources(L"star.bmp"), 10, 10, true);
	ImageManager::GetInstance()->
		LoadFromFile(L"StarUpEffect", Resources(L"starupeffect.bmp"), 256, 256, 4 ,4, true);

	//대기실,상점 ui
	ImageManager::GetInstance()
		->LoadFromFile(L"UI_WaitingRoomSlot", Resources(L"WaitingroomSlot.bmp"), 100, 90, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"UI_StoreSlot", Resources(L"StoreSlot.bmp"), 160, 100, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"UI_RefreshButton", Resources(L"Refreshbutton.bmp"), 100, 50, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"UI_Button", Resources(L"Button.bmp"), 100, 50, true);
	
	//체력,마력바
	ImageManager::GetInstance()
		->LoadFromFile(L"HPbar", Resources(L"ui/hfront.bmp"), 53, 5, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"MPbar", Resources(L"ui/efront.bmp"), 53, 5, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Backbar", Resources(L"ui/barback.bmp"), 53, 5, true);
	//드라군관련이미지
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Dragoon", Resources(L"unit/dragoon/dragoon.bmp"), 600, 722, 7, 9, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Dragoon_Death", Resources(L"unit/dragoon/killDragoon.bmp"), 588, 80, 7, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Dragoon_Bullet", Resources(L"unit/dragoon/dra.bmp"), 130, 21, 5, 1, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Dragoon_Store", Resources(L"unit/dragoon/dragoonimg.bmp"), 150, 80, true);

	//질럿관련이미지
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Zealot", Resources(L"unit/zealot/Zealot2.bmp"), 1344, 352, 32, 8, true, RGB(74,221,1));
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_ZealotEnemy", Resources(L"unit/zealot/Zealot1.bmp"), 1344, 352, 32, 8, true, RGB(73, 223, 2));
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Zealot_Death", Resources(L"unit/zealot/zealotDeath.bmp"), 200, 36, 7, 1, true, RGB(74, 221, 1));
	ImageManager::GetInstance()
		->LoadFromFile(L"Zealot_Store", Resources(L"unit/zealot/zealotimg.bmp"), 150, 80, true);
	
	//저글링관련이미지
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Zergling", Resources(L"unit/zergling/zergling2.bmp"), 1376, 294, 32, 7, true, RGB(85, 170, 170));
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_ZerglingEnemy", Resources(L"unit/zergling/zergling1.bmp"), 1376, 294, 32, 7, true, RGB(85, 170, 170));
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Zergling_Death", Resources(L"unit/zergling/zerglingDeath.bmp"), 240, 29, 7, 1, true, RGB(85, 170, 170));
	ImageManager::GetInstance()
		->LoadFromFile(L"Zergling_Store", Resources(L"unit/zergling/zerglingimg.bmp"), 150, 80, true);

	//마린관련이미지
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Marine", Resources(L"unit/marine/marine2.bmp"), 2432, 333, 64, 9, true, RGB(255, 0, 255));
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Marine_Death", Resources(L"unit/marine/marineDeath.bmp"), 456, 38, 8, 1, true, RGB(255, 0, 255));
	ImageManager::GetInstance()
		->LoadFromFile(L"Marine_Store", Resources(L"unit/marine/marineimg.bmp"), 150, 80, true);

	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Reaver", Resources(L"unit/reaver/reaver.bmp"), 756, 1344, 9, 16, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Unit_Carrier", Resources(L"unit/carrier/carrier.bmp"), 100, 1600, 1, 16, true);
	ImageManager::GetInstance()
		->LoadFromFile(L"Status", Resources(L"StandartBar_01.bmp"), 200, 200, true );

	mUI_Board = ImageManager::GetInstance()->FindImage(L"UI_board");
	mUI_BackGround = ImageManager::GetInstance()->FindImage(L"BackGround");

	mUImanager = new UImanager();
	mUImanager->Init();
	
	mStartScene = ImageManager::GetInstance()->FindImage(L"StartScene");
	mIsStart = 0;

	
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	KillTimer(_hWnd, 1);//타이머 꺼주자

	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);
	mUImanager->Release();
	SafeDelete(mUImanager);

}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	if (!mIsStart)
	{
		if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
		{
			mIsStart = 1;
		}
	}
	else
		mUImanager->Update();
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		if (!mIsStart)
		{
			mStartScene->Render(backDC, 0, 0);
		}
		else
		{
			mUI_BackGround->Render(backDC, 0, 0);
			mUI_Board->Render(backDC, 130, -50);

			mUImanager->Render(backDC);
		}
			

	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}

