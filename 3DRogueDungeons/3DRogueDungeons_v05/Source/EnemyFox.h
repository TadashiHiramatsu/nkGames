/***********************************************************************/
/*! @file  EnemyFox.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"Enemy.h"

class CEnemyFox :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};