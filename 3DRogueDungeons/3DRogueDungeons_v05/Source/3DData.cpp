/***********************************************************************/
/*! @file  3DData.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"3DData.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void C3DData::Initialize()
{
	D3DXLoadMeshFromX(
		this->XfileName,
		D3DXMESH_MANAGED,
		graphicsDevice(),
		NULL,
		&pMaterials,
		NULL,
		&NumMaterials,
		&pMesh
		);
	pTextures = new LPDIRECT3DTEXTURE9[NumMaterials];
	D3DXMATERIAL    *materials = (D3DXMATERIAL*)pMaterials->GetBufferPointer();
	// テクスチャの読み出し
	for (DWORD i = 0; i<NumMaterials; i++)
	{
		pTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(
				graphicsDevice(),
				materials[i].pTextureFilename,          // テクスチャファイル名
				&pTextures[i]);   // テクスチャオブジェクト
		}
	}
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void C3DData::Draw()
{
	for (DWORD i = 0; i < NumMaterials; i++){
		D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(pMaterials->GetBufferPointer());
		(*graphicsDevice()).SetMaterial(&mtrl->MatD3D);
		(*graphicsDevice()).SetTexture(0, pTextures[i]);
		pMesh->DrawSubset(i);
	}
}