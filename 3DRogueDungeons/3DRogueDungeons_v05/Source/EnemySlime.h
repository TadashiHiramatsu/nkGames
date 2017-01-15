#pragma once

#include"Enemy.h"

class CEnemySlime :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};