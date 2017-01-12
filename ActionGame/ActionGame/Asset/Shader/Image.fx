/**
 * @file C:\Github\nkGames\ActionGame\ActionGame\Asset\Shader\Image.fx
 *
 * ImageUIのシェーダ.
 */

/** ディフューズテクスチャ. */
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

float4x4 matWorld; //ワールド行列.
float4 uvRect; //UV矩形.
float4 color; //色.

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

	//座標計算
	Out.pos = mul(In.pos, matWorld);
	//UV計算
	Out.uv = uvRect.xy * (1.0f - In.uv) + uvRect.zw * (In.uv);

	return Out;
}

float4 ps_main(VS_OUT In) : COLOR0
{
	float4 col = tex2D(g_diffuseTextureSampler, In.uv);

	return col * color;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
};