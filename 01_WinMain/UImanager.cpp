#include "pch.h"

#include "UImanager.h"
#include "UI.h"
#include "UI_Board.h"
#include "UI_store.h"
#include "UI_WaitingRoom.h"
#include "Image.h"
#include "Unit.h"

void UImanager::Init()
{
	mGold = 5;

	mIsShowStatus = 0;
	
	mStarCount.insert(pair<string, int>("Dragoon1", 0));
	mStarCount.insert(pair<string, int>("Dragoon2", 0));
	mStarCount.insert(pair<string, int>("Dragoon3", 0));
	mStarCount.insert(pair<string, int>("Zealot1", 0));
	mStarCount.insert(pair<string, int>("Zealot2", 0));
	mStarCount.insert(pair<string, int>("Zealot3", 0));
	mStarCount.insert(pair<string, int>("Marine1", 0));
	mStarCount.insert(pair<string, int>("Marine2", 0));
	mStarCount.insert(pair<string, int>("Marine3", 0));
	mStarCount.insert(pair<string, int>("Zergling1", 0));
	mStarCount.insert(pair<string, int>("Zergling2", 0));
	mStarCount.insert(pair<string, int>("Zergling3", 0));
	/*mStarCount.insert(pair<string, int>("Reaver1", 0));
	mStarCount.insert(pair<string, int>("Reaver2", 0));
	mStarCount.insert(pair<string, int>("Reaver3", 0));
	mStarCount.insert(pair<string, int>("Carrier1", 0));
	mStarCount.insert(pair<string, int>("Carrier2", 0));
	mStarCount.insert(pair<string, int>("Carrier3", 0));*/

	mBoard = new UI_Board();
	mBoard->Init();
	mStore = new UI_store();
	mStore->Init();
	mWaitingRoom = new UI_WaitingRoom();
	mWaitingRoom->Init();
	mStore->Refresh();
}

void UImanager::Release()
{
	mWaitingRoom->Release();
	mStore->Release();
	mBoard->Release();
}

void UImanager::Update()
{
	mBoard->Update();
	mWaitingRoom->Update();
	mStore->Update();
	

	
	//상점에서 구매하기
	//구매하면 상점 슬롯에서 영웅 빼주고 그 영웅을 대기실로. 만약 대기실이 꽉차잇으면 구매불가
	for (int i = 0; i < mStore->GetSlots().size(); i++)
	{
		if (PtInRect(&mStore->GetSlots()[i]->rc, _mousePosition))
		{
			if (mStore->GetSlots()[i]->unit != NULL)
			{
				mStore->GetSlots()[i]->unit->SetIsPickTrue();
				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					if (mWaitingRoom->GetUnitCount() < 6)
					{
						mWaitingRoom->InsertUnit(mStore->GetSlots()[i]->unit,false);
						mStarCount[mStore->GetSlots()[i]->unit->GetUnitType()+'1'] ++;
						mStore->DeleteUnit(i);
					}
				}
			}
		}
		else
		{
			if (mStore->GetSlots()[i]->unit != NULL)
			{
				mStore->GetSlots()[i]->unit->SetIsPickFalse();
			}
		}
	}
	//영웅대기실
	for (int i = 0; i < mWaitingRoom->GetSlots().size(); i++)
	{
		if (PtInRect(&mWaitingRoom->GetSlots()[i]->rc, _mousePosition))
		{
			if (mWaitingRoom->GetSlots()[i]->unit != NULL)
			{
				mWaitingRoom->GetSlots()[i]->unit->SetIsPickTrue();
				if (!mBoard->GetIsStart())
				{
					if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
					{
						mBoard->InsertUnit(mWaitingRoom->GetSlots()[i]->unit, false);
						mWaitingRoom->DeleteUnit(i);
					}
				}
				if (Input::GetInstance()->GetKeyUp(VK_RBUTTON))
				{
					mWaitingRoom->DeleteUnit(i);
				}
			}
		}
		else
		{
			if (mWaitingRoom->GetSlots()[i]->unit != NULL)
			{
				mWaitingRoom->GetSlots()[i]->unit->SetIsPickFalse();
			}
		}
	}

	//전장
	
	if (!mBoard->GetIsStart())
	{
		for (int i = 0; i < mBoard->GetSlots().size(); i++)
		{
			if (PtInRect(&mBoard->GetSlots()[i]->rc, _mousePosition))
			{
				if (mBoard->GetSlots()[i]->unit != NULL)
				{
					mBoard->GetSlots()[i]->unit->SetIsPickTrue();
					if (Input::GetInstance()->GetKeyUp(VK_RBUTTON))
					{
						if (mWaitingRoom->GetUnitCount() < 6)
						{
							mWaitingRoom->InsertUnit(mBoard->GetSlots()[i]->unit, false);
							mBoard->DeleteUnit(i);
						}
					}
					
					if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
					{
						num = i;
						
					}
				}
			}
			else
			{
				if (mBoard->GetSlots()[i]->unit != NULL)
				{
					mBoard->GetSlots()[i]->unit->SetIsPickFalse();
				}
			}
		}
		for (int i = 0; i < mBoard->GetSlots().size(); i++)
		{
			if (PtInRect(&mBoard->GetSlots()[i]->rc, _mousePosition))
			{
				if (mBoard->GetSlots()[i]->unit == NULL && num !=999)
				{
					if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
					{
						mBoard->InsertUnit(mBoard->GetSlots()[i], mBoard->GetSlots()[num]->unit, false);
						mBoard->DeleteUnit(num);
					}
				}
			}
		}
		//합성
		map<string, int >::iterator iter;

		for (iter = mStarCount.begin(); iter != mStarCount.end(); iter++)
		{
			string type = iter->first;
			int star = type[type.size() - 1] - 48;
			type = type.substr(0, type.size() - 1);
			if (iter->second == 3)
			{
				Unit* unittemp = NULL;
				//대기실 영웅 삭제.
				for (int i = 0; i < mWaitingRoom->GetSlots().size(); i++)
				{
					if (mWaitingRoom->GetSlots()[i]->unit != NULL)
					{
						if (mWaitingRoom->GetSlots()[i]->unit->GetUnitStar() == star
							&& mWaitingRoom->GetSlots()[i]->unit->GetUnitType() == type)
						{
							unittemp = mWaitingRoom->GetSlots()[i]->unit;
							mWaitingRoom->DeleteUnit(i);
						}
					}
				}
				//전장 영웅 삭제.
				for (int i = 0; i < mBoard->GetSlots().size(); i++)
				{
					if (mBoard->GetSlots()[i]->unit != NULL)
					{
						if (mBoard->GetSlots()[i]->unit->GetUnitStar() == star
							&& mBoard->GetSlots()[i]->unit->GetUnitType() == type)
						{
							unittemp = mBoard->GetSlots()[i]->unit;
							mBoard->DeleteUnit(i);
						}
					}
				}
				mStarCount[iter->first] = 0;
				mWaitingRoom->InsertUnit(unittemp, true);
				mIsStarUp = 1;
				mStarCount[type + to_string(star + 1)]++;

			}
		}
	}

	//성급 업그레이드될때 이펙트
	mFrameCt++;
	if (mFrameCt > 20)
	{
		mFrameCt = 0;
		mFrameX++;
		if (mFrameX >= 4)
		{
			mFrameX = 0;
			mFrameY++;

			if (mFrameY >= 4)
			{
				mFrameY = 0;
				mFrameX = 0;
				mIsStarUp = 0;
			}
		}
	}

}

void UImanager::Render(HDC hdc)
{
	mBoard->Render(hdc);
	mStore->Render(hdc);
	mWaitingRoom->Render(hdc);
	if (mIsStarUp)
	{
		mStarUpImage->FrameRender(hdc, mWaitingRoom->GetStarUpX()-30, mWaitingRoom->GetStarUpY()-30,mFrameX,mFrameY);
	}
}

//같은 유닛 3마리면 별(성급)이 올라감
void UImanager::StarUp(Unit* unit)
{
}
