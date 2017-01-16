/**
 * @file _Graphics\_PostEffect\nkBloom.h
 *
 * �u���[���N���X�̒�`.
 */
#pragma once

#include"nkBlur.h"

namespace nkEngine
{

	/**
	 * �u���[���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Bloom
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Bloom()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Bloom()
		{
		}

		/**
		 * �쐬.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void Create(const BloomConfigS& config);

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param [in,out] postEffect If non-null, the post effect.
		 */
		void Render(PostEffect* postEffect);

		/**
		 * ���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Release();

	private:

		/**
		 * �d�݂��v�Z.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param dis The dis.
		 */
		void UpdateWeight(float dis);

	private:

		/** Number of weights. */
		static const int NUM_WEIGHTS = 8;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** �����_�����O�^�[�Q�b�g. */
		RenderTarget LuminanceRT_;
		/** �L���t���O. */
		bool isEnable_;
		/** The weights [num weights]. */
		float Weights_[NUM_WEIGHTS];
		/** The blur [ 2]. */
		Blur Blur_[2];

	};

}// namespace nkEngine