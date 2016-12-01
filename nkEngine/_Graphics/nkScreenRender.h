#pragma once

#include"_PostEffect\nkAntiAliasing.h"
#include"_PostEffect\nkBloom.h"

namespace nkEngine
{
	class CScreenRender
	{
	private:

		//コンストラクタ
		CScreenRender();
		//デストラクタ
		~CScreenRender();

	public:

		//インスタンス取得
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}

		//初期化
		void Start(const SInitParam& initParam);

		void Loop();

		//メインレンダーターゲットを取得
		CRenderTarget& GetMainRenderTarget()
		{
			return m_rtMain;
		}

	private:
		CRenderTarget m_rtBackBuffer;
		CRenderTarget m_rtMain;

		CAntiAliasing m_AntiAliasing;
		CBloom m_Bloom;
	};

	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
}