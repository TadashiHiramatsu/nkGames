#pragma once

#include"Source\Physics\CCollider.h"

class CBoxCollider : public CCollider
{
public:

	//コンストラクタ
	CBoxCollider();

	//デストラクタ
	~CBoxCollider();

	//ボックスコライダー作成
	//param[in] サイズ
	void Create(const D3DXVECTOR3& size);

	//ボディの取得
	btCollisionShape* GetBody()override
	{
		return m_Shape;
	}

private:
	btBoxShape* m_Shape; //ボックス形状
};