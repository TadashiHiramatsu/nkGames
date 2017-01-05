/*
 *2D�`��shader
 */
texture g_diffuseTexture;		//�f�B�t���[�Y�e�N�X�`���B
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
	float4 col = tex2D(g_diffuseTextureSampler, In.uv);
	//�F�v�Z
	col.r *= color.r;
	col.g *= color.g;
	col.b *= color.b;
	//�s�����x�v�Z
	col.a *= color.a;
	return col;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};