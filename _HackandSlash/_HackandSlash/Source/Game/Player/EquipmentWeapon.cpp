#include"stdafx.h"
#include"EquipmentWeapon.h"

#include"../GameCamera.h"
#include"../GameLight.h"

void EquipmentWeapon::Start(ModelRender& parent)
{
	ModelRender_.Load("Sword_01.X", nullptr);
	ModelRender_.SetTransform(&Transform_);
	ModelRender_.SetLight(g_GameLight->GetLight());
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	Transform_.ParentMatrix_ = parent.FindBoneWorldMatrix("Sword_joint");

	//法線マップの設定
	Normal_.Load("Paladin_normal.png");
	ModelRender_.SetNormalMap(&Normal_);

	//スペキュラマップの設定
	Specular_.Load("Paladin_specular.png");
	ModelRender_.SetSpecMap(&Specular_);

}

void EquipmentWeapon::Update()
{
	Transform_.Update();
	ModelRender_.Update();
}

void EquipmentWeapon::Render()
{
	ModelRender_.Render();
}