#include"EnemyInsect.h"

void CEnemyInsect::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	XfileName = _T("XFile\\EnemyInsect.x");
	LifePoint = 200.0f;
	Damage = 2.0f;
	Radius = 5.0f;
	InferRadius = 70.0f;
	Speed = 1.5f;
	CEnemy::Initialize(pDun, pPla);
}