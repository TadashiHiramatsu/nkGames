#pragma once

#include"nkRenderTarget.h"
#include"nkSprite.h"
#include"PostEffect\nkAntiAliasing.h"

namespace nkEngine
{
	class CScreenRender
	{
	public:

		//初期化
		void Init(const SInitParam& initParam);
		
		//更新
		void Update();

		//描画
		void Render();

		//メインレンダーターゲットを取得
		CRenderTarget& GetMainRenderTarget()
		{
			return m_rtMain;
		}

		//インスタンス取得
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}
		
	private:

		//コンストラクタ
		CScreenRender();
		
		//デストラクタ
		~CScreenRender();

	private:
		CRenderTarget m_rtBackBuffer;
		CRenderTarget m_rtMain;

		CAntiAliasing m_AntiAliasing;
	};

	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
}