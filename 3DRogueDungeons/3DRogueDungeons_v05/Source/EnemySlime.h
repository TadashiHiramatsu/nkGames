/***********************************************************************/
/*! @file  EnemySlime.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"Enemy.h"

class CEnemySlime :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};