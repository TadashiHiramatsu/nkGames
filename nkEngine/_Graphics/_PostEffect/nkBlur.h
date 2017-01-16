/**
 * @file _Graphics\nkBlur.h
 *
 * �u���[�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �u���[�N���X.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class Blur
	{
	public:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		Blur();

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~Blur();

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @param w			 ����.
		 * @param h			 �c��.
		 * @param srcTexture ���ƂȂ�e�N�X�`��.
		 */
		void Init(int w,int h,const Texture& srcTexture);

		/**
		 * �`��.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Render();

		/**
		 * �e�N�X�`�����擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return Null if it fails, else the texture.
		 */
		const Texture* GetTexture()const
		{
			return BlurRT_[1].GetTexture();
		}

		/**
		 * �e�N�X�`���̉���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size w.
		 */
		int GetSizeW()
		{
			return SrcTexWH_[0];
		}

		/**
		 * �e�N�X�`���̍���.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The size h.
		 */
		int GetSizeH()
		{
			return SrcTexWH_[1];
		}

	private:

		/** �K�E�V�A���u���[�̌��ʂ�`�����ރ����_�����O�^�[�Q�b�g. */
		RenderTarget BlurRT_[2];
		/** �\�[�X�ƂȂ�e�N�X�`��. */
		const Texture*	SrcTexture_;
		/** �G�t�F�N�g. */
		ID3DXEffect* Effect_;
		/** �e�N�X�`���̕�. */
		int SrcTexWH_[2];
		/** �v���~�e�B�u. */
		Primitive Primitive_;

	};

}// namespace nkEngine