//コライダー
#pragma once

namespace nkEngine
{
	class CCollider
	{
	public:

		//ボディの取得
		virtual btCollisionShape* GetBody() = 0;
	};

}