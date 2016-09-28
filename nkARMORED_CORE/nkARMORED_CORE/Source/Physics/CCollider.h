//コライダー
#pragma once

class CCollider
{
public:
	
	//ボディの取得
	virtual btCollisionShape* GetBody() = 0;
};