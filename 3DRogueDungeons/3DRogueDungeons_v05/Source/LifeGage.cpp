/***********************************************************************/
/*! @file  LifeGage.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include "LifeGage.h"


/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CLifeGage::CLifeGage() { }
/***********************************************************************/
/*! @brief 
 * 
 *  @retval  
 */
/***********************************************************************/
CLifeGage::~CLifeGage(){ }

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pPla 
 *  @retval void
 */
/***********************************************************************/
void CLifeGage::Initialize(CPlayer* pPla)
{
	m_position = D3DXVECTOR2(10, 10);
	m_angle = 0.0f;
	m_scale = D3DXVECTOR2(20.0f, 1.0f);
	m_backColor = D3DCOLOR_ARGB(255, 0, 255, 0);
	m_texFileName = "Texture\\Life.png";
	C2DImage::Initialize();
	m_texCenter = D3DXVECTOR2(0, 0);
	pPlayer = pPla;
	MaxLife = pPlayer->getLife();
}

/***********************************************************************/
/*! @brief 
 * 
 *  @retval void
 */
/***********************************************************************/
void CLifeGage::Update()
{
	float Life = pPlayer->getLife();
	if (Life >= 0.0f)
	{
		m_scale.x = Life/ MaxLife * 20;
		if (Life < 100)
		{
			m_backColor = D3DCOLOR_ARGB(255, 255, 0, 0);
		}
		else if (Life < 250)
		{
			m_backColor = D3DCOLOR_ARGB(255, 255, 255, 0);
		}
		else if (Life <= MaxLife)
		{
			m_backColor = D3DCOLOR_ARGB(255, 0, 255, 0);
		}
	}
	this->SetupMatrices();
}