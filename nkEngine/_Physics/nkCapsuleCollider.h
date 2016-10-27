#pragma once

#include"CCollider.h"

namespace nkEngine
{
	//カプセルコライダー
	class CCapsuleCollider : public CCollider
	{
	public:
		CCapsuleCollider();
		~CCapsuleCollider();

		//カプセルコライダー作成
		//param[in] サイズ
		void Create(float radius, float height)
		{
			m_Shape = new btCapsuleShape(radius, height);
		}

		//ボディの取得
		btCollisionShape* GetBody()override
		{
			return m_Shape;
		}

	private:
		btCapsuleShape* m_Shape; //ボックス形状
	};
}