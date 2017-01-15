#pragma once
#include"IncludeManagers.h"

class C3DData
{
public:
	void Initialize();
	void Draw();
protected:
	ID3DXBuffer *pMaterials;	//�}�e���A���|�C���^
	DWORD NumMaterials;			//�}�e���A����
	ID3DXMesh *pMesh;			//���b�V���|�C���^
	LPCTSTR XfileName;			//X�t�@�C����
	LPDIRECT3DTEXTURE9  *pTextures;
};