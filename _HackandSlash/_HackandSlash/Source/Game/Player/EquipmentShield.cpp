#include"stdafx.h"
#include"EquipmentShield.h"

#include"../GameCamera.h"
#include"../GameLight.h"

void EquipmentShield::Start(ModelRender& parent)
{
	ModelRender_.Load("Shield_01.X", nullptr);
	ModelRender_.SetTransform(&Transform_);
	ModelRender_.SetLight(g_GameLight->GetLight());
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	Transform_.ParentMatrix_ = parent.FindBoneWorldMatrix("Shield_joint");

	//�@���}�b�v�̐ݒ�
	Normal_.Load("Paladin_normal.png");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("Paladin_specular.png");
	ModelRender_.SetSpecMap(&Specular_);

}

void EquipmentShield::Update()
{
	Transform_.Update();
	ModelRender_.Update();
}

void EquipmentShield::Render()
{
	ModelRender_.Render();
}