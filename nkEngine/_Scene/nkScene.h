#pragma once 

#include"..\_Graphics\nkGraphicsConfig.h"

namespace nkEngine
{
	//シーンの基底クラス
	//このクラスを継承する
	class IScene
	{
	public:

		//コンストラクタ
		IScene();
		//デストラクタ
		virtual ~IScene();

	public:

		//初期化
		virtual void Start() {}

		//グラフィックコンフィグの取得
		const SGraphicsConfig& GetGraphicsConfig()
		{
			return m_GraphicsConfig;
		}

	protected:
		SGraphicsConfig m_GraphicsConfig;
	};
}
