/***********************************************************************/
/*! @file  2DImage.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"IncludeManagers.h"

class C2DImage
{
public:
	C2DImage();
	~C2DImage();
	virtual void Initialize();
	virtual void Update() = 0;
	void Draw(LPD3DXSPRITE);
	void SetupMatrices();
protected:
	D3DXVECTOR2 m_position;			///<位置情報
	float m_angle;					///<回転情報
	D3DXVECTOR2 m_scale;			///<スケール情報
	LPDIRECT3DTEXTURE9 m_pTexture;	///<テクスチャ
	D3DCOLOR m_backColor;			///<背景カラー
	LPCTSTR m_texFileName;			///<テクスチャファイル名
	D3DXVECTOR2 m_texCenter;		///<テクスチャの中点
	RECT m_rect;					///<描画矩形
	D3DXMATRIX m_transformMatrix;	///<変換行列
};
