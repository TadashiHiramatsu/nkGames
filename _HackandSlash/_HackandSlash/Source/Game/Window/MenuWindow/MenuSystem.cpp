#include"stdafx.h"
#include"MenuSystem.h"

//‰Šú‰»
void MenuSystem::Start(Player * player)
{
	MenuBar_.Start();

	float size = MenuBar_.GetTransform()->Width_;

	IMenuWindow_.reset(new Inventory);
	IMenuWindow_->Start(MenuBar_.GetTransform(), size / 2);

	IMenuWindow_->SetPlayer(player);
}

//XV
void MenuSystem::Update()
{

	if (XInput().IsTrigger(ButtonE::Start))
	{
		isEffectiveness_ = !isEffectiveness_;
		
		if (!isEffectiveness_)
		{
			IMenuWindow_->Close();
		}
	}

	if (isEffectiveness_)
	{
		MenuBar_.Update();
		IMenuWindow_->Update();
		IMenuWindow_->NameUpdate();
	}
}

//•`‰æ
void MenuSystem::PostRender()
{
	if (isEffectiveness_)
	{
		IMenuWindow_->Render();
		MenuBar_.Render();
		IMenuWindow_->NameRender();
	}
}
