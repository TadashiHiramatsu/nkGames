//���C�e�B���O�֌W�̊֐��W

//�f�B�t���[�Y���C�g�̐�
#define NUM_DIFFUSE_LIGHT 6

//�X�y�L�����}�b�v
texture g_speculerMap;
sampler g_speculerMapSampler =
sampler_state
{
	Texture = <g_speculerMap>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Wrap;
	AddressV = Wrap;
};
//�X�y�L�����}�b�v�p
float4 g_cameraPos;
bool g_isSpec;

struct  SLight
{
	float3 diffuseLightDir[NUM_DIFFUSE_LIGHT];
	float4 diffuseLightColor[NUM_DIFFUSE_LIGHT];
	float3 ambient;
};

SLight g_light;

//�f�B�t���[�Y���C�g�̌v�Z
float4 DiffuseLight(float3 normal)
{
	float4 color = 0.0f;

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		color += max(0.0f, -dot(normal, g_light.diffuseLightDir[i])) * g_light.diffuseLightColor[i];
	}

	color.a = 1.0f;

	return color;
}

//�A���t�@�ɖ��ߍ��ދP�x���v�Z
float CalcLuminance(float3 color)
{
	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	if (luminance > 1.0f)
	{
		luminance = 1.0f / luminance;
	}
	else
	{
		luminance = 0.0f;
	}
	return luminance;
}

float3 CalcSpecular(float3 worldPos, float3 normal, float2 uv)
{
	float4 specPow = tex2D(g_speculerMapSampler, uv);
	float3 spec = 0.0f;
	float3 toCameraDir = normalize(g_cameraPos - worldPos);
	float3 R = -toCameraDir + 2.0f * dot(normal, toCameraDir) * normal;
	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++) {
		//�X�y�L�����������v�Z����B
		//���˃x�N�g�����v�Z�B
		float3 L = -g_light.diffuseLightDir[i].xyz;
		spec += g_light.diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 2) * g_light.diffuseLightColor[i].w;	//�X�y�L�������x�B
	}
	return spec * specPow;
}