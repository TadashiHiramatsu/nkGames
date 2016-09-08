//スキンモデルシェーダー

#include"LightingFunction.h"

//スキン行列。
#define MAX_MATRICES  26
float4x3 g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//アニメーション用
float g_numBone;			//骨の数。

float4x4 g_mWorldMatrix; //ワールド行列
float4x4 g_mRotation; //回転行列
float4x4 g_mViewProj : VIEWPROJECTION;

float4x4 g_mViewMatrixRotInv;	////カメラの回転行列の逆行列。

float4x4 g_mLVP;	//ライトビュープロジェクション

int4 g_flags;				//xに法線マップの保持フラグ、yはシャドウレシーバー、zはフレネル、wは輝度

//被写界深度
bool g_isDepthField;

//フォグパラメータ x:フォグがかかり始める距離 ,y:フォグがかかりきる距離 ,z:フォグの種類
float4 g_fogParam;

//ディフューズテクスチャ。
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

//シャドウテクスチャ。
texture g_ShadowTexture;	
sampler g_ShadowTextureSampler =
sampler_state
{
	Texture = <g_ShadowTexture>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//法線マップ
texture g_normalMap;		
sampler g_normalMapSampler =
sampler_state
{
	Texture = <g_normalMap>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};

//入力頂点
struct VS_INPUT
{
	float4  Pos             : POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float3  Normal          : NORMAL;
	float3	Tangent			: TANGENT;		//接ベクトル
	float3  Tex0            : TEXCOORD0;
};

//インスタンシング入力頂点
struct VS_INPUT_INSTANCING
{
	VS_INPUT base;
	float4 mWorld1 : TEXCOORD1; //ワールド行列の1行目
	float4 mWorld2 : TEXCOORD2; //ワールド行列の2行目
	float4 mWorld3 : TEXCOORD3; //ワールド行列の3行目
	float4 mWorld4 : TEXCOORD4; //ワールド行列の4行目
};

//出力頂点
struct VS_OUTPUT
{
	float4 Pos      : POSITION;
	float3 Normal   : NORMAL;
    float2 Tex0     : TEXCOORD0;
	float3 Tangent	: TEXCOORD1;//接ベクトル
	float4 lightViewPos : TEXCOORD2;
	float3 worldPos : TEXCOORD3;
};

//シャドウマップ出力頂点
struct VS_OUTPUT_RENDER_SHADOW_MAP
{
	float4 Pos : POSITION;
	float4 depth : TEXCOORD0;
};

//ワールド座標とワールド法線をスキン行列から計算
//param[in]  入力頂点
//param[out] ワールド座標の格納先
//param[out] ワールド法線の格納先
//param[out] ワールド説ベクトルの格納先
//param[in]  影？
void CalcWorldPosAndNormalFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal)
{
	//初期化
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;

	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
	int   IndexArray[4] = (int[4])IndexVector;
	float LastWeight = 0.0f;
	
	for (int iBone = 0; iBone < g_numBone - 1; iBone++)
	{
		LastWeight = LastWeight + BlendWeightsArray[iBone];

		Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		if (calcNormal) 
		{
			Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
			Tangent += mul(In.Tangent, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		}
	}
	LastWeight = 1.0f - LastWeight;

	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	if (calcNormal) 
	{
		Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
		Tangent += (mul(In.Tangent, g_mWorldMatrixArray[IndexArray[g_numBone - 1]]) * LastWeight);
	}
}

//ワールド座標とワールド法線を計算
//param[in]  入力頂点
//param[out] ワールド座標の格納先
//param[out] ワールド法線の格納先
//param[out] ワールド説ベクトルの格納先
//param[in]  影？
void CalcWorldPosAndNormal(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal)
{
	//初期化
	Normal = 0.0f;
	Tangent = 0.0f;
	Pos = mul(In.Pos, g_mWorldMatrix);
	if (calcNormal)
	{
		Normal = mul(In.Normal, g_mRotation);
		Tangent = mul(In.Tangent, g_mRotation);
	}
}

//頂点シェーダー
//param[in] 入力頂点
//param[in] スキンあり？
//return 出力頂点
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, true);
	}
	else {
		//スキンなし。
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent, true);
	}
	Out.worldPos = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Normal = normalize(Normal);
	Out.Tangent = normalize(Tangent);
	Out.Tex0 = In.Tex0;
	if (g_flags.y) {
		//シャドウレシーバー。
		Out.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_mLVP);
	}
	return Out;
}

//頂点シェーダー(インスタンシング)
//param[in] 入力頂点(インスタンシング)
//param[in] スキンあり？
//return 出力頂点
VS_OUTPUT VSMainInstancing(VS_INPUT_INSTANCING In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, true);
	}
	else {
		//スキンなし。
		CalcWorldPosAndNormal(In.base, Pos, Normal, Tangent, true);
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat);	//ワールド行列をかける。
	Out.worldPos = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Normal = mul(normalize(Normal), worldMat);
	Out.Tex0 = In.base.Tex0;
	if (g_flags.y) {
		//シャドウレシーバー。
		Out.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_mLVP);
	}
	return Out;
}

//ピクセルシェーダー
//param[in] 出力頂点
//return カラー
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler,In.Tex0);
	
	float3 normal = 0.0f;
	if (g_flags.x)
	{
		//法線マップあり
		normal = tex2D(g_normalMapSampler, In.Tex0);
		float4x4 tangentSpaceMatrix;
		float3 biNormal = normalize(cross(In.Tangent, In.Normal));
		tangentSpaceMatrix[0] = float4(In.Tangent, 0.0f);
		tangentSpaceMatrix[1] = float4(biNormal, 0.0f);
		tangentSpaceMatrix[2] = float4(In.Normal, 0.0f);
		tangentSpaceMatrix[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);
		normal = (normal * 2.0f) - 1.0f;
		normal = tangentSpaceMatrix[0] * normal.x + tangentSpaceMatrix[1] * normal.y + tangentSpaceMatrix[2] * normal.z;
	}
	else
	{
		//法線マップなし
		normal = In.Normal;
	}

	float4 lig = DiffuseLight(normal);

	if (g_flags.y)
	{
		//影落とす
		float4 posInLVP = In.lightViewPos;
		posInLVP.xyz /= posInLVP.w;

		//uv座標に変換
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
		float2 shadow_val = 1.0f;

		if (shadowMapUV.x <= 1.0f && shadowMapUV.y <= 1.0f && shadowMapUV.x >= 0.0f && shadowMapUV.y >= 0.0f) {
			shadow_val = tex2D(g_ShadowTextureSampler, shadowMapUV).rg;
			float depth = min(posInLVP.z, 1.0f);

			//if (depth > shadow_val.r) {
			//	//チェビシェフ
			//	float depth_sq = shadow_val.r * shadow_val.r;
			//	float variance = max(shadow_val.g - depth_sq, 0.0006f);
			//	float md = depth - shadow_val.r;
			//	float P = variance / (variance + md * md);
			//	lig *= pow(P, 5.0f);
			//}
			if (depth > shadow_val.r + 0.0006f) {
				lig = 0;
			}
		}
	}

	if (g_isSpec)
	{
		//スペキュラライト。
		lig.xyz += CalcSpecular(In.worldPos, normal, In.Tex0);
	}

	//アンビエントライト
	lig.xyz += g_light.ambient.xyz;
	color.xyz *= lig;

	if (g_flags.z)
	{
		//リムライト
		float3 normalInCamera = mul(normal, g_mViewMatrixRotInv);
		float t = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		t = pow(t, 1.5f);
		color.xyz += t * 0.7f;
	}

	//アルファに輝度を埋め込む
	if (g_flags.w){
		color.a *= CalcLuminance(color.xyz);
	}

	if (g_fogParam.z > 1.9f) {
		//高さフォグ
		float h = max(In.worldPos.y - g_fogParam.y, 0.0f);
		float t = min(h / g_fogParam.x, 1.0f);
		color.xyz = lerp(float3(1.0f, 1.0f, 1.0f), color.xyz, t);
	}
	else if (g_fogParam.z > 0.0f) {
		//距離フォグ
		float z = length(In.worldPos - g_cameraPos);
		z = max(z - g_fogParam.x, 0.0f);
		float t = z / g_fogParam.y;
		color.xyz = lerp(color.xyz, float3(1.0f, 1.0f, 1.0f), t);
	}
	
	return color;
}

//シャドウマップ書き込み用頂点シェーダー
//param[in] 入力頂点
//param[in] スキンあり？
VS_OUTPUT_RENDER_SHADOW_MAP VSMainRenderShadowMap(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP Out = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, false);
	}
	else {
		//スキンなし。
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent, false);
	}
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.depth = Out.Pos;
	return Out;
}

//シャドウマップ書き込み用頂点シェーダー(インスタンシング)
//param[in] 入力頂点(インスタンシング)
//param[in] スキンあり？
VS_OUTPUT_RENDER_SHADOW_MAP VSMainInstancingRenderShadowMap(VS_INPUT_INSTANCING In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP Out = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//スキンあり。
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, false);
	}
	else {
		//スキンなし。
		CalcWorldPosAndNormal(In.base, Pos, Normal, Tangent, false);
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat);	//ワールド行列をかける。
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.depth = Out.Pos;
	return Out;
}

//シャドウマップ書き込み用ピクセルシェーダー
//param[in] 出力頂点
//return カラー
float4 PSMainRenderShadowMap(VS_OUTPUT_RENDER_SHADOW_MAP In) : COLOR
{
	float z = In.depth.z / In.depth.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z + 0.25f*(dx*dx + dy*dy), 0.0f, 1.0f);
}


//スキンありモデル用のテクニック
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
    }
}

//スキンなしモデル用のテクニック
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//スキンありのインスタンシング描画用のテクニック
technique SkinModelInstancing
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancing(true);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//スキンなしのインスタンシング描画用のテクニック
technique NoSkinModelInstancing
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancing(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//スキンありモデル用のシャドウマップ描き込みテクニック
technique SkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(true);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//スキンなしモデル用のシャドウマップ描き込みテクニック
technique NoSkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(false);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//スキンありモデルのインスタンシング描画用のシャドウマップ描き込みテクニック
technique SkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(true);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//スキンなしモデルのインスタンシング描画用のシャドウマップ描き込みテクニック
technique NoSkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(false);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}
