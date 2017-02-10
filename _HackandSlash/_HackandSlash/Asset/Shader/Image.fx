/**
 * @file C:\Github\nkGames\ActionGame\ActionGame\Asset\Shader\Image.fx
 *
 * ImageUI�̃V�F�[�_.
 */

/** �f�B�t���[�Y�e�N�X�`��. */
texture g_diffuseTexture;
sampler g_diffuseTextureSampler =
sampler_state
{
	Texture = <g_diffuseTexture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4x4 matWorld; //���[���h�s��.
float4 uvRect; //UV��`.
float4 color; //�F.

/** ���m�N���t���O. */
bool isMonochrome;

struct VS_IN
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

struct VS_OUT
{
	float4 pos		: POSITION;
	float2 uv		: TEXCOORD0;
};

VS_OUT vs_main(VS_IN In)
{
	VS_OUT Out;

	//���W�v�Z
	Out.pos = mul(In.pos, matWorld);
	//UV�v�Z
	Out.uv = uvRect.xy * (1.0f - In.uv) + uvRect.zw * (In.uv);

	return Out;
}

float4 ps_main(VS_OUT In) : COLOR0
{

	float4 ret;
	float4 col = tex2D(g_diffuseTextureSampler, In.uv) * color;

	ret = col;

	if (isMonochrome)
	{
		//���m�N�����ɂ���Ƃ���RGB�̕��S�����B
		float4 tomono = float4(0.298912, 0.586611, 0.114478, 0.0);
		//�e�N�X�`���̃s�N�Z���F�ɒ��_�F����������
		ret = dot(col, tomono);
		//�A���t�@�l�����͌��̃e�N�X�`���ɖ߂�
		ret.w = col.w;
	}

	return ret;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};