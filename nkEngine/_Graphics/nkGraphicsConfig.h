#pragma once

namespace nkEngine
{
	struct SShadowConfig
	{
		SShadowConfig()
		{
			isEnable = isSoftShadowMap = false;
			ShadowMapW = ShadowMapH = 512;
			Fur = 1000.0f;
			Near = 1.0f;
		}
		bool isEnable; //シャドウマップの有効フラグ
		int ShadowMapW; //シャドウマップの横幅
		int ShadowMapH; //シャドウマップの縦幅
		bool isSoftShadowMap; //ソフトシャドウマップの有効フラグ
		float Fur; //ファー
		float Near; //ニア
	};

	struct SGraphicsConfig
	{
		SShadowConfig ShadowConfig;
	};
}