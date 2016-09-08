#include"stdafx.h"
#include"CBuilding.h"
#include"CGameCamera.h"

Parameter param[] = {
#include"werky.h"
};

CBuilding::CBuilding() :
	worldMatrixBuffer(nullptr)
{

}

CBuilding::~CBuilding()
{
	Release();
}

void CBuilding::Init()
{
	skinModelData.LoadModelData("building.X",NULL);
	//インスタンス描画用のデータを作成。
	D3DVERTEXELEMENT9 vertexElement[] = {
		{ 1,  0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },  // WORLD 1行目
		{ 1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },  // WORLD 2行目
		{ 1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },  // WORLD 3行目
		{ 1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },  // WORLD 4行目
		D3DDECL_END()
	};
	int num = sizeof(param) / sizeof(param[0]);
	skinModelData.CreateInstancingDrawData(num, vertexElement);
	worldMatrixBuffer = new D3DXMATRIX[num];
	
	for (int i = 0; i < num; i++) {
		D3DXMATRIX mWorld, mPosition, mScale, m_mRotation;

		D3DXMatrixTranslation(&mPosition, param[i].pos.x, param[i].pos.y, param[i].pos.z);
		D3DXMatrixRotationQuaternion(&m_mRotation, &param[i].rot);
		D3DXMatrixScaling(&mScale, param[i].scale.x, param[i].scale.y, param[i].scale.z);

		mWorld = mScale * m_mRotation * mPosition;
		worldMatrixBuffer[i] = mWorld;
	}

	skinModel.Init(&skinModelData);
	skinModel.SetLight(&light);
	skinModel.SetCamera(g_camera.GetCamera());
	skinModel.SetTransform(&m_trans);

	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
}

void CBuilding::Update()
{
	skinModel.UpdateInstancinfDrawData(worldMatrixBuffer);
	skinModel.Update();

}

void CBuilding::Render()
{
	skinModel.Draw();
}

void CBuilding::Release()
{
	delete[] worldMatrixBuffer;
}
