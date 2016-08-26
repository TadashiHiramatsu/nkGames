//���C�e�B���O�֌W�̊֐��W

//�f�B�t���[�Y���C�g�̐�
#define NUM_DIFFUSE_LIGHT 6

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