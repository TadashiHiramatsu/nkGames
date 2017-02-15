#include"stdafx.h"
#include"EquipmentShield.h"

#include"../GameCamera.h"

void EquipmentShield::Start(ModelRender& parent)
{
	ModelRender_.Load("Shield.X", nullptr);
	ModelRender_.SetTransform(&Transform_);
	ModelRender_.SetLight(&Light_);
	ModelRender_.SetCamera(g_MainCamera->GetCamera());
	Transform_.ParentMatrix_ = parent.FindBoneWorldMatrix("LeftShield");

	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));

	//�@���}�b�v�̐ݒ�
	Normal_.Load("Player_n.png");
	ModelRender_.SetNormalMap(&Normal_);

	//�X�y�L�����}�b�v�̐ݒ�
	Specular_.Load("Player_s.png");
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