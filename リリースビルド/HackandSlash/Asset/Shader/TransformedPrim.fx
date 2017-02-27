/**
 * @file C:\Github\nkGames\_HackandSlash\_HackandSlash\Asset\Shader\TransformedPrim.fx
 *
 * トランスフォーム済みプリミティブを描画.
 */

/**
 * 頂点シェーダ入力情報.
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
 * 頂点シェーダ出力情報.
 *
 * @author HiramatsuTadashi
 * @date 2017/01/16
 */
struct VS_OUTPUT
{
	float4 Pos	: POSITION;
	float2 uv	: TEXCOORD0;
};

/** テクスチャ. */
texture g_Texture;
sampler g_TextureSampler =
sampler_state
{
	Texture = <g_Texture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

/** オフセット. */
float2 g_Offset;


/**
 * 頂点シェーダ.
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

	//トランスフォーム済み頂点なのでそのまま
	Out.Pos = In.Pos;

	//uvのオフセット計算
	Out.uv = In.uv + g_Offset;
	
	return Out;
}

/**
 * ピクセルシェーダ.
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