#include"stdafx.h"
#include"Weapon.h"

#include"../GameCamera.h"

void Weapon::Start(ModelRender& parent)
{
	ModelRender_.Load("Weapon.X", nullptr);
	ModelRender_.SetTransform(&Transform_);
	ModelRender_.SetLight(&Light_);
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	Transform_.ParentMatrix_ = parent.FindBoneWorldMatrix("RightWeapon");

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

	//法線マップの設定
	Normal_.Load("Player_n.png");
	ModelRender_.SetNormalMap(&Normal_);

	//スペキュラマップの設定
	Specular_.Load("Player_s.png");
	ModelRender_.SetSpecMap(&Specular_);

}

void Weapon::Update()
{
	Transform_.Update();
	ModelRender_.Update();
}

void Weapon::Render()
{
	ModelRender_.Render();
}