/**
 * @file C:\Github\nkGames\ActionGame\ActionGame\Asset\Shader\Sprite.fx
 *
 * Sprite用シェーダ.
 */

/** ワールド行列. */
float4x4 g_mWorld;
/** ビュープロジェクション行列. */
float4x4 g_mViewProj;

/** UV矩形. */
float4 g_RectUV;
/** 色. */
float4 g_Color;

/**
 * 入力頂点.
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
 * 出力頂点.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/11
 */
struct VS_OUTPUT
{
	float4 Pos	:	POSITION;
	float2 uv	:	TEXCOORD0;
};

/** ディフューズテクスチャ. */
texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

/**
 * 頂点シェーダ.
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
	//出力頂点
	VS_OUTPUT Out;

	//ポジション
	float3 pos;

	//ワールド行列計算
	pos = mul(In.Pos, g_mWorld);
	//ビュープロジェクション行列計算
	Out.Pos = mul(float4(pos.xyz, 1.0f), g_mViewProj);

	//UV計算
	Out.uv = g_RectUV.xy * (1.0f - In.uv) + g_RectUV.zw * (In.uv);

	return Out;
}

/**
 * ピクセルシェーダ.
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
	//テクスチャカラー読み込み
	float4 color = tex2D(g_TextureSampler,In.uv);

	//色計算
	color.r *= g_Color.r;
	color.g *= g_Color.g;
	color.b *= g_Color.b;
	//不透明度計算
	color.a *= g_Color.a;

	return color;
}

technique Sprite
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSMain();
		PixelShader = compile ps_2_0 PSMain();
	}
}