#pragma once

#include"3DCharacter.h"
#include"camera.h"
#include"Input.h"

class CPlayer :public C3DCharacter
{
public:
	void Initialize(CDungeon*);
	void Updata();
	bool getflg(){ return flg; }
	void setflg(){ flg = false; }
	D3DXVECTOR3 getkou(){ return D3DXVECTOR3(vec3Trans.x + (vec3Front.x*15), 30, vec3Trans.z + (vec3Front.z*15) ); }
	void setEnemyIT(){ EnemyI=true; }
	void setEnemyIF(){ EnemyI = false; }
	bool getEnemyI(){ return EnemyI; }
protected:
	CCamera m_camesa;
	bool flg = false;
	bool Key = false;
	bool Key2 = false;
	bool EnemyI = false;
	float cameras;
};