/**
 * @file C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Shader\Bloom.fx
 *
 * �u���[���V�F�[�_.
 */

/** �V�[���e�N�X�`��. */
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
 * ���_�V�F�[�_���͒��_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_INPUT
{
	float4 Pos : POSITION; 
};

/**
 * ���_�V�F�[�_�o�͒��_.
 * �s�N�Z���V�F�[�_���͒��_.
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
 * ���_�V�F�[�_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A VS_OUTPUT.
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.Pos = In.Pos;
	Out.Tex = (In.Pos * 0.5f) + 0.5f;
	Out.Tex.y = 1.0f - Out.Tex.y;
	return Out;
}

/**
 * �P�x���o�s�N�Z���V�F�[�_.
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
	//�J���[�擾
	float4 color = tex2D(g_SceneSampler, In.Tex);

	//�P�x�𒊏o
	// float3(0.299f , 0.587f , 0.114f ); NTSC�W���A���{��k�Ăł̃e���r�p�̋K�i�B
	// float3(0.2125f, 0.7154f, 0.0721f); ��ʓI��sRGB�F��Ԃ̃��j�^
	// �΂ɋP�x��񂪋���.
	float4 t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));

	//�P�x��1.0f��菬�����Ƃ����݂̃s�N�Z����j��
	clip(t - 1.001f);
	
	//�P�x��1.0f��葽���̂Ō����Ă���
	color.xyz *= (t - 1.0f);
	color.a = 1.0f;
	
	return color;
}

/**
 * �u���[�p���_�V�F�[�_�o�͒��_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 */
struct VS_BlurOutput
{
	float4 Pos	: POSITION;
	float2 Tex0	: TEXCOORD0;
	float2 Tex1 : TEXCOORD1;
	float2 Tex2 : TEXCOORD2;
	float2 Tex3 : TEXCOORD3;
	float2 Tex4 : TEXCOORD4;
	float2 Tex5 : TEXCOORD5;
	float2 Tex6 : TEXCOORD6;
	float2 Tex7 : TEXCOORD7;
};

/** �u���[�e�N�X�`��. */
texture g_Blur;
sampler g_BlurSampler =
sampler_state
{
	Texture = <g_Blur>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

/** �P�x�e�N�X�`���̃T�C�Y. */
float2 g_LuminanceTexSize;
/** �I�t�Z�b�g. */
float2 g_Offset;
/** �K�E�X�t�B���^�̏d��. */
float g_Weight[8];

/**
 * X�u���[���_�V�F�[�_�[.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 *
 * @param In The in.
 *
 * @return A VS_BlurOutput.
 */
VS_BlurOutput VSXBlur(VS_INPUT In)
{
	VS_BlurOutput Out;

	//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.Pos = In.Pos;

	//uv���W�ɕϊ���A�c�����t�ɕϊ�
	float2 tex = (In.Pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;

	//uv���W���v�Z
	tex += float2(0.5 / g_LuminanceTexSize.x, 0.5 / g_LuminanceTexSize.y);
	Out.Tex0 = tex + float2(-1.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex1 = tex + float2(-3.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex2 = tex + float2(-5.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex3 = tex + float2(-7.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex4 = tex + float2(-9.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex5 = tex + float2(-11.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex6 = tex + float2(-13.0f / g_LuminanceTexSize.x, 0.0f);
	Out.Tex7 = tex + float2(-15.0f / g_LuminanceTexSize.x, 0.0f);

	return Out;
}

/**
 * X�u���[�s�N�Z���V�F�[�_�[.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSXBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;

	Color = g_Weight[0] * (tex2D(g_BlurSampler, In.Tex0)
		+ tex2D(g_BlurSampler, In.Tex7 + g_Offset));
	Color += g_Weight[1] * (tex2D(g_BlurSampler, In.Tex1)
		+ tex2D(g_BlurSampler, In.Tex6 + g_Offset));
	Color += g_Weight[2] * (tex2D(g_BlurSampler, In.Tex2)
		+ tex2D(g_BlurSampler, In.Tex5 + g_Offset));
	Color += g_Weight[3] * (tex2D(g_BlurSampler, In.Tex3)
		+ tex2D(g_BlurSampler, In.Tex4 + g_Offset));
	Color += g_Weight[4] * (tex2D(g_BlurSampler, In.Tex4)
		+ tex2D(g_BlurSampler, In.Tex3 + g_Offset));
	Color += g_Weight[5] * (tex2D(g_BlurSampler, In.Tex5)
		+ tex2D(g_BlurSampler, In.Tex2 + g_Offset));
	Color += g_Weight[6] * (tex2D(g_BlurSampler, In.Tex6)
		+ tex2D(g_BlurSampler, In.Tex1 + g_Offset));
	Color += g_Weight[7] * (tex2D(g_BlurSampler, In.Tex7)
		+ tex2D(g_BlurSampler, In.Tex0 + g_Offset));

	return Color;
}

/**
 * Y�u���[���_�V�F�[�_�[.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 *
 * @param In The in.
 *
 * @return A VS_BlurOutput.
 */
VS_BlurOutput VSYBlur(VS_INPUT In)
{
	VS_BlurOutput Out;

	//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.Pos = In.Pos;
	
	float2 tex = (In.Pos * 0.5f) + 0.5f;
	tex.y = 1.0f - tex.y;

	tex += float2(0.5 / g_LuminanceTexSize.x, 0.5 / g_LuminanceTexSize.y);
	Out.Tex0 = tex + float2(0.0f, -1.0f / g_LuminanceTexSize.y);
	Out.Tex1 = tex + float2(0.0f, -3.0f / g_LuminanceTexSize.y);
	Out.Tex2 = tex + float2(0.0f, -5.0f / g_LuminanceTexSize.y);
	Out.Tex3 = tex + float2(0.0f, -7.0f / g_LuminanceTexSize.y);
	Out.Tex4 = tex + float2(0.0f, -9.0f / g_LuminanceTexSize.y);
	Out.Tex5 = tex + float2(0.0f, -11.0f / g_LuminanceTexSize.y);
	Out.Tex6 = tex + float2(0.0f, -13.0f / g_LuminanceTexSize.y);
	Out.Tex7 = tex + float2(0.0f, -15.0f / g_LuminanceTexSize.y);

	return Out;
}

/**
 * Y�u���[�s�N�Z���V�F�[�_�[.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSYBlur(VS_BlurOutput In) : COLOR
{
	float4 Color;

	Color = g_Weight[0] * (tex2D(g_BlurSampler, In.Tex0)
		+ tex2D(g_BlurSampler, In.Tex7 + g_Offset));
	Color += g_Weight[1] * (tex2D(g_BlurSampler, In.Tex1)
		+ tex2D(g_BlurSampler, In.Tex6 + g_Offset));
	Color += g_Weight[2] * (tex2D(g_BlurSampler, In.Tex2)
		+ tex2D(g_BlurSampler, In.Tex5 + g_Offset));
	Color += g_Weight[3] * (tex2D(g_BlurSampler, In.Tex3)
		+ tex2D(g_BlurSampler, In.Tex4 + g_Offset));
	Color += g_Weight[4] * (tex2D(g_BlurSampler, In.Tex4)
		+ tex2D(g_BlurSampler, In.Tex3 + g_Offset));
	Color += g_Weight[5] * (tex2D(g_BlurSampler, In.Tex5)
		+ tex2D(g_BlurSampler, In.Tex2 + g_Offset));
	Color += g_Weight[6] * (tex2D(g_BlurSampler, In.Tex6)
		+ tex2D(g_BlurSampler, In.Tex1 + g_Offset));
	Color += g_Weight[7] * (tex2D(g_BlurSampler, In.Tex7)
		+ tex2D(g_BlurSampler, In.Tex0 + g_Offset));

	return Color;
}

/** �ڂ������摜1����. */
texture g_CombineTex00;
sampler g_CombineSampler00 =
sampler_state
{
	Texture = <g_CombineTex00>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
/** �ڂ������摜2����. */
texture g_CombineTex01;
sampler g_CombineSampler01 =
sampler_state
{
	Texture = <g_CombineTex01>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
/** �ڂ������摜3����. */
texture g_CombineTex02;
sampler g_CombineSampler02 =
sampler_state
{
	Texture = <g_CombineTex02>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
/** �ڂ������摜4����. */
texture g_CombineTex03;
sampler g_CombineSampler03 =
sampler_state
{
	Texture = <g_CombineTex03>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
/** �ڂ������摜5����. */
texture g_CombineTex04;
sampler g_CombineSampler04 =
sampler_state
{
	Texture = <g_CombineTex04>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

/**
 * �����s�N�Z���V�F�[�_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/17
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSCombine(VS_OUTPUT In) : COLOR
{
	float2 uv = In.Tex;
	uv += g_Offset;

	float4 combineColor = tex2D(g_CombineSampler00, uv);
	combineColor += tex2D(g_CombineSampler01, uv);
	combineColor += tex2D(g_CombineSampler02, uv);
	combineColor += tex2D(g_CombineSampler03, uv);
	combineColor += tex2D(g_CombineSampler04, uv);
	combineColor.xyz /= 5.0f;
	
	return combineColor;
}

/**
 * �t�@�C�i���̒��_�V�F�[�_.
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

	//�g�����X�t�H�[���ςݒ��_�Ȃ̂ł��̂܂�
	Out.Pos = In.Pos;
	Out.Tex = (In.Pos.xy * 0.5f) + 0.5f;
	Out.Tex.y = 1.0f - Out.Tex.y;
	Out.Tex += g_Offset;

	return Out;
}

/**
 * �t�@�C�i���̃s�N�Z���V�F�[�_.
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
	float2 uv = In.Tex;
	return clamp(tex2D(g_BlurSampler, uv), 0.0f, 1.0f);
}

/**
 * �P�x���o�̃e�N�j�b�N.
 *
 * @return The sampling luminance.
 */
technique SamplingLuminance
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSSamplingLuminance();
	}
}

/**
 * ���u���[.
 *
 * @return The x coordinate blur.
 */
technique XBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSXBlur();
		PixelShader = compile ps_3_0 PSXBlur();
	}
}

/**
 * �c�u���[.
 *
 * @return The y coordinate blur.
 */
technique YBlur
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSYBlur();
		PixelShader = compile ps_3_0 PSYBlur();
	}
}

/**
 * ����.
 *
 * @return The combine.
 */
technique Combine
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSCombine();
	}
}

/**
 * �t�@�C�i��.
 *
 * @return The final.
 */
technique Final
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSFinal();
		PixelShader = compile ps_3_0 PSFinal();
	}
}