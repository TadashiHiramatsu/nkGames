#pragma once

#include"..\nkBlur.h"

namespace nkEngine
{
	class CBloom
	{
	public:
		//�R���X�g���N�^
		CBloom();
		//�f�X�g���N�^
		~CBloom();
		//�`��
		void Render();
		//�쐬
		void Create(bool);
		//���
		void Release();
	private:
		void UpdateWeight(float);
	private:
		static const int NUM_WEIGHTS = 8;
		ID3DXEffect* m_pEffect;
		CRenderTarget m_luminanceRenderTarget;
		bool m_isEnable;
		float m_weights[NUM_WEIGHTS];
		CSprite fullscreen;

		CBlur Blur[2];
	};
}