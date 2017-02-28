//�X�L�����f���V�F�[�_�[

#include"LightingFunction.h"
#include"ShadowFunction.h"

//�X�L���s��B
#define MAX_MATRICES  26
float4x3 g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;//�A�j���[�V�����p
float g_numBone;			//���̐��B

float4x4 g_mWorldMatrix; //���[���h�s��
float4x4 g_mRotation; //��]�s��
float4x4 g_mViewProj : VIEWPROJECTION;

float4x4 g_mViewMatrixRotInv;	//�J�����̉�]�s��̋t�s��B

int4 g_flags;				//x�ɖ@���}�b�v�̕ێ��t���O�Ay�̓V���h�E���V�[�o�[�Az�̓t���l���Aw�͋P�x

//��ʊE�[�x
bool g_isDepthField;

//�t�H�O�p�����[�^ x:�t�H�O��������n�߂鋗�� ,y:�t�H�O�������肫�鋗�� ,z:�t�H�O�̎��
float4 g_fogParam;
//�t�H�O�̐F.
float4 g_fogColor;

/** �O���ݒ�J���[. */
float4 g_Color;

//�f�B�t���[�Y�e�N�X�`���B
texture g_diffuseTexture;
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
	AddressV = Wrap;
};

//�@���}�b�v
texture g_normalMap;		
sampler g_normalMapSampler =
sampler_state
{
	Texture = <g_normalMap>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
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
	float3 Tangent	: TEXCOORD1; //�ڃx�N�g��
	float4 WorldPos_Depth : TEXCOORD2; //xyz�Ƀ��[���h���W�Bw�ɂ͎ˉe��Ԃł�depth���i�[�����B
};

//�V���h�E�}�b�v�o�͒��_
struct VS_OUTPUT_RENDER_SHADOW_MAP
{
	float4 Pos : POSITION;
	float4 depth : TEXCOORD;
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
	if (hasSkin) 
	{
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, true);
	}
	else 
	{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In, Pos, Normal, Tangent, true);
	}
	Out.WorldPos_Depth.xyz = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.WorldPos_Depth.w = Out.Pos.w;
	Out.Normal = normalize(Normal);
	Out.Tangent = normalize(Tangent);
	Out.Tex0 = In.Tex0;

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
	if (hasSkin) 
	{
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, true);
	}
	else
	{
		//�X�L���Ȃ��B
		CalcWorldPosAndNormal(In.base, Pos, Normal, Tangent, true);
	}
	float4x4 worldMat;
	worldMat[0] = In.mWorld1;
	worldMat[1] = In.mWorld2;
	worldMat[2] = In.mWorld3;
	worldMat[3] = In.mWorld4;
	Pos = mul(float4(Pos.xyz, 1.0f), worldMat);	//���[���h�s���������B
	Out.WorldPos_Depth.xyz = Pos.xyz;
	Out.Pos = mul(float4(Pos.xyz, 1.0f), g_mViewProj);
	Out.WorldPos_Depth.w = Out.Pos.w;
	Out.Normal = mul(normalize(Normal), worldMat);
	Out.Tex0 = In.base.Tex0;

	return Out;
}

//�s�N�Z���V�F�[�_�[
//param[in] �o�͒��_
//return �J���[
float4 PSMain(VS_OUTPUT In) : COLOR
{
	float4 color = 0.0f;
	float4 diffuseColor = tex2D(g_diffuseTextureSampler,In.Tex0);
	
	color = diffuseColor;
	
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

	//�f�B�t���[�Y���C�g�̌v�Z
	float4 lig = DiffuseLight(normal);

	if (g_flags.z)
	{
		//�������C�g
		float lim = 0.0f;
		float3 normalInCamera = mul(normal, g_mViewMatrixRotInv);
		float t = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		t = pow(t, 1.5f);
		lig.xyz += t * 0.7f;
	}
	if (g_isSpec)
	{
		//�X�y�L�������C�g�B
		lig.xyz += CalcSpecular(In.WorldPos_Depth, normal, In.Tex0);
	}
	if (g_flags.y)
	{
		//�e
		lig.xyz *= CalcShadow(In.WorldPos_Depth.xyz);
	}

	//���Ȕ����F
	lig.xyz += g_light.Emission;

	color *= lig;

	//�A���r�G���g���C�g
	color.xyz += diffuseColor.xyz * g_light.ambient.xyz;

	if (g_fogParam.z > 1.9f)
	{
		//�����t�H�O
		float h = max(In.WorldPos_Depth.y - g_fogParam.y, 0.0f);
		float t = min(h / g_fogParam.x, 1.0f);
		color.xyz = lerp(float3(g_fogColor.x, g_fogColor.y, g_fogColor.z), color.xyz, t);
	}
	else if (g_fogParam.z > 0.0f) 
	{
		//�����t�H�O
		float z = length(In.WorldPos_Depth.xyz - g_cameraPos);
		z = max(z - g_fogParam.x, 0.0f);
		float t = z / g_fogParam.y;
		color.xyz = lerp(color.xyz, float3(g_fogColor.x, g_fogColor.y, g_fogColor.z), t);
	}

	return color * g_Color;
}

//�V���h�E�}�b�v�������ݗp���_�V�F�[�_�[
//param[in] ���͒��_
//param[in] �X�L������H
VS_OUTPUT_RENDER_SHADOW_MAP VSMainRenderShadowMap(VS_INPUT In, uniform bool hasSkin)
{
	VS_OUTPUT_RENDER_SHADOW_MAP Out = (VS_OUTPUT_RENDER_SHADOW_MAP)0;
	float3 Pos, Normal, Tangent;
	if (hasSkin)
	{
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In, Pos, Normal, Tangent, false);
	}
	else
	{
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
	if (hasSkin) 
	{
		//�X�L������B
		CalcWorldPosAndNormalFromSkinMatrix(In.base, Pos, Normal, Tangent, false);
	}
	else 
	{
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
	return float4(z, z*z + 0.25f * (dx*dx + dy*dy), 0.0f, 1.0f);
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
