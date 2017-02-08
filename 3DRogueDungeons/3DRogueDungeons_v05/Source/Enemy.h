/***********************************************************************/
/*! @file  Enemy.h
 *  @brief
 *  
 *  @author 
 *  @date 
 */
/***********************************************************************/
#pragma once

#include"3DCharacter.h"
#include"Player.h"
#include"SphereCollision.h"

class CEnemy :public C3DCharacter
{
public:
	virtual void Initialize(CDungeon*,CPlayer*);
	void Updata();

	BOOL PlayerInfer();

protected:
	CPlayer* pPlayer;
	float InferRadius;
};

