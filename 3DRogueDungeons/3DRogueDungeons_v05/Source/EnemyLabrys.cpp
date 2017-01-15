#include"EnemyLabrys.h"

void CEnemyLabrys::Initialize(CDungeon* pDun, CPlayer* pPla)
{
	XfileName = _T("XFile\\EnemyLabrys.x");
	LifePoint = 200.0f;
	Damage = 4.0f;
	Radius = 5.0f;
	InferRadius = 70.0f;
	Speed = 1.0f;
	CEnemy::Initialize(pDun, pPla);
}