/**
 * @file C:\Github\nkGames\ActionGame\ActionGame\Asset\Shader\Sprite.fx
 *
 * Sprite�p�V�F�[�_.
 */

/** ���[���h�r���[�v���W�F�N�V�����s��. */
float4x4 g_mWVP;

/** UV��`. */
float4 g_RectUV;
/** �F. */
float4 g_Color;

/**
 * ���͒��_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct VS_INPUT
{
	float4 Pos	:	POSITION;
	float2 uv	:	TEXCOORD0;
};

/**
 * �o�͒��_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct VS_OUTPUT
{
	float4 Pos	:	POSITION;
	float2 uv	:	TEXCOORD0;
};

/** �f�B�t���[�Y�e�N�X�`��. */
texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
	Texture = <g_Texture>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

/**
 * ���_�V�F�[�_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 *
 * @param In The in.
 *
 * @return A VS_OUTPUT.
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	//�o�͒��_
	VS_OUTPUT Out;

	//���[���h�s��v�Z
	Out.Pos = mul(In.Pos, g_mWVP);

	//UV�v�Z
	Out.uv = g_RectUV.xy * (1.0f - In.uv) + g_RectUV.zw * (In.uv);

	return Out;
}

/**
 * �s�N�Z���V�F�[�_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSMain(VS_OUTPUT In) : COLOR
{
	//�e�N�X�`���J���[�ǂݍ���
	float4 color = tex2D(g_TextureSampler,In.uv);

	return color * g_Color;
}

technique Sprite
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSMain();
		PixelShader = compile ps_2_0 PSMain();
	}
}