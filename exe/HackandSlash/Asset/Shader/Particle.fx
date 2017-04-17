//�p�[�e�B�N��

float4x4 g_mWVP;	//���[���h�r���[�v���W�F�N�V�����s��

struct VS_INPUT
{
	float4 pos	:	POSITION;
	float2 uv	:	TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos	:	POSITION;
	float2 uv	:	TEXCOORD0;
};

float g_brightness;	//�P�x
float g_alpha;		//�A���t�@

texture g_texture;	//�f�B�t���[�Y�e�N�X�`��
sampler g_textureSampler =
sampler_state
{
	Texture = <g_texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(In.pos, g_mWVP);
	Out.uv = In.uv;
	return Out;
}

//�����������s�N�Z��
float4 PSMainTrans(VS_OUTPUT In):COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);
	return float4(tex.xyz + g_brightness, tex.a * g_alpha);
}

//���Z�����p�s�N�Z��
float4 PSMainAdd(VS_OUTPUT In):COLOR0
{
	float4 tex = tex2D(g_textureSampler, In.uv);

	return float4(tex.xyz * g_alpha + g_brightness, 1.0f);
}

/*!
* @brief	�����������p�̃e�N�j�b�N�B
*/
technique ColorTexPrimTrans
{
	pass P0
	{
		VertexShader = compile vs_2_0 VSMain();
		PixelShader = compile ps_2_0 PSMainTrans();
	}
}

/*!
* @brief	���Z�p�e�N�j�b�N�B
*/
technique ColorTexPrimAdd
{
	pass P0
	{
		VertexShader = compile vs_2_0 VSMain();
		PixelShader = compile ps_2_0 PSMainAdd();
	}
}