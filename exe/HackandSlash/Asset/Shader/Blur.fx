//ブラー

struct VS_INPUT {
	float4 pos : POSITION;
	float2 tex : TEXCOORD0;
};

struct VS_OUTPUT_BLUR {
	float4 pos	: POSITION;
	float2 tex0	: TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
};

texture g_blur;
sampler g_blurSampler =
sampler_state
{
	Texture = <g_blur>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

float2 g_texSize; //テクスチャのサイズ


//Xブラーの頂点シェーダー
VS_OUTPUT_BLUR VSBlur_X(VS_INPUT In)
{
	VS_OUTPUT_BLUR Out;
	Out.pos = In.pos;

	float2 tex = In.tex;

	Out.tex0 = tex;
	Out.tex1 = float2(0.5f / g_texSize.x, 0.0f);
	Out.tex2 = float2(1.0f / g_texSize.x, 0.0f);

	return Out;
}

//Yブラーの頂点シェーダー
VS_OUTPUT_BLUR VSBlur_Y(VS_INPUT In)
{
	VS_OUTPUT_BLUR Out;
	Out.pos = In.pos;

	float2 tex = In.tex;

	Out.tex0 = tex;
	Out.tex1 = float2(0.0f, 0.5f / g_texSize.y);
	Out.tex2 = float2(0.0f, 1.0f / g_texSize.y);

	return Out;
}

//ブラーのピクセルシェーダー
float4 PSBlur(VS_OUTPUT_BLUR In) : COLOR
{
	float4 Color;

//5点ブラー
Color = tex2D(g_blurSampler, In.tex0);
Color += tex2D(g_blurSampler, In.tex0 + In.tex1);
Color += tex2D(g_blurSampler, In.tex0 - In.tex1);
Color += tex2D(g_blurSampler, In.tex0 + In.tex2);
Color += tex2D(g_blurSampler, In.tex0 - In.tex2);
Color /= 5.0f;

	return Color;
}


//横ブラー
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSBlur_X();
		PixelShader = compile ps_3_0 PSBlur();
	}
}

//縦ブラー
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSBlur_Y();
		PixelShader = compile ps_3_0 PSBlur();
	}
}