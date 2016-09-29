#pragma once

namespace nkEngine
{
	struct SShadowConfig
	{
		SShadowConfig()
		{
			isEnable = isSoftShadowMap = false;
			ShadowMapW = ShadowMapH = 512;
			Fur = 1000.0f;
			Near = 1.0f;
		}
		bool isEnable; //�V���h�E�}�b�v�̗L���t���O
		int ShadowMapW; //�V���h�E�}�b�v�̉���
		int ShadowMapH; //�V���h�E�}�b�v�̏c��
		bool isSoftShadowMap; //�\�t�g�V���h�E�}�b�v�̗L���t���O
		float Fur; //�t�@�[
		float Near; //�j�A
	};

	struct SGraphicsConfig
	{
		SShadowConfig ShadowConfig;
	};
}