#include"EnemySlime.h"

void CEnemySlime::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	XfileName = _T("XFile\\EnemySlime.x");
	LifePoint = 100.0f;
	Damage = 1.0f;
	Radius = 5.0f;
	InferRadius = 50.0f;
	Speed = 1.0f;
	CEnemy::Initialize(pDun, pPla);
}