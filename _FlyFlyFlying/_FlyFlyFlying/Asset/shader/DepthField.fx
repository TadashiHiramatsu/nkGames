//被写界深度

struct VS_BlurOutput {
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
	float2 tex1 : TEXCOORD1;
	float2 tex2 : TEXCOORD2;
	float2 tex3 : TEXCOORD3;
	float2 tex4 : TEXCOORD4;
	float2 tex5 : TEXCOORD5;
	float2 tex6 : TEXCOORD6;
	float2 tex7 : TEXCOORD7;
};

struct VS_BlurInput {
	float4 pos : POSITION;

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



float2 g_TexSize;
float2 g_offset;
float g_weight[8];

VS_BlurOutput VSXBlur(VS_BlurInput In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
		tex.y = 1.0f - tex.y;
	tex += float2(0.5f / g_TexSize.x, 0.5f / g_TexSize.y);
	Out.tex0 = tex + float2(-1.0f / g_TexSize.x, 0.0f);
	Out.tex1 = tex + float2(-3.0f / g_TexSize.x, 0.0f);
	Out.tex2 = tex + float2(-5.0f / g_TexSize.x, 0.0f);
	Out.tex3 = tex + float2(-7.0f / g_TexSize.x, 0.0f);
	Out.tex4 = tex + float2(-9.0f / g_TexSize.x, 0.0f);
	Out.tex5 = tex + float2(-11.0f / g_TexSize.x, 0.0f);
	Out.tex6 = tex + float2(-13.0f / g_TexSize.x, 0.0f);
	Out.tex7 = tex + float2(-15.0f / g_TexSize.x, 0.0f);
	return Out;
}

float4 PSXBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;
	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
		+ tex2D(g_blurSampler, In.tex7 + g_offset));
	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
		+ tex2D(g_blurSampler, In.tex6 + g_offset));
	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
		+ tex2D(g_blurSampler, In.tex5 + g_offset));
	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
		+ tex2D(g_blurSampler, In.tex4 + g_offset));
	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
		+ tex2D(g_blurSampler, In.tex3 + g_offset));
	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
		+ tex2D(g_blurSampler, In.tex2 + g_offset));
	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
		+ tex2D(g_blurSampler, In.tex1 + g_offset));
	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
		+ tex2D(g_blurSampler, In.tex0 + g_offset));
	return Color;
}

VS_BlurOutput VSYBlur(VS_BlurInput In)
{
	VS_BlurOutput Out;
	Out.pos = In.pos;
	float2 tex = (In.pos * 0.5f) + 0.5f;
		tex.y = 1.0f - tex.y;
	tex += float2(0.5 / g_TexSize.x, 0.5 / g_TexSize.y);
	Out.tex0 = tex + float2(0.0f, -1.0f / g_TexSize.y);
	Out.tex1 = tex + float2(0.0f, -3.0f / g_TexSize.y);
	Out.tex2 = tex + float2(0.0f, -5.0f / g_TexSize.y);
	Out.tex3 = tex + float2(0.0f, -7.0f / g_TexSize.y);
	Out.tex4 = tex + float2(0.0f, -9.0f / g_TexSize.y);
	Out.tex5 = tex + float2(0.0f, -11.0f / g_TexSize.y);
	Out.tex6 = tex + float2(0.0f, -13.0f / g_TexSize.y);
	Out.tex7 = tex + float2(0.0f, -15.0f / g_TexSize.y);
	return Out;
}
/*!
* @brief	Yブラーピクセルシェーダー。
*/
float4 PSYBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;
	Color = g_weight[0] * (tex2D(g_blurSampler, In.tex0)
		+ tex2D(g_blurSampler, In.tex7 + g_offset));
	Color += g_weight[1] * (tex2D(g_blurSampler, In.tex1)
		+ tex2D(g_blurSampler, In.tex6 + g_offset));
	Color += g_weight[2] * (tex2D(g_blurSampler, In.tex2)
		+ tex2D(g_blurSampler, In.tex5 + g_offset));
	Color += g_weight[3] * (tex2D(g_blurSampler, In.tex3)
		+ tex2D(g_blurSampler, In.tex4 + g_offset));
	Color += g_weight[4] * (tex2D(g_blurSampler, In.tex4)
		+ tex2D(g_blurSampler, In.tex3 + g_offset));
	Color += g_weight[5] * (tex2D(g_blurSampler, In.tex5)
		+ tex2D(g_blurSampler, In.tex2 + g_offset));
	Color += g_weight[6] * (tex2D(g_blurSampler, In.tex6)
		+ tex2D(g_blurSampler, In.tex1 + g_offset));
	Color += g_weight[7] * (tex2D(g_blurSampler, In.tex7)
		+ tex2D(g_blurSampler, In.tex0 + g_offset));
	return Color;
}

/*!
* @brief	横ブラー
*/
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSXBlur();
		PixelShader = compile ps_2_0 PSXBlur();
	}
}

/*!
* @brief	縦ブラー
*/
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSYBlur();
		PixelShader = compile ps_2_0 PSYBlur();
	}
}

//ここから被写界深度
float g_Near; //ブラーが開始される近距離
float g_Far; //最もブラーが強くかかる遠距離
float g_Len; //g_Far-g_Near

//そのままのTexture
texture g_tex0;
sampler g_tex0Sampler =
sampler_state
{
	Texture = <g_tex0>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//深度のTexture
texture g_tex1;
sampler g_tex1Sampler =
sampler_state
{
	Texture = <g_tex1>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};


//ぼかしたTexture
texture g_tex2;
sampler g_tex2Sampler =
sampler_state
{
	Texture = <g_tex2>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//さらにぼかしたTexture
texture g_tex3;
sampler g_tex3Sampler =
sampler_state
{
	Texture = <g_tex3>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT VSDepthField(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.Pos = In.Pos;
	Out.Tex = In.Tex;
	return Out;
}

float4 PSDepthField(VS_OUTPUT In) : COLOR
{
	//バックバッファのZ値を取得
	float z = tex2D(g_tex1Sampler, In.Tex).r;

//if (0.0f <= z && z<0.25f)
//{
//	z = z * 4;
//}
//else if (0.25f<=z&&z<0.75)
//{
//	z = 1.0f;
//}
//else if (0.75f<=z&&z<=1.0f)
//{
//	z = (1 - z) * 4;
//}

float4 Out;

if (g_Far <= z)//遠距離
{
	Out = tex2D(g_tex3Sampler, In.Tex);
}
else if (g_Near >= z)//近距離
{
	Out = tex2D(g_tex0Sampler, In.Tex);
}
else//中間
{
	//z値が0.0f～1.0fの範囲内での値に変換する
	float ConvZ = (z - g_Near) / g_Len;

	if (ConvZ < 0.5f)
	{
		ConvZ *= 2.0f;
		Out = tex2D(g_tex0Sampler, In.Tex)*(1.0f - ConvZ) + tex2D(g_tex2Sampler, In.Tex)*ConvZ;
	}
	else
	{
		ConvZ -= 0.5f;
		ConvZ *= 2.0f;
		Out = tex2D(g_tex2Sampler, In.Tex)*(1.0f - ConvZ) + tex2D(g_tex3Sampler, In.Tex)*ConvZ;
	}

}

return Out;
}

//画像合成
technique DepthField
{
	pass p0
	{
		VertexShader = compile vs_1_1 VSDepthField();
		PixelShader = compile ps_2_0 PSDepthField();
	}
}