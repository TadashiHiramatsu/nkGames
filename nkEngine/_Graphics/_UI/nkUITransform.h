#pragma once

namespace nkEngine
{
	class UITransform
	{
	public:
		UITransform();
		
		//更新
		void Update();
	public:

		D3DXVECTOR2 Position = D3DXVECTOR2(0, 0); //ポジション
		D3DXVECTOR2 Size = D3DXVECTOR2(100, 100);	//サイズ
		D3DXVECTOR2 Pivot = D3DXVECTOR2(0.5f, 0.5f);	//中心
		D3DXQUATERNION Rotation = D3DXQUATERNION(0, 0, 0, 1);	//回転		

		D3DXMATRIX mWorld;
		D3DXMATRIX mLocal;
		D3DXMATRIX* mParent;
	};
}