/**
 * @file _Graphics\_PostEffect\nkBloom.h
 *
 * �u���[���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �u���[���N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Bloom : Noncopyable
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

		/** �L���t���O. */
		bool isEnable_;

		/** �d��. */
		static const int NUM_WEIGHTS = 8;
		/** �d�� [num weights]. */
		float Weights_[NUM_WEIGHTS];

		/** �G�t�F�N�g. */
		Effect* Effect_;
		
		/** �����_�����O�^�[�Q�b�g. */
		RenderTarget LuminanceRT_;
	
		/** �ڂ��������p��RT. */
		RenderTarget CombineRT_;

		/** �_�E���T���v�����O�pRT�̐�. */
		static const int NUM_DOWN_SAMPLING_RT = 10;
		/** �P�x���_�E���T���v�����O���邽�߂�RT. */
		RenderTarget DownSamplingRT_[NUM_DOWN_SAMPLING_RT];

	};

}// namespace nkEngine