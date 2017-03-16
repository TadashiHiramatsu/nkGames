/**
 * @file _Graphics\nkScreenRender.h
 *
 * �V�[���������_�����O����N���X���`.
 */
#pragma once

#include"_PostEffect\nkPostEffect.h"

namespace nkEngine
{

	/**
	 * �V�[�������_�[�N���X.
	 * �V���O���g���N���X
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 */
	class CScreenRender : Noncopyable
	{
	private:

		/**
		 * �R���X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		CScreenRender()
		{
		}

		/**
		 * �f�X�g���N�^.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		~CScreenRender()
		{
		}

	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 *
		 * @return The instance.
		 */
		inline static CScreenRender& GetInstance()
		{
			static CScreenRender instance;
			return instance;
		}

		/**
		 * ������.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/09
		 */
		void Start();

		/**
		 * �O���t�B�b�N�֘A�̏�����.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param config The configuration.
		 */
		void StartGraphic(const GraphicsConfigS& config);

		/**
		* �X�V.
		*
		* @author HiramatsuTadashi
		* @date 2017/01/09
		*/
		void Loop();

		/**
		 * ���C�������_�[�^�[�Q�b�g���擾.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 *
		 * @param num Number of.
		 *
		 * @return The main render target.
		 */
		RenderTarget& GetMainRenderTarget()
		{
			return MainRT_[CurrentMainRT_];
		}

		/**
		 * ���C�������_�����O�^�[�Q�b�g��؂�ւ�.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void ToggleMainRenderTarget()
		{
			CurrentMainRT_ ^= 1;
		}

	private:

		/**
		 * �o�b�N�o�b�t�@�Ƀ����_�����O.
		 *
		 * @author HiramatsuTadashi
		 * @date 2017/01/16
		 */
		void BackBufferRender();

	private:

		/** �f�o�C�X. */
		IDirect3DDevice9* Device_ = nullptr;

		/** �o�b�N�o�b�t�@�̃����_�[�^�[�Q�b�g. */
		RenderTarget BackBufferRT_;

		/** ���ݎg�p����Ă��郁�C�������_�[�^�[�Q�b�g. */
		unsigned char CurrentMainRT_ = 0;
		/** ���C���̃����_�[�^�[�Q�b�g. */
		RenderTarget MainRT_[2];

		/** The post effect. */
		PostEffect PostEffect_;

		/** �v���~�e�B�u. */
		Primitive Primitive_;
		/** �G�t�F�N�g. */
		Effect* Effect_ = nullptr;

	};

	/**
	 * �X�N���[�������_�[�N���X�̎擾.
	 *
	 * @author HiramatsuTadashi
	 * @date 2017/01/09
	 *
	 * @return A reference to a CScreenRender.
	 */
	inline static CScreenRender& ScreenRender()
	{
		return CScreenRender::GetInstance();
	}
	 
}// namespace nkEngine