/**
* メニューシステムクラスの実装.
*/
#include"stdafx.h"
#include"MenuSystem.h"

/** 
* 初期化.
*/
void MenuSystem::Start(Player * player)
{
	MenuBar_.Start();

	float size = MenuBar_.GetTransform()->Width_;

	IMenuWindow_[0].reset(new InventoryWindow());
	IMenuWindow_[0]->Start(MenuBar_.GetTransform(), size / (WINDOW_NUM + 1));
	IMenuWindow_[0]->SetPlayer(player);

	IMenuWindow_[1].reset(new OptionWindow());
	IMenuWindow_[1]->Start(MenuBar_.GetTransform(), size / (WINDOW_NUM + 1) * 2);
	IMenuWindow_[1]->SetPlayer(player);

	SelectImage_.Load("Image/Select.png");
	SelectImage_.SetTransform(&SelectRT_);

	SelectRT_.Width_ = 120;
	SelectRT_.Height_ = 40;

	SelectRT_.Parent_ = IMenuWindow_[WindowStateE::Inventory]->GetNameTransformPointer();
}

/** 
* 更新.
*/
void MenuSystem::Update()
{

	if (XInput().IsTrigger(ButtonE::Start))
	{
		isEffectiveness_ = !isEffectiveness_;
		
		if (!isEffectiveness_)
		{
			IMenuWindow_[WindowState_]->Close();
		}

		SoundSource* se = NewGO<SoundSource>();
		se->InitOnMemory("Game/Menu");
		se->Play();
	}

	if (isEffectiveness_)
	{
		if (XInput().IsTrigger(ButtonE::RB1))
		{
			//右に移動.

			if (WindowState_ != WindowStateE::WindowEnd)
			{
				WindowState_++;

				SoundSource* se = NewGO<SoundSource>();
				se->InitOnMemory("Game/Menu");
				se->Play();

				SelectRT_.Parent_ = IMenuWindow_[WindowState_]->GetNameTransformPointer();
			}
		}
		if (XInput().IsTrigger(ButtonE::LB1))
		{
			//左に移動.

			if (WindowState_ != WindowStateE::WindowBegin)
			{
				WindowState_--;

				SoundSource* se = NewGO<SoundSource>();
				se->InitOnMemory("Game/Menu");
				se->Play();

				SelectRT_.Parent_ = IMenuWindow_[WindowState_]->GetNameTransformPointer();
			}
		}

		MenuBar_.Update();
		IMenuWindow_[WindowState_]->Update();

		for (int i = 0; i < WINDOW_NUM; i++)
		{
			IMenuWindow_[i]->NameUpdate();
		}
		SelectRT_.Update();
	}
}

/**
* 描画.
*/
void MenuSystem::PostRender()
{
	if (isEffectiveness_)
	{
		IMenuWindow_[WindowState_]->Render();
		MenuBar_.Render();
		for (int i = 0; i < WINDOW_NUM; i++)
		{
			IMenuWindow_[i]->NameRender();
		}
		SelectImage_.Render();
	}
}
