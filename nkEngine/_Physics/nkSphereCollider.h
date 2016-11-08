#pragma once

#include"CCollider.h"

namespace nkEngine
{
	class CSphereCollider : public CCollider
	{
	public:

		//コンストラクタ
		CSphereCollider();

		//デストラクタ
		~CSphereCollider();

		//球体コライダー作成
		//param[in] サイズ
		void Create(const float _radius);

		//ボディの取得
		btCollisionShape* GetBody()override
		{
			return m_Shape;
		}

	private:
		btSphereShape* m_Shape; //球体形状
	};

}