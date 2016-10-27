#include"stdafx.h"
#include"CLeftArm.h"

CLeftArm::CLeftArm()
{
}

CLeftArm::~CLeftArm()
{
}

void CLeftArm::Update()
{

	m_ACModel.FindBoneRotationMatrix("Elbow",&rot);


	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &D3DXVECTOR3(1,0,0), D3DXToRadian(90.0f));
	D3DXMatrixRotationQuaternion(&rot, &q);

	CParts::Update();

}