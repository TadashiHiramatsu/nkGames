//�X�L�����f���V�F�[�_�[

#include"LightingFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3 g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//�A�j���[�V�����p
float g_numBone;			//���̐��B

float4x4 g_mWorldMatrix; //���[���h�s��
float4x4 g_mRotation; //��]�s��
float4x4 g_mViewProj : VIEWPROJECTION;

float4x4 g_mViewMatrixRotInv;	////�J�����̉�]�s��̋t�s��B

float4x4 g_mLVP;	//���C�g�r���[�v���W�F�N�V����

int4 g_flags;				//x�ɖ@���}�b�v�̕ێ��t���O�Ay�̓V���h�E���V�[�o�[�Az�̓t���l���Aw�͋P�x

//��ʊE�[�x
bool g_isDepthField;

//�t�H�O�p�����[�^ x:�t�H�O��������n�߂鋗�� ,y:�t�H�O�������肫�鋗�� ,z:�t�H�O�̎��
float4 g_fogParam;

//�f�B�t���[�Y�e�N�X�`���B
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

//�V���h�E�e�N�X�`���B
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

//�@���}�b�v
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

//���͒��_
struct VS_INPUT
{
	float4  Pos             : POSITION;
	float4  BlendWeights    : BLENDWEIGHT;
	float4  BlendIndices    : BLENDINDICES;
	float3  Normal          : NORMAL;
	float3	Tangent			: TANGENT;		//�ڃx�N�g��
	float3  Tex0            : TEXCOORD0;
};

//�C���X�^���V���O���͒��_
struct VS_INPUT_INSTANCING
{
	VS_INPUT base;
	float4 mWorld1 : TEXCOORD1; //���[���h�s���1�s��
	float4 mWorld2 : TEXCOORD2; //���[���h�s���2�s��
	float4 mWorld3 : TEXCOORD3; //���[���h�s���3�s��
	float4 mWorld4 : TEXCOORD4; //���[���h�s���4�s��
};

//�o�͒��_
struct VS_OUTPUT
{
	float4 Pos      : POSITION;
	float3 Normal   : NORMAL;
    float2 Tex0     : TEXCOORD0;
	float3 Tangent	: TEXCOORD1;//�ڃx�N�g��
	float4 lightViewPos : TEXCOORD2;
	float3 worldPos : TEXCOORD3;
};

//�V���h�E�}�b�v�o�͒��_
struct VS_OUTPUT_RENDER_SHADOW_MAP
{
	float4 Pos : POSITION;
	float4 depth : TEXCOORD0;
};

//���[���h���W�ƃ��[���h�@�����X�L���s�񂩂�v�Z
//param[in]  ���͒��_
//param[out] ���[���h���W�̊i�[��
//param[out] ���[���h�@���̊i�[��
//param[out] ���[���h���x�N�g���̊i�[��
//param[in]  �e�H
void CalcWorldPosAndNormalFromSkinMatrix(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal)
{
	//������
	Pos = 0.0f;
	Normal = 0.0f;
	Tangent = 0.0f;

	//�u�����h����{�[���̃C���f�b�N�X�B
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);

	//�u�����h���[�g�B
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

//���[���h���W�ƃ��[���h�@�����v�Z
//param[in]  ���͒��_
//param[out] ���[���h���W�̊i�[��
//param[out] ���[���h�@���̊i�[��
//param[out] ���[���h���x�N�g���̊i�[��
//param[in]  �e�H
void CalcWorldPosAndNormal(VS_INPUT In, out float3 Pos, out float3 Normal, out float3 Tangent, uniform bool calcNormal)
{
	//������
	Normal = 0.0f;
	Tangent = 0.0f;
	Pos = mul(In.Pos, g_mWorldMatrix);
	if (calcNormal)
	{
		Normal = mul(In.Normal, g_mRotation);
		Tangent = mul(In.Tangent, g_mRotation);
	}
}

//���_�V�F�[�_�[
//param[in] ���͒��_
//param[in] �X�L������H
//return �o�͒��_
VS_OUTPUT VSMain( VS_INPUT In, uniform bool hasSkin )
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, true);
	}
	else {
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent, true);
	}
	Out.worldPos = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Normal = normalize(Normal);
	Out.Tangent = normalize(Tangent);
	Out.Tex0 = In.Tex0;
	if (g_flags.y) {
		//�V���h�E���V�[�o�[�B
		Out.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_mLVP);
	}
	return Out;
}

//���_�V�F�[�_�[(�C���X�^���V���O)
//param[in] ���͒��_(�C���X�^���V���O)
//param[in] �X�L������H
//return �o�͒��_
VS_OUTPUT VSMainInstancing(VS_INPUT_INSTANCING In, uniform bool hasSkin)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, true);
	}
	else {
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In.base, Pos, Normal, Tangent, true);
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat);	//���[���h�s���������B
	Out.worldPos = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.Normal = mul(normalize(Normal), worldMat);
	Out.Tex0 = In.base.Tex0;
	if (g_flags.y) {
		//�V���h�E���V�[�o�[�B
		Out.lightViewPos = mul(float4(Pos.xyz, 1.0f), g_mLVP);
	}
	return Out;
}

//�s�N�Z���V�F�[�_�[
//param[in] �o�͒��_
//return �J���[
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = tex2D(g_diffuseTextureSampler,In.Tex0);
	
	float3 normal = 0.0f;
	if (g_flags.x)
	{
		//�@���}�b�v����
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
		//�@���}�b�v�Ȃ�
		normal = In.Normal;
	}

	float4 lig = DiffuseLight(normal);

	if (g_flags.y)
	{
		//�e���Ƃ�
		float4 posInLVP = In.lightViewPos;
		posInLVP.xyz /= posInLVP.w;

		//uv���W�ɕϊ�
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
		float2 shadow_val = 1.0f;

		if (shadowMapUV.x <= 1.0f && shadowMapUV.y <= 1.0f && shadowMapUV.x >= 0.0f && shadowMapUV.y >= 0.0f) {
			shadow_val = tex2D(g_ShadowTextureSampler, shadowMapUV).rg;
			float depth = min(posInLVP.z, 1.0f);

			//if (depth > shadow_val.r) {
			//	//�`�F�r�V�F�t
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
		//�X�y�L�������C�g�B
		lig.xyz += CalcSpecular(In.worldPos, normal, In.Tex0);
	}

	//�A���r�G���g���C�g
	lig.xyz += g_light.ambient.xyz;
	color.xyz *= lig;

	if (g_flags.z)
	{
		//�������C�g
		float3 normalInCamera = mul(normal, g_mViewMatrixRotInv);
		float t = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		t = pow(t, 1.5f);
		color.xyz += t * 0.7f;
	}

	//�A���t�@�ɋP�x�𖄂ߍ���
	if (g_flags.w){
		color.a *= CalcLuminance(color.xyz);
	}

	if (g_fogParam.z > 1.9f) {
		//�����t�H�O
		float h = max(In.worldPos.y - g_fogParam.y, 0.0f);
		float t = min(h / g_fogParam.x, 1.0f);
		color.xyz = lerp(float3(1.0f, 1.0f, 1.0f), color.xyz, t);
	}
	else if (g_fogParam.z > 0.0f) {
		//�����t�H�O
		float z = length(In.worldPos - g_cameraPos);
		z = max(z - g_fogParam.x, 0.0f);
		float t = z / g_fogParam.y;
		color.xyz = lerp(color.xyz, float3(1.0f, 1.0f, 1.0f), t);
	}
	
	return color;
}

//�V���h�E�}�b�v�������ݗp���_�V�F�[�_�[
//param[in] ���͒��_
//param[in] �X�L������H
VS_OUTPUT_RENDER_SHADOW_MAP VSMainRenderShadowMap(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP Out = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, false);
	}
	else {
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent, false);
	}
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.depth = Out.Pos;
	return Out;
}

//�V���h�E�}�b�v�������ݗp���_�V�F�[�_�[(�C���X�^���V���O)
//param[in] ���͒��_(�C���X�^���V���O)
//param[in] �X�L������H
VS_OUTPUT_RENDER_SHADOW_MAP VSMainInstancingRenderShadowMap(VS_INPUT_INSTANCING In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP Out = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin) {
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, false);
	}
	else {
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In.base, Pos, Normal, Tangent, false);
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat);	//���[���h�s���������B
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.depth = Out.Pos;
	return Out;
}

//�V���h�E�}�b�v�������ݗp�s�N�Z���V�F�[�_�[
//param[in] �o�͒��_
//return �J���[
float4 PSMainRenderShadowMap(VS_OUTPUT_RENDER_SHADOW_MAP In) : COLOR
{
	float z = In.depth.z / In.depth.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z + 0.25f*(dx*dx + dy*dy), 0.0f, 1.0f);
}


//�X�L�����胂�f���p�̃e�N�j�b�N
technique SkinModel
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain(true);
		PixelShader = compile ps_3_0 PSMain();
    }
}

//�X�L���Ȃ����f���p�̃e�N�j�b�N
technique NoSkinModel
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//�X�L������̃C���X�^���V���O�`��p�̃e�N�j�b�N
technique SkinModelInstancing
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancing(true);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//�X�L���Ȃ��̃C���X�^���V���O�`��p�̃e�N�j�b�N
technique NoSkinModelInstancing
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancing(false);
		PixelShader = compile ps_3_0 PSMain();
	}
}

//�X�L�����胂�f���p�̃V���h�E�}�b�v�`�����݃e�N�j�b�N
technique SkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(true);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//�X�L���Ȃ����f���p�̃V���h�E�}�b�v�`�����݃e�N�j�b�N
technique NoSkinModelRenderShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainRenderShadowMap(false);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//�X�L�����胂�f���̃C���X�^���V���O�`��p�̃V���h�E�}�b�v�`�����݃e�N�j�b�N
technique SkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(true);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}

//�X�L���Ȃ����f���̃C���X�^���V���O�`��p�̃V���h�E�}�b�v�`�����݃e�N�j�b�N
technique NoSkinModelInstancingRenderToShadowMap
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMainInstancingRenderShadowMap(false);
		PixelShader = compile ps_3_0 PSMainRenderShadowMap();
	}
}
