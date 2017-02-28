/**
 * @file C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Shader\TransformedPrim.fx
 *
 * �g�����X�t�H�[���ς݃v���~�e�B�u��`��.
 */

/**
 * ���_�V�F�[�_���͏��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_INPUT
{
	float4 Pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

/**
 * ���_�V�F�[�_�o�͏��.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_OUTPUT
{
	float4 Pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

/** �e�N�X�`��. */
texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

/** �I�t�Z�b�g. */
float2 g_Offset;


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

	//uv�̃I�t�Z�b�g�v�Z
	Out.uv = In.uv + g_Offset;
	
	return Out;
}

/**
 * �s�N�Z���V�F�[�_.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 *
 * @param In The in.
 *
 * @return A float4.
 */
float4 PSMain(VS_OUTPUT In) : COLOR0
{
	return tex2D(g_TextureSampler, In.uv);
}

technique TransformedPrim
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}