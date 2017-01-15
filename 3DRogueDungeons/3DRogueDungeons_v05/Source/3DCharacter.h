#pragma once

#include"3DData.h"
#include"Dungeon.h"

class C3DCharacter :public C3DData
{
public:
	void Initialize(CDungeon*);
	void Draw();

	
	BOOL WallCollision(D3DXVECTOR3);
	void setTrans(D3DXVECTOR3);
	void setFront(D3DXVECTOR3, D3DXVECTOR3);
	void setDD(CDungeon* pDun){ DD = pDun; }
	D3DXVECTOR3 getTrans(){ return vec3Trans; }
	float getRadius(){ return Radius; }
	float getLife(){ return this->LifePoint; }
	void setLife(float Damage){ LifePoint -= Damage; }
	float getDamage(){ return Damage; }
protected:
	float LifePoint;	//ライフポイント
	float Damage;	//ダメージ数
	float Radius;		//半径
	float Speed;		//スピード

	D3DXMATRIX matWorld, matTrans, matScale, matRot;

	D3DXVECTOR3 vec3Trans;
	D3DXVECTOR3 vec3Scale;
	D3DXVECTOR3 vec3Rot;

	D3DXVECTOR3 vec3Front;
	float L;

	CDungeon* DD;
};