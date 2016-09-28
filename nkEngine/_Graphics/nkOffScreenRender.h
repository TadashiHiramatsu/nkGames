#pragma once

#include"nkRenderTarget.h"
#include"nkSprite.h"
#include"PostEffect\nkAntiAliasing.h"

namespace nkEngine
{
	class COffScreenRender
	{
	public:

		//初期化
		void Init(const SInitParam& initParam);
		
		//更新
		void Update();

		//描画
		void Render();

		//インスタンス取得
		inline static COffScreenRender& GetInstance()
		{
			static COffScreenRender instance;
			return instance;
		}
		
	private:

		//コンストラクタ
		COffScreenRender();
		
		//デストラクタ
		~COffScreenRender();

	private:

		CRenderTarget m_RenderTarget;
		D3DVIEWPORT9 m_viewport;

		CAntiAliasing m_AntiAliasing;

		CSprite full;
	};

	inline static COffScreenRender& OffScreenRender()
	{
		return COffScreenRender::GetInstance();
	}
}