#pragma once

#include"Enemy.h"

class CEnemyInsect :public CEnemy
{
public:
	void Initialize(CDungeon*, CPlayer*)override;
};