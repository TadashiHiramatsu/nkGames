/***********************************************************************/
/*! @file  EnemyLabrys.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"Enemy.h"

class CEnemyLabrys :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};