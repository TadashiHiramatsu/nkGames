/***********************************************************************/
/*! @file  EnemyFlower.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"Enemy.h"

class CEnemyFlower :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};