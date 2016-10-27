//影関係の関数集

//シャドウ用のテクスチャ
texture g_ShadowMap_0;
sampler g_ShadowMapSampler_0 =
sampler_state
{
	Texture = <g_ShadowMap_0>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_ShadowMap_1;
sampler g_ShadowMapSampler_1 =
sampler_state
{
	Texture = <g_ShadowMap_1>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

texture g_ShadowMap_2;
sampler g_ShadowMapSampler_2 =
sampler_state
{
	Texture = <g_ShadowMap_2>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//シャドウマップの最大数
#define MAX_SHADOW_MAP 3

//シャドウレシーバー用のパラメータ
struct SShadowReceiverParam
{
	float4x4 mLightViewProj[MAX_SHADOW_MAP]; //ライトビュープロジェクション行列
	bool vsmFlag; //バリアンスシャドウマップを行うかのフラグ
	int numShadowMap; //シャドウマップの枚数
};

SShadowReceiverParam g_ShadowReceiverParam; //シャドウレシーバーのパラメータ

//影の計算
//param[in] 一つ目のライトビューポジション
//param[in] 二つ目のライトビューポジション
//param[in] 三つ目のライトビューポジション
//return 影の値
float CalcShadow(
	float4 lightViewPos_0,
	float4 lightViewPos_1,
	float4 lightViewPos_2)
{
	//ループで回せるように
	float4x4 mLightViewPos;
	mLightViewPos[0] = lightViewPos_0;
	mLightViewPos[1] = lightViewPos_1;
	mLightViewPos[2] = lightViewPos_2;

	sampler texSampler[MAX_SHADOW_MAP];
	texSampler[0] = g_ShadowMapSampler_0;
	texSampler[1] = g_ShadowMapSampler_1;
	texSampler[2] = g_ShadowMapSampler_2;

	//return用変数 1のまま返すと影ではない
	float result = 1.0f;

	for (int i = 0; i < g_ShadowReceiverParam.numShadowMap; i++)
	{
		//影落とす
		float4 posInLVP = mLightViewPos[i];
		posInLVP.xyz /= posInLVP.w;

		//uv座標に変換
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
		float2 shadow_val = 1.0f;

		if (shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f)
		{
			shadow_val = tex2D(texSampler[i], shadowMapUV).rg;
			float depth = min(posInLVP.z, 1.0f);

			if (g_ShadowReceiverParam.vsmFlag == 1)
			{
				if (depth > shadow_val.r) {
					//チェビシェフ
					float depth_sq = shadow_val.r * shadow_val.r;
					float variance = max(shadow_val.g - depth_sq, 0.0006f);
					float md = depth - shadow_val.r;
					float P = variance / (variance + md * md);
					result = pow(P, 5.0f);
				}
			}
			else
			{
				if (depth > shadow_val.r + 0.006f)
				{
					result = 0.0f;
				}
			}
			//一枚にヒットしたらループを終わる
			break;
		}
	}
	return result;
}