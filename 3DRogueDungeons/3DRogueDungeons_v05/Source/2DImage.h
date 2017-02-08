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
	D3DXVECTOR2 m_position;			///<�ʒu���
	float m_angle;					///<��]���
	D3DXVECTOR2 m_scale;			///<�X�P�[�����
	LPDIRECT3DTEXTURE9 m_pTexture;	///<�e�N�X�`��
	D3DCOLOR m_backColor;			///<�w�i�J���[
	LPCTSTR m_texFileName;			///<�e�N�X�`���t�@�C����
	D3DXVECTOR2 m_texCenter;		///<�e�N�X�`���̒��_
	RECT m_rect;					///<�`���`
	D3DXMATRIX m_transformMatrix;	///<�ϊ��s��
};
