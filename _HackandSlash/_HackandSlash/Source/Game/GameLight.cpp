#include"stdafx.h"
#include"GameLight.h"

void GameLight::Start()
{
	D3DXVECTOR3 dld;
	D3DXVec3Normalize(&dld, &D3DXVECTOR3(5.0f, -5.0f, 5.0f));
	Light_.SetDiffuseLightDirection(0, dld);
	Light_.SetDiffuseLightColor(0, D3DXVECTOR4(1, 1, 1, 0));
}
