#pragma once
#include"IncludeManagers.h"

class C3DData
{
public:
	void Initialize();
	void Draw();
protected:
	ID3DXBuffer *pMaterials;	//マテリアルポインタ
	DWORD NumMaterials;			//マテリアル数
	ID3DXMesh *pMesh;			//メッシュポインタ
	LPCTSTR XfileName;			//Xファイル名
	LPDIRECT3DTEXTURE9  *pTextures;
};