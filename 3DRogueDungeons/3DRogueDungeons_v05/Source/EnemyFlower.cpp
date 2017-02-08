/***********************************************************************/
/*! @file  EnemyFlower.cpp
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#include"EnemyFlower.h"

/***********************************************************************/
/*! @brief 
 * 
 *  @param[in,out] pDun 
 *  @param[in,out] pPla 
 *  @retval void
 */
/***********************************************************************/
void CEnemyFlower::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	XfileName = _T("XFile\\EnemyFlower.x");
	LifePoint = 200.0f;
	Damage = 2.0f;
	Radius = 5.0f;
	InferRadius = 100.0f;
	Speed = 1.0f;
	CEnemy::Initialize(pDun, pPla);
}