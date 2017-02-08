/***********************************************************************/
/*! @file  EnemyFox.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"EnemyFox.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDun 
 *  @param[in,out] pPla 
 *  @retval void
 */
/***********************************************************************/
void CEnemyFox::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	XfileName = _T("XFile\\EnemyFox.x");
	LifePoint = 300.0f;
	Damage = 2.0f;
	Radius = 5.0f;
	InferRadius = 70.0f;
	Speed = 1.0f;
	CEnemy::Initialize(pDun, pPla);
}