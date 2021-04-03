#include "pch.h"
#include "UI_Board.h"
#include "Unit.h"
#include "UImanager.h"
#include "Unit_Dragoon.h"
#include "Unit_Reaver.h"
#include "Unit_Carrier.h"
#include "Unit_Zealot.h"
#include "Unit_Zergling.h"
#include "Unit_Marine.h"
void UI_Board::Init()
{
	mStage = 1;
	mIsStart = 0;
	mTimerCount = 5;
	mTimer = 60;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Slot* mSlot = new Slot();
			mSlot->sizex = 85;
			mSlot->sizey = 85;
			mSlot->x = 160 + mSlot->sizex * j;
			mSlot->y = 80 + mSlot->sizey * i;
			mSlot->rc = RectMake(mSlot->x, mSlot->y, mSlot->sizex, mSlot->sizey);
			mSlot->unit = NULL;
			mEnemySlots.push_back(mSlot);
		}
	}
	for (int i= 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Slot* mSlot = new Slot();
			mSlot->sizex = 85;
			mSlot->sizey = 85;
			mSlot->x = 160 + mSlot->sizex * j;
			mSlot->y = 322 + mSlot->sizey * i;
			mSlot->rc = RectMake(mSlot->x, mSlot->y, mSlot->sizex, mSlot->sizey);
			mSlot->unit = NULL;
			mSlots.push_back(mSlot);
		}
	}
	if (mStage == 1)
	{
		for (int i = 0; i < 4; i++)
		{
			Unit_Zealot* zealot;
			zealot = new Unit_Zealot();
			mEnemySlots[i]->unit = zealot;
			mEnemySlots[i]->unit->Init(mEnemySlots[i]->x + 50, mEnemySlots[i]->y + 50, zealot->GetUnitType(), zealot->GetUnitStar());
			zealot->SetFrameX(8);
			zealot->SetImage(ImageManager::GetInstance()->FindImage(L"Unit_ZealotEnemy"));

		}
	}
}

void UI_Board::Update()
{

	if (mIsStart == 1)
	{
		mTimerCount--;
		if (mTimerCount < 0)
		{
			mTimerCount = 5;
			mTimer--;
		}
		if (mTimer <= 0)
		{
			mIsStart = 0;
			mTimer = 100;
		}

		//½Î¿ò
		for (int i = 0; i < mPlayerUnits.size(); i++)
		{
			float minDistance = 10000;
			Unit* nearestUnit = nullptr;
			
			for (int j = 0; j < mEnemyUnits.size(); j++)
			{
				if (!mEnemyUnits[j]->GetIsDeath())
				{
					float distance = Math::GetDistance(mPlayerUnits[i]->GetmX(), mPlayerUnits[i]->GetmY()
						, mEnemyUnits[j]->GetmX(), mEnemyUnits[j]->GetmY());
					if (distance < minDistance)
					{
						minDistance = distance;
						nearestUnit = mEnemyUnits[j];
					}
				}
			}
			if (nearestUnit != nullptr)
			{
				mPlayerUnits[i]->MoveTO(nearestUnit);
				mPlayerUnits[i]->Update();
			}
			//player½Â¸®
			else
			{

				mStage++; 
				if (mStage == 2)
				{
					for (int i = 0; i < 8; i++)
					{
						Unit_Zealot* zealot;
						zealot = new Unit_Zealot();
						mEnemySlots[i]->unit = zealot;
						mEnemySlots[i]->unit->Init(mEnemySlots[i]->x + 50, mEnemySlots[i]->y + 50, zealot->GetUnitType(), zealot->GetUnitStar());
						zealot->SetFrameX(8);
						zealot->SetImage(ImageManager::GetInstance()->FindImage(L"Unit_ZealotEnemy"));
					}
				}
				else if (mStage == 3)
				{
					for (int i = 0; i < 12; i++)
					{
						Unit_Zealot* zealot;
						zealot = new Unit_Zealot();
						mEnemySlots[i]->unit = zealot;
						mEnemySlots[i]->unit->Init(mEnemySlots[i]->x + 50, mEnemySlots[i]->y + 50, zealot->GetUnitType(), zealot->GetUnitStar());
						zealot->SetFrameX(8);
						zealot->SetImage(ImageManager::GetInstance()->FindImage(L"Unit_ZealotEnemy"));
					}
				}
				mIsStart = 0;
				mTimer = 100;
				break;
				
			}

		}
		
		for (int i = 0; i < mEnemyUnits.size(); i++)
		{

			float minDistance = 10000;
			Unit* nearestUnit = nullptr;
			for (int j = 0; j < mPlayerUnits.size(); j++)
			{
				if (!mPlayerUnits[j]->GetIsDeath())
				{
					float distance = Math::GetDistance(mEnemyUnits[i]->GetmX(), mEnemyUnits[i]->GetmY()
						, mPlayerUnits[j]->GetmX(), mPlayerUnits[j]->GetmY());
					if (distance < minDistance)
					{
						minDistance = distance;
						nearestUnit = mPlayerUnits[j];
					}
				}

			}
			if (nearestUnit != nullptr)
			{
				mEnemyUnits[i]->MoveTO(nearestUnit);
				mEnemyUnits[i]->Update();
			}
			//enemy½Â¸®
			else
			{
				mIsStart = 0;
				mTimer = 100;
			}
		}
		
	}
	else  //misStart == 0
	{
		mPlayerUnits.clear();
		mEnemyUnits.clear();
		for (int i = 0; i < mSlots.size(); i++)
		{
			if (mSlots[i]->unit != NULL)
			{
				mSlots[i]->unit->Update();
			}
		}
		for (int i = 0; i < mEnemySlots.size(); i++)
		{
			if (mEnemySlots[i]->unit != NULL)
			{
				mEnemySlots[i]->unit->Update();
			}
		}
		
		mTimerCount--;
		if (mTimerCount <0 )
		{
			mTimerCount = 5;
			mTimer--;
		}
		if (mTimer <= 0)
		{
			mIsStart = 1;
			mTimer = 200;
			//mSlots , mEnemySlots¿¡ÀÖ´Â À¯´ÖµéÀ» 
			//mPlayerUnits, mEnemyUnits¿¡ º¹»ç.
			for (int i = 0; i < mSlots.size(); i++)
			{
				if (mSlots[i]->unit != NULL)
				{
					Unit* unit;
					if(mSlots[i]->unit->GetUnitType() == "Zealot")
						unit = new Unit_Zealot(*(Unit_Zealot*)mSlots[i]->unit);
					else if (mSlots[i]->unit->GetUnitType() == "Dragoon")
						unit = new Unit_Dragoon(*(Unit_Dragoon*)mSlots[i]->unit);
					else if (mSlots[i]->unit->GetUnitType() == "Zergling")
						unit = new Unit_Zergling(*(Unit_Zergling*)mSlots[i]->unit);
					else if (mSlots[i]->unit->GetUnitType() =="Marine")
						unit = new Unit_Marine(*(Unit_Marine*)mSlots[i]->unit);
					mPlayerUnits.push_back(unit);

					//mPlayerUnit , mEnemyUnit 
					//mPlayerSlots , mEnmySlots
				}
			}
			for (int i = 0; i < mEnemySlots.size(); i++)
			{
				if (mEnemySlots[i]->unit != NULL)
				{
					Unit* unit;
					if (mEnemySlots[i]->unit->GetUnitType() == "Zealot")
						unit = new Unit_Zealot(*(Unit_Zealot*)mEnemySlots[i]->unit);
					else if (mEnemySlots[i]->unit->GetUnitType() == "Dragoon")
						unit = new Unit_Dragoon(*(Unit_Dragoon*)mEnemySlots[i]->unit);
					else if (mSlots[i]->unit->GetUnitType() == "Zergling")
						unit = new Unit_Zergling(*(Unit_Zergling*)mSlots[i]->unit);
					mEnemyUnits.push_back(unit);
				}
			}
		}
	}
	
}

void UI_Board::Render(HDC hdc)
{
	TextOut(hdc, 100, 80, (L"Stage" + to_wstring(mStage)).c_str(), (L"Stage" + to_wstring(mStage)).length());
	TextOut(hdc, 100, 100, to_wstring(mTimer/10).c_str(), to_wstring(mTimer/10).length());

	if (mIsStart)
	{
		for (int i = 0; i < mPlayerUnits.size(); i++)
		{
			if (mPlayerUnits[i] != NULL)
			{
				mPlayerUnits[i]->Render(hdc);
			}
		}
		for (int i = 0; i < mEnemyUnits.size(); i++)
		{
			if (mEnemyUnits[i] != NULL)
			{
				mEnemyUnits[i]->Render(hdc);
			}
		}
	}
	else
	{
		for (int i = 0; i < mSlots.size(); i++)
		{
			if (mSlots[i]->unit != NULL)
			{
				mSlots[i]->unit->Render(hdc);
			}
		}
		for (int i = 0; i < mEnemySlots.size(); i++)
		{
			if (mEnemySlots[i]->unit != NULL)
			{
				mEnemySlots[i]->unit->Render(hdc);
			}
		}

	}
}

