/**
 * @file C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Shader\Bloom.fx
 *
 * ブルームシェーダ.
 */

/** シーンテクスチャ. */
texture g_Scene;
sampler g_SceneSampler =
sampler_state
{
	Texture = <g_Scene>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

/**
 * 頂点シェーダ入力頂点.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_INPUT
{
	float4 Pos : POSITION;
};

/**
 * 頂点シェーダ出力頂点.
 * ピクセルシェーダ入力頂点.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD;
};

/**
 * 輝度抽出頂点シェーダ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A VS_OUTPUT.
 */
VS_OUTPUT VSSamplingLuminance(VS_INPUT In)
{
	VS_OUTPUT Out;
	//トランスフォーム済み頂点なのでそのまま
	Out.Pos = In.Pos;
	Out.Tex = (In.Pos * 0.5f) + 0.5f;
	Out.Tex.y = 1.0f - Out.Tex.y;
	return Out;
}

/**
 * 輝度抽出ピクセルシェーダ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSSamplingLuminance(VS_OUTPUT In) : COLOR
{
	//カラー取得
	float4 color = tex2D(g_SceneSampler, In.tex);

	float4 t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));

	//輝度が1.0より小さいとき現在のピクセルを破棄
	clip(color.a - 1.001f);
	
	color.xyz *= (t - 1.0f);
	color.a = 1.0f;
	
	return color;
}

//
//struct VS_BlurOutput
//{
//	float4 pos	: POSITION;
//	float2 tex0	: TEXCOORD0;
//	float2 tex1 : TEXCOORD1;
//	float2 tex2 : TEXCOORD2;
//	float2 tex3 : TEXCOORD3;
//	float2 tex4 : TEXCOORD4;
//	float2 tex5 : TEXCOORD5;
//	float2 tex6 : TEXCOORD6;
//	float2 tex7 : TEXCOORD7;
//};
//
//texture g_blur;
//sampler g_blurSampler = 
//sampler_state
//{
//	Texture = <g_blur>;
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
//
//float2 g_luminanceTexSize;
//float2 g_offset;
//float g_weight[8];
//
//VS_BlurOutput VSXBlur(VS_INPUT In)
//{
//	VS_BlurOutput Out;
//	Out.pos = In.pos;
//	float2 tex = (In.pos * 0.5f) + 0.5f;
//		tex.y = 1.0f - tex.y;
//	tex += float2(0.5f / g_luminanceTexSize.x, 0.5f / g_luminanceTexSize.y);
//	Out.tex0 = tex + float2(-1.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex1 = tex + float2(-3.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex2 = tex + float2(-5.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex3 = tex + float2(-7.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex4 = tex + float2(-9.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex5 = tex + float2(-11.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex6 = tex + float2(-13.0f / g_luminanceTexSize.x, 0.0f);
//	Out.tex7 = tex + float2(-15.0f / g_luminanceTexSize.x, 0.0f);
//	return Out;
//}
//
//float4 PSXBlur(VS_BlurOutput In) : COLOR
//{
//	float4 Color;
//	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
//		+ tex2D(g_blurSampler, In.tex7 + g_offset));
//	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
//		+ tex2D(g_blurSampler, In.tex6 + g_offset));
//	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
//		+ tex2D(g_blurSampler, In.tex5 + g_offset));
//	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
//		+ tex2D(g_blurSampler, In.tex4 + g_offset));
//	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
//		+ tex2D(g_blurSampler, In.tex3 + g_offset));
//	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
//		+ tex2D(g_blurSampler, In.tex2 + g_offset));
//	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
//		+ tex2D(g_blurSampler, In.tex1 + g_offset));
//	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
//		+ tex2D(g_blurSampler, In.tex0 + g_offset));
//	return Color;
//}
//
//VS_BlurOutput VSYBlur(VS_INPUT In)
//{
//	VS_BlurOutput Out;
//	Out.pos = In.pos;
//	float2 tex = (In.pos * 0.5f) + 0.5f;
//		tex.y = 1.0f - tex.y;
//	tex += float2(0.5 / g_luminanceTexSize.x, 0.5 / g_luminanceTexSize.y);
//	Out.tex0 = tex + float2(0.0f, -1.0f / g_luminanceTexSize.y);
//	Out.tex1 = tex + float2(0.0f, -3.0f / g_luminanceTexSize.y);
//	Out.tex2 = tex + float2(0.0f, -5.0f / g_luminanceTexSize.y);
//	Out.tex3 = tex + float2(0.0f, -7.0f / g_luminanceTexSize.y);
//	Out.tex4 = tex + float2(0.0f, -9.0f / g_luminanceTexSize.y);
//	Out.tex5 = tex + float2(0.0f, -11.0f / g_luminanceTexSize.y);
//	Out.tex6 = tex + float2(0.0f, -13.0f / g_luminanceTexSize.y);
//	Out.tex7 = tex + float2(0.0f, -15.0f / g_luminanceTexSize.y);
//	return Out;
//}
///*!
//* @brief	Yブラーピクセルシェーダー。
//*/
//float4 PSYBlur(VS_BlurOutput In) : COLOR
//{
//	float4 Color;
//	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
//		+ tex2D(g_blurSampler, In.tex7 + g_offset));
//	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
//		+ tex2D(g_blurSampler, In.tex6 + g_offset));
//	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
//		+ tex2D(g_blurSampler, In.tex5 + g_offset));
//	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
//		+ tex2D(g_blurSampler, In.tex4 + g_offset));
//	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
//		+ tex2D(g_blurSampler, In.tex3 + g_offset));
//	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
//		+ tex2D(g_blurSampler, In.tex2 + g_offset));
//	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
//		+ tex2D(g_blurSampler, In.tex1 + g_offset));
//	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
//		+ tex2D(g_blurSampler, In.tex0 + g_offset));
//	return Color;
//}

/**
 * ファイナルの頂点シェーダ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A VS_OUTPUT.
 */
VS_OUTPUT VSFinal(VS_INPUT In)
{
	VS_OUTPUT Out;

	//トランスフォーム済み頂点なのでそのまま
	Out.pos = In.pos;
	Out.tex = (In.pos.xy * 0.5f) + 0.5f;
	Out.tex.y = 1.0f - Out.tex.y;
	Out.tex += g_offset;

	return Out;
}

/**
 * ファイナルのピクセルシェーダ.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSFinal(VS_OUTPUT In) : COLOR
{
	float2 uv = In.tex;
	return clamp(tex2D(g_blurSampler, uv), 0.0f, 1.0f);
}

technique SamplingLuminance
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSSamplingLuminance();
		PixelShader = compile ps_3_0 PSSamplingLuminance();
	}
}

///*!
//* @brief	横ブラー
//*/
//technique XBlur
//{
//	pass p0
//	{
//		VertexShader = compile vs_3_0 VSXBlur();
//		PixelShader = compile ps_3_0 PSXBlur();
//	}
//}
//
///*!
//* @brief	縦ブラー
//*/
//technique YBlur
//{
//	pass p0
//	{
//		VertexShader = compile vs_3_0 VSYBlur();
//		PixelShader = compile ps_3_0 PSYBlur();
//	}
//}

technique Final
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSFinal();
		PixelShader = compile ps_3_0 PSFinal();
	}
}