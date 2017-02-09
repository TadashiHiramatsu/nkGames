#include"stdafx.h"
#include"MenuSystem.h"

//初期化
void MenuSystem::Start()
{
	MenuBar_.Start();

	float size = MenuBar_.GetTransform()->Width_;

	IMenuWindow_.reset(new Inventory);
	IMenuWindow_->Start(MenuBar_.GetTransform(), size /2);
}

//更新
void MenuSystem::Update()
{

	if (XInput().IsTrigger(ButtonE::ButtonStart))
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

//描画
void MenuSystem::PostRender()
{
	if (isEffectiveness_)
	{
		IMenuWindow_->Render();
		MenuBar_.Render();
		IMenuWindow_->NameRender();
	}
}
