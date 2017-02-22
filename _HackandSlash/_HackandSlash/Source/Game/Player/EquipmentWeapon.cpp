#include"stdafx.h"
#include"EquipmentWeapon.h"

#include"../GameCamera.h"
#include"../GameLight.h"

void EquipmentWeapon::Start(ModelRender& parent)
{
	ModelRender_.Load("Weapon.X", nullptr);
	ModelRender_.SetTransform(&Transform_);
	ModelRender_.SetLight(g_GameLight->GetLight());
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	Transform_.ParentMatrix_ = parent.FindBoneWorldMatrix("RightWeapon");

	//�@���}�b�v�̐ݒ�
	Normal_.Load("Player_n.png");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("Player_s.png");
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