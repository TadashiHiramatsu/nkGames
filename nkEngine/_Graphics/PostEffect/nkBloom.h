#pragma once

#include"..\nkBlur.h"

namespace nkEngine
{
	class CBloom
	{
	public:
		//コンストラクタ
		CBloom();
		//デストラクタ
		~CBloom();
		//描画
		void Render();
		//作成
		void Create(bool);
		//解放
		void Release();
	private:
		void UpdateWeight(float);
	private:
		static const int NUM_WEIGHTS = 8;
		ID3DXEffect* m_pEffect;
		CRenderTarget m_luminanceRenderTarget;
		bool m_isEnable;
		float m_weights[NUM_WEIGHTS];
		CSprite fullscreen;

		CBlur Blur[2];
	};
}