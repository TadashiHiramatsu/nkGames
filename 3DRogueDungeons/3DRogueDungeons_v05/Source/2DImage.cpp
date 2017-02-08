/***********************************************************************/
/*! @file  2DImage.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "2DImage.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
C2DImage::C2DImage()
{
}


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
C2DImage::~C2DImage()
{
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void C2DImage::Initialize()
{
	D3DXIMAGE_INFO imgInfo;										//�摜���i�[�p�\����
	D3DXCreateTextureFromFileEx(
		graphicsDevice(),
		this->m_texFileName,
		0,
		0,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&imgInfo,
		NULL,
		&this->m_pTexture
		);	//�e�N�X�`���Ǎ�
	this->m_texCenter = D3DXVECTOR2((float)imgInfo.Width / 2, (float)imgInfo.Height / 2);	//�e�N�X�`���̒��_�Z�b�g
	RECT rec = { 0, 0, imgInfo.Width, imgInfo.Height };			//�`��̈�
	memcpy(&this->m_rect, &rec, sizeof(RECT));					//�`��̈�Z�b�g
}

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pSprite 
 *  @retval void
 */
/***********************************************************************/
void C2DImage::Draw(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);		//�X�v���C�g�`��J�n
	pSprite->SetTransform(&this->m_transformMatrix);	//�ϊ��s��Z�b�g
	pSprite->Draw(this->m_pTexture, &this->m_rect, &D3DXVECTOR3(this->m_texCenter.x, this->m_texCenter.y, 0.0f), NULL, this->m_backColor);	//�X�v���C�g�Ƀe�N�X�`���\�t��
	pSprite->End();	//�X�v���C�g�`��I��
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void C2DImage::SetupMatrices()
{
	D3DXMatrixIdentity(&this->m_transformMatrix);	//���[���h�s�񏉊���
	D3DXMatrixTransformation2D(&this->m_transformMatrix, NULL, 0.0f, &this->m_scale, NULL, D3DXToRadian(this->m_angle), &this->m_position);	//�ϊ��s��쐬
}