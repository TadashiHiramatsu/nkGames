#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	//シーンの基底クラス
	//このクラスを継承する
	class CScene
	{
	public:

		//コンストラクタ
		CScene();

		//デストラクタ
		virtual ~CScene();

		//初期化
		virtual void Init() = 0;

		//更新
		virtual void Update() = 0;
		
		//描画
		virtual void Render() = 0;
		
		//解放
		virtual void Release() = 0;

		//グラフィックコンフィグの取得
		const SGraphicsConfig& GetGraphicsConfig()
		{
			return m_GraphicsConfig;
		}

	protected:
		SGraphicsConfig m_GraphicsConfig;
	};
}
