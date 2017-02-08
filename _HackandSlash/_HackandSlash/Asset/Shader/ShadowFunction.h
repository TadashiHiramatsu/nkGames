//�e�֌W�̊֐��W

//�V���h�E�p�̃e�N�X�`��
texture g_ShadowMap_0 : register(t0);
sampler g_ShadowMapSampler_0 =
sampler_state
{
	Texture = <g_ShadowMap_0>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
//�V���h�E�p�̃e�N�X�`��
texture g_ShadowMap_1 : register(t1);
sampler g_ShadowMapSampler_1 =
sampler_state
{
	Texture = <g_ShadowMap_1>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};
//�V���h�E�p�̃e�N�X�`��
texture g_ShadowMap_2 : register(t2);
sampler g_ShadowMapSampler_2 =
sampler_state
{
	Texture = <g_ShadowMap_2>;
	MipFilter = NONE;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

//�V���h�E�}�b�v�̍ő吔
#define MAX_SHADOW_MAP 3

//�V���h�E���V�[�o�[�p�̃p�����[�^
struct SShadowReceiverParam
{
	float4x4 mLightViewProj[MAX_SHADOW_MAP]; //���C�g�r���[�v���W�F�N�V�����s��
	bool vsmFlag; //�o���A���X�V���h�E�}�b�v���s�����̃t���O
	int numShadowMap; //�V���h�E�}�b�v�̖���
};

SShadowReceiverParam g_ShadowReceiverParam : register(c0);	 //�V���h�E���V�[�o�[�̃p�����[�^

//�e�̌v�Z
float CalcShadow(float3 worldPos)
{
	sampler texSampler[MAX_SHADOW_MAP];
	texSampler[0] = g_ShadowMapSampler_0;
	texSampler[1] = g_ShadowMapSampler_1;
	texSampler[2] = g_ShadowMapSampler_2;

	//return�p�ϐ� 1�̂܂ܕԂ��Ɖe�ł͂Ȃ�
	float result = 1.0f;

	for (int i = 0; i < g_ShadowReceiverParam.numShadowMap; i++)
	{
		//�e���Ƃ�
		float4 posInLVP = mul(float4(worldPos, 1.0f), g_ShadowReceiverParam.mLightViewProj[i] );
		posInLVP.xyz /= posInLVP.w;

		//uv���W�ɕϊ�
		float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
		float2 shadow_val = 1.0f;

		if (shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f)
		{
			shadow_val = tex2D(texSampler[i], shadowMapUV).rg;
			float depth = min(posInLVP.z, 1.0f);

			if (g_ShadowReceiverParam.vsmFlag == 1)
			{
				if (depth > shadow_val.r) {
					//�`�F�r�V�F�t
					float depth_sq = shadow_val.r * shadow_val.r;
					float variance = max(shadow_val.g - depth_sq, 0.0006f);
					float md = depth - shadow_val.r;
					float P = variance / (variance + md * md);
					result = pow(P, 5.0f);
				}
			}
			else
			{
				if (depth > shadow_val.r + 0.006f)
				{
					result = 0.0f;
				}
			}
			//�ꖇ�Ƀq�b�g�����烋�[�v���I���
			break;
		}
	}
	return result;
}