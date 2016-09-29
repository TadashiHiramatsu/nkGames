//アンチエイリアシング
#pragma once

namespace nkEngine
{

	//ポストエフェクトによるアンチエイリアス
	class CAntiAliasing
	{
	public:

		//コンストラクタ
		CAntiAliasing();

		//デストラクタ
		~CAntiAliasing();
		
		//初期化
		void Init();

		//描画 
		void Render();

		//解放
		void Release();

	private:
		bool m_isEnable; //有効フラグ
		ID3DXEffect* m_effect; //エフェクト

		float texSize[2];

		CSprite full;
	};
}